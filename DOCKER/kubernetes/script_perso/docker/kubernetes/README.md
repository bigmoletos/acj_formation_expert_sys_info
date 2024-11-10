# Démystifions Kubernetes

## Licence

Tous les scripts, images, textes en markdown et présentations dans ce dépôt sont sous licence CC BY-SA 4.0 (Creative Commons Attribution-ShareAlike 4.0 International).

Cette licence exige que les réutilisateurs donnent crédit au créateur. Elle permet aux réutilisateurs de distribuer, remixer, adapter et construire sur le matériel dans n'importe quel support ou format, même à des fins commerciales. Si d'autres remixent, adaptent ou construisent sur le matériel, ils doivent licencier le matériel modifié sous des termes identiques.

    BY : Le crédit doit vous être donné, le créateur.
    SA : Les adaptations doivent être partagées sous les mêmes termes.

## Prérequis

Je vais lancer cela sur une VM propre fonctionnant sous Ubuntu 22.04. Le nom d'hôte pour cette VM doit être **kubernetes** (en raison des ✨*choses liées aux certificats*✨ que je ne veux pas vous déranger avec).

### api-server & amis

Obtenez les binaires de Kubernetes à partir de la page de version de Kubernetes. Nous voulons le bundle "server" pour Linux amd64.

Note : Le dépôt de jpetazzo mentionne un binaire tout-en-un appelé `hyperkube` qui ne semble plus exister.

### etcd

Voir [https://github.com/etcd-io/etcd/releases/tag/v3.5.10](https://github.com/etcd-io/etcd/releases/tag/v3.5.10)

Obtenez les binaires à partir de la page de version d'etcd. Choisissez le tarball pour Linux amd64. Dans ce tarball, nous avons juste besoin de `etcd` et (juste au cas où) `etcdctl`.

C'est une ligne de commande élégante pour télécharger le tarball et extraire juste ce dont nous avons besoin :

Testez-le

Créez un répertoire pour héberger les fichiers de base de données etcd

### containerd

Note : Jérôme utilisait Docker, mais depuis Kubernetes 1.24, dockershim, le composant responsable de la liaison entre le démon docker et Kubernetes, n'est plus supporté. J'ai (comme beaucoup d'autres) changé pour `containerd`, mais il existe des alternatives.

### runc

`containerd` est un runtime de conteneur de haut niveau qui repose sur `runc` (de bas niveau). Téléchargez-le :

### Divers

Nous avons besoin de l'outil `cfssl` pour générer des certificats. Installez-le (voir [github.com/cloudflare/cfssl](https://github.com/cloudflare/cfssl#installation)).

Pour installer Calico (le plugin CNI dans ce tutoriel), le moyen le plus simple est d'utiliser `helm` (voir [helm.sh/docs](https://helm.sh/docs/intro/install/)).

Optionnellement, pour faciliter ce tutoriel, vous devriez également avoir un moyen de passer facilement entre les terminaux. `tmux` ou `screen` sont vos amis. Voici une [fiche de triche tmux](https://tmuxcheatsheet.com/) si vous en avez besoin ;-).

Optionnellement également, `curl` est un bon ajout pour jouer avec le serveur API.

### Certificats

Bien que ce tutoriel puisse être exécuté sans avoir de chiffrement TLS entre les composants (comme Jérôme l'a fait), pour le plaisir (et le profit), je préfère utiliser le chiffrement partout. Voir [github.com/kelseyhightower/kubernetes-the-hard-way](https://github.com/kelseyhightower/kubernetes-the-hard-way/blob/master/docs/04-certificate-authority.md)

Générez le CA

```bash
mkdir certs && cd certs

{
cat > ca-config.json <<EOF
{
  "signing": {
    "default": {
      "expiry": "8760h"
    },
    "profiles": {
      "kubernetes": {
        "usages": ["signing", "key encipherment", "server auth", "client auth"],
        "expiry": "8760h"
      }
    }
  }
}
EOF
cat > ca-csr.json <<EOF
{
  "CN": "Kubernetes",
  "key": {
    "algo": "rsa",
    "size": 2048
  },
  "names": [
    {
      "C": "FR",
      "L": "Pessac",
      "O": "Kubernetes",
      "OU": "CA",
      "ST": "Nouvelle Aquitaine"
    }
  ]
}
EOF
cfssl gencert -initca ca-csr.json | cfssljson -bare ca
}
```

Générez les certificats administratifs (seront utilisés pour tout, mauvaise pratique).

```bash
{
cat > admin-csr.json <<EOF
{
  "CN": "admin",
  "key": {
    "algo": "rsa",
    "size": 2048
  },
  "names": [
    {
      "C": "FR",
      "L": "Pessac",
      "O": "system:masters",
      "OU": "Démystifions Kubernetes",
      "ST": "Nouvelle Aquitaine"
    }
  ]
}
EOF
cfssl gencert \
  -ca=ca.pem \
  -ca-key=ca-key.pem \
  -config=ca-config.json \
  -profile=kubernetes \
  admin-csr.json | cfssljson -bare admin
}
```

Retournez dans le répertoire principal

```bash
cd ..
```

### Avertissements

Nous allons utiliser le certificat administrateur pour TOUS les composants de Kubernetes. S'il vous plaît, ne faites pas cela, c'est vraiment une mauvaise pratique. Tous les composants devraient avoir des certificats séparés (certains nécessitent même plus d'un). Voir [PKI certificates and requirements](https://kubernetes.io/docs/setup/best-practices/certificates/) dans la documentation officielle pour plus d'informations sur ce sujet.

De plus, de nombreux fichiers seront créés à divers endroits, et parfois ils nécessitent des privilèges pour le faire. Pour plus de commodité, certains binaires seront lancés en tant que **root** (`containerd`, `kubelet`, `kube-proxy`) en utilisant `sudo`.

## Bootstrap Kubernetes

### Configurations d'authentification

Nous allons créer des fichiers kubeconfig en utilisant les certificats que nous avons générés. Nous les utiliserons plus tard :

```bash
#lancer tmux
tmux new -t bash

export KUBECONFIG=admin.conf
kubectl config set-cluster demystifions-kubernetes \
  --certificate-authority=certs/ca.pem \
  --embed-certs=true \
  --server=https://127.0.0.1:6443

kubectl config set-credentials admin \
  --embed-certs=true \
  --client-certificate=certs/admin.pem \
  --client-key=certs/admin-key.pem

kubectl config set-context admin \
  --cluster=demystifions-kubernetes \
  --user=admin

kubectl config use-context admin
```

### etcd

Nous ne pouvons pas démarrer le serveur API tant que nous n'avons pas un backend `etcd` pour soutenir sa persistance. Commençons donc par la commande `etcd` :

```bash
#create a new tmux session for etcd
'[ctrl]-b' and then ': new -s etcd'

./etcd --advertise-client-urls https://127.0.0.1:2379 \
--client-cert-auth \
--data-dir etcd-data \
--cert-file=certs/admin.pem \
--key-file=certs/admin-key.pem \
--listen-client-urls https://127.0.0.1:2379 \
--trusted-ca-file=certs/ca.pem
[...]
{"level":"info","ts":"2022-11-29T17:34:54.601+0100","caller":"embed/serve.go:198","msg":"serving client traffic securely","address":"127.0.0.1:2379"}
```

### kube-apiserver

Maintenant, nous pouvons démarrer le `kube-apiserver` :

```bash
#create a new tmux session for apiserver
'[ctrl]-b' and then ': new -s apiserver'

./kube-apiserver --allow-privileged \
--authorization-mode=Node,RBAC \
--client-ca-file=certs/ca.pem \
--etcd-cafile=certs/ca.pem \
--etcd-certfile=certs/admin.pem \
--etcd-keyfile=certs/admin-key.pem \
--etcd-servers=https://127.0.0.1:2379 \
--service-account-key-file=certs/admin.pem \
--service-account-signing-key-file=certs/admin-key.pem \
--service-account-issuer=https://kubernetes.default.svc.cluster.local \
--tls-cert-file=certs/admin.pem \
--tls-private-key-file=certs/admin-key.pem
```

Note : vous pouvez ensuite passer entre les sessions avec '[ctrl]-b' et puis '(' ou ')'

Retournez à la session tmux "bash" et vérifiez que le serveur API répond

```bash
'[ctrl]-b' and then ': attach -t bash'

kubectl version --short
```

Vous devriez obtenir une sortie similaire

```
Client Version: v1.29.0-alpha.3
Kustomize Version: v4.5.7
Server Version: v1.29.0-alpha.3
```

Vérifiez quelles API sont disponibles

```
kubectl api-resources | head
NAME                              SHORTNAMES   APIVERSION                             NAMESPACED   KIND
bindings                                       v1                                     true         Binding
componentstatuses                 cs           v1                                     false        ComponentStatus
configmaps                        cm           v1                                     true         ConfigMap
endpoints                         ep           v1                                     true         Endpoints
events                            ev           v1                                     true         Event
limitranges                       limits       v1                                     true         LimitRange
namespaces                        ns           v1                                     false        Namespace
nodes                             no           v1                                     false        Node
persistentvolumeclaims            pvc          v1                                     true         PersistentVolumeClaim
```

Nous pouvons essayer de déployer un *Deployment* et voir que le *Deployment* est créé mais pas les *Pods*.

```
cat > deploy.yaml << EOF
apiVersion: apps/v1
kind: Deployment
metadata:
  labels:
    app: web
  name: web
spec:
  replicas: 2
  selector:
    matchLabels:
      app: web
  template:
    metadata:
      labels:
        app: web
    spec:
      containers:
      - image: zwindler/vhelloworld
        name: web
EOF
kubectl apply -f deploy.yaml

#ou
#kubectl create deployment web --image=zwindler/vhelloworld
```

Vous devriez obtenir le message suivant :
```bash
deployment.apps/web created
```

Mais... rien ne se passe

```bash
kubectl get deploy
NAME   READY   UP-TO-DATE   AVAILABLE   AGE
web    0/1     0            0           3m38s

kubectl get pods
No resources found in default namespace.
```

### kube-controller-manager

C'est parce que la plupart de la magie de Kubernetes est faite par le **Controller manager** de Kubernetes (et les contrôleurs qu'il contrôle). Typiquement ici, créer un *Deployment* déclenchera la création d'un *Replicaset*, qui à son tour créera nos *Pods*.

Nous pouvons démarrer le controller manager pour corriger cela.

```bash
#create a new tmux session for the controller manager
'[ctrl]-b' and then ': new -s controller'

./kube-controller-manager \
--kubeconfig admin.conf \
--cluster-signing-cert-file=certs/ca.pem \
--cluster-signing-key-file=certs/ca-key.pem \
--service-account-private-key-file=certs/admin-key.pem \
--use-service-account-credentials \
--root-ca-file=certs/ca.pem
[...]
I1130 14:36:38.454244    1772 garbagecollector.go:163] Garbage collector: all resource monitors have synced. Proceeding to collect garbage
```

Le *ReplicaSet* et ensuite le *Pod* sont créés... mais le *Pod* est bloqué en `Pending` indéfiniment !

C'est parce qu'il manque beaucoup de choses avant que le Pod puisse démarrer.

Pour le démarrer, nous avons encore besoin d'un planificateur pour décider où démarrer le **Pod**.

### kube-scheduler

Démarrons maintenant le `kube-scheduler` :

```bash
#create a new tmux session for scheduler
'[ctrl]-b' and then ': new -s scheduler'
./kube-scheduler --kubeconfig admin.conf

[...]
I1201 12:54:40.814609    2450 secure_serving.go:210] Serving securely on [::]:10259
I1201 12:54:40.814805    2450 tlsconfig.go:240] "Starting DynamicServingCertificateController"
I1201 12:54:40.914977    2450 leaderelection.go:248] attempting to acquire leader lease kube-system/kube-scheduler...
I1201 12:54:40.923268    2450 leaderelection.go:258] successfully acquired lease kube-system/kube-scheduler
```

Mais nous n'avons toujours pas notre *Pod*... Triste panda.

En fait, c'est parce qu'il manque encore beaucoup de choses...
- un runtime de conteneur pour exécuter les conteneurs dans les pods
- un démon `kubelet` pour permettre à Kubernetes d'interagir avec le runtime de conteneur
### Runtime de conteneur

Démarrons le runtime de conteneur `containerd` sur notre machine :

```bash
#create a new tmux session for containerd
'[ctrl]-b' and then ': new -s containerd'
sudo ./containerd
[...]
INFO[2022-12-01T11:03:37.616892592Z] serving...                                    address=/run/containerd/containerd.sock
INFO[2022-12-01T11:03:37.617062671Z] containerd successfully booted in 0.038455s
[...]
```

### kubelet

Démarrons le composant `kubelet`. Il enregistrera notre machine actuelle en tant que *Node*, ce qui permettra aux futurs *Pods* planifiés par le planificateur.

Enfin !

Le rôle du kubelet est également de parler avec containerd pour lancer/monitorer/tuer les conteneurs de nos *Pods*.

```bash
#create a new tmux session for kubelet
'[ctrl]-b' and then ': new -s kubelet'
sudo ./kubelet \
--container-runtime=remote \
--container-runtime-endpoint=unix:///var/run/containerd/containerd.sock \
--fail-swap-on=false \
--kubeconfig admin.conf \
--register-node=true
```

Nous allons obtenir des messages d'erreur nous disant que nous n'avons pas de plugin CNI

```bash
E1211 21:13:22.555830   27332 kubelet.go:2373] "Container runtime network not ready" networkReady="NetworkReady=false reason:NetworkPluginNotReady message:Network plugin returns error: cni plugin not initialized"
E1211 21:13:27.556616   27332 kubelet.go:2373] "Container runtime network not ready" networkReady="NetworkReady=false reason:NetworkPluginNotReady message:Network plugin returns error: cni plugin not initialized"
E1211 21:13:32.558180   27332 kubelet.go:2373] "Container runtime network not ready" networkReady="NetworkReady=false reason:NetworkPluginNotReady message: Network plugin returns error: cni plugin not initialized"
```

### Plugin CNI

Pour gérer le réseau à l'intérieur de Kubernetes, nous avons besoin de quelques dernières choses. Un `kube-proxy` (qui dans certains cas peut être supprimé) et un plugin CNI.

Pour le plugin CNI, j'ai choisi Calico mais il existe de nombreuses autres options. Ici, je déploie simplement le chart et laisse Calico faire la magie.

```bash
helm repo add projectcalico https://projectcalico.docs.tigera.io/charts

kubectl create namespace tigera-operator
helm install calico projectcalico/tigera-operator --version v3.24.5 --namespace tigera-operator
```

### kube-proxy

Démarrons le `kube-proxy` :

```bash
#create a new tmux session for proxy
'[ctrl]-b' and then ': new -s proxy'
sudo ./kube-proxy --kubeconfig admin.conf
```

Ensuite, nous allons créer un service ClusterIP pour obtenir une adresse IP stable (et un équilibreur de charge) pour notre déploiement.

```bash
cat > service.yaml << EOF
apiVersion: v1
kind: Service
metadata:
  labels:
    app: web
  name: web
spec:
  ports:
  - port: 3000
    protocol: TCP
    targetPort: 80
  selector:
    app: web
EOF
kubectl apply -f service.yaml

kubectl get svc
NAME         TYPE        CLUSTER-IP   EXTERNAL-IP   PORT(S)   AGE
kubernetes   ClusterIP   10.0.0.1     <none>        443/TCP   38m
web          ClusterIP   10.0.0.34    <none>        3000/TCP  67s

```

### IngressController

Enfin, pour nous permettre de nous connecter à notre Pod en utilisant une belle URL dans notre navigateur, je vais ajouter un *IngressController* optionnel. Déployons Traefik comme notre ingressController

```bash
helm repo add traefik https://traefik.github.io/charts
"traefik" has been added to your repositories

helm install traefik traefik/traefik
[...]
Traefik Proxy v2.9.5 has been deployed successfully

kubectl get svc
NAME         TYPE           CLUSTER-IP   EXTERNAL-IP   PORT(S)                      AGE
kubernetes   ClusterIP      10.0.0.1     <none>        443/TCP                      58m
traefik      LoadBalancer   10.0.0.86    <pending>     80:31889/TCP,443:31297/TCP   70s
web          ClusterIP      10.0.0.34    <none>        3000/TCP                     21m
```

Remarquez les ports sur la ligne traefik : **80:31889/TCP,443:31297/TCP** dans mon exemple.

À condition que le DNS puisse résoudre domain.tld à l'IP de notre nœud, nous pouvons maintenant accéder à Traefik depuis Internet en utilisant http://domain.tld:31889 (et https://domain.tld:31297).

Mais comment pouvons-nous nous connecter à notre site web ?

En créant un Ingress qui redirige le trafic venant à dk.domain.tld vers notre image docker

```yaml
cat > ingress.yaml << EOF
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: dk
  namespace: default
spec:
  rules:
    - host: dk.domain.tld
      http:
        paths:
          - path: /
            pathType: Exact
            backend:
              service:
                name:  web
                port:
                  number: 3000
EOF
kubectl apply -f ingress.yaml
```

[http://dk.domain.tld:31889/](http://dk.domain.tld:31889/) devrait maintenant être disponible !! Félicitations !

## Jouer avec notre cluster

Jetons ensuite un œil aux iptables générés par `kube-proxy`

```bash
sudo iptables -t nat -L KUBE-SERVICES |grep -v calico
Chain KUBE-SERVICES (2 references)
target     prot opt source               destination
KUBE-SVC-NPX46M4PTMTKRN6Y  tcp  --  anywhere             10.0.0.1             /* default/kubernetes:https cluster IP */ tcp dpt:https
KUBE-SVC-LOLE4ISW44XBNF3G  tcp  --  anywhere             10.0.0.34            /* default/web cluster IP */ tcp dpt:http
KUBE-NODEPORTS  all  --  anywhere             anywhere             /* kubernetes service nodeports; NOTE: this must be the last rule in this chain */ ADDRTYPE match dst-type LOCAL
```

Ici, nous pouvons voir que tout ce qui essaie d'aller à 10.0.0.34 (l'IP de notre **Service** Kubernetes pour nginx) est redirigé vers la règle **KUBE-SVC-LOLE4ISW44XBNF3G**

```bash
sudo iptables -t nat -L KUBE-SVC-LOLE4ISW44XBNF3G
Chain KUBE-SVC-LOLE4ISW44XBNF3G (1 references)
target     prot opt source               destination
KUBE-SEP-3RY52QTAPPWAROT7  all  --  anywhere             anywhere             /* default/web -> 192.168.238.4:80 */
```

En creusant un peu plus, nous pouvons voir que pour l'instant, tout le trafic est dirigé vers la règle appelée **KUBE-SEP-3RY52QTAPPWAROT7**. **SEP** signifie "Service EndPoint"

```bash
sudo iptables -t nat -L KUBE-SEP-3RY52QTAPPWAROT7
Chain KUBE-SEP-3RY52QTAPPWAROT7 (1 references)
target     prot opt source               destination
KUBE-MARK-MASQ  all  --  192.168.238.4        anywhere             /* default/web */
DNAT       tcp  --  anywhere             anywhere             /* default/web */ tcp to:192.168.238.4:80
```

Scalons notre déploiement pour voir ce qui se passe

```bash
kubectl scale deploy web --replicas=4
deployment.apps/web scaled

kubectl get pods -o wide
NAME                   READY   STATUS    RESTARTS   AGE   IP              NODE                           NOMINATED NODE   READINESS GATES
web-8667899c97-8dsp7   1/1     Running   0          10s   192.168.238.6   instance-2022-12-01-15-47-29   <none>           <none>
web-8667899c97-jvwbl   1/1     Running   0          10s   192.168.238.5   instance-2022-12-01-15-47-29   <none>           <none>
web-8667899c97-s4sjg   1/1     Running   0          10s   192.168.238.7   instance-2022-12-01-15-47-29   <none>           <none>
web-8667899c97-vvqb7   1/1     Running   0          43m   192.168.238.4   instance-2022-12-01-15-47-29   <none>           <none>
```

Les règles iptables sont mises à jour en conséquence, avec une probabilité aléatoire d'être sélectionnées

```bash
sudo iptables -t nat -L KUBE-SVC-LOLE4ISW44XBNF3G
Chain KUBE-SVC-LOLE4ISW44XBNF3G (1 references)
target     prot opt source               destination
KUBE-SEP-3RY52QTAPPWAROT7  all  --  anywhere             anywhere             /* default/web -> 192.168.238.4:80 */ statistic mode random probability 0.25000000000
KUBE-SEP-XDYZG4GSYEXZWWXS  all  --  anywhere             anywhere             /* default/web -> 192.168.238.5:80 */ statistic mode random probability 0.33333333349
KUBE-SEP-U3XU475URPOLV25V  all  --  anywhere             anywhere             /* default/web -> 192.168.238.6:80 */ statistic mode random probability 0.50000000000
KUBE-SEP-XLJ4FHFV6DVOXHKZ  all  --  anywhere             anywhere             /* default/web -> 192.168.238.7:80 */
```

## La fin

Maintenant, vous devriez avoir un "cluster Kubernetes à un nœud" fonctionnel.

### Nettoyage

Vous devriez vider le répertoire `/var/lib/kubelet` et supprimer les binaires `/usr/bin/runc` et `/usr/local/bin/kubectl`

Si vous souhaitez relancer le laboratoire, videz également le répertoire etcd-data ou même tout le dossier demystifions-kubernetes et `git clone` à nouveau.

## Ressources similaires

* Jérôme Petazzoni's [dessine-moi-un-cluster](https://github.com/jpetazzo/dessine-moi-un-cluster)
* Kelsey Hightower's [kubernetes the hard way](https://github.com/kelseyhightower/kubernetes-the-hard-way)
