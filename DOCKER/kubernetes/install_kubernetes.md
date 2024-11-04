# Installation kubernetes sur VM UBUNTU

## Recommandations

```bash
2 Gb ram
2 CPU
ouverture réseau large entre les 2 machines
Ports master : 6443 2379-2380 10250 10251 10252
Ports node : 10250 30000-32767
pas de swap
```

## ajout droit sudo au user

```bash
su -
usermod -aG sudo master
visudo
# ajouter
master ALL=(ALL:ALL) ALL
exit
```

## pre-requis Installation kubernetes

```bash
# mettre master sur une des machines et worker sur l'autre
sudo nano /etc/hostname
# pour appliquer le nouveau hostname
exec bash

#  rajouter les ip master et worker dans le fichier hosts à faire sur les 2 VM
sudo nano /etc/hosts


# 127.0.0.1 localhost
# 192.167.1.79 master
# 192.168.1.178  worker

# 127.0.1.1       ubuntu.myguest.virtualbox.org   ubuntu

# # The following lines are desirable for IPv6 capable hosts
# ::1     ip6-localhost ip6-loopback
# fe00::0 ip6-localnet
# ff00::0 ip6-mcastprefix
# ff02::1 ip6-allnodes
# ff02::2 ip6-allrouters

```

## installation docker

```bash
curl -fsSL https://get.docker.com | sh;
sudo usermod -aG docker $USER
sudo chmod 644 /etc/group
echo "dockremap:500000:65536" >> /etc/subuid && echo "dockremap:500000:65536" >>/etc/subgid
echo "dockremap:500000:65536" | sudo tee -a /etc/subuid
echo "dockremap:500000:65536" | sudo tee -a /etc/subgid
sudo nano /etc/docker/daemon.json
systemctl daemon-reload && systemctl restart docker

sudo nano /etc/docker/daemon.json
{
"exec-opts":["native.cgroupdriver=systemd"]
}


systemctl daemon-reload && systemctl restart docker
```

## installation kubernetes


```bash
sudo nano /etc/fstab
sudo swapoff -a

sudo nano /etc/fstab
# commenter la ligne
#/swapfile                                 none            swap    sw              0       0

sudo apt-get update && sudo apt-get install -y apt-transport-https curl
curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
sudo add-apt-repository "https://apt.kubernetes.io/ kubernetes-xenial main"
sudo nano /etc/apt/sources.list.d/kubernetes.list
ll /etc/apt/sources.list
sudo nano /etc/apt/sources.list
sudo nano /etc/apt/sources.list.d/kubernetes.list

sudo rm /etc/apt/sources.list.d/kubernetes.list
sudo nano /etc/apt/sources.list.d/kubernetes.list
sudo apt-get update
sudo apt-get install -y apt-transport-https ca-certificates curl
curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list

sudo nano /etc/apt/sources.list.d/kubernetes.list
sudo apt-get update
sudo apt-get install -y kubelet kubeadm kubectl
kubectl version --client
kubeadm version
kubelet --version
sudo snap install kubectl
sudo snap install kubectl --classic
sudo snap install kubeadm --classic
sudo snap install kubelet --classic
kubectl version --client
kubeadm version
kubelet --version

# relancer kubelet
sudo snap start kubelet && sudo snap services kubelet

## Initialisation de kubernetes sur la vm master

```bash
# sequence complete :
# Avant l’init.
# Edition sur les deux machines :
sudo nano /etc/containerd/config.toml
# Changer disabled_plugins = ["cri"] par
enabled_plugins = [« cri »]
# Puis restart :
sudo systemctl restart containerd.service
# Ensuite INIT : SUR LE MASTER
# relancer kubelet
sudo snap start kubelet && sudo snap services kubelet
# initialiser la sessio kubadmin
sudo kubeadm init --apiserver-advertise-address=192.168.1.79 --node-name $HOSTNAME --pod-network-cidr=10.244.0.0/16





# 192.168.1.79 etant l’ip de mon master
# SUR LE MASTER :
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

# Puis : sur les deux machines
# relancer kubelet
sudo snap start kubelet && sudo snap services kubelet
# si probleme de connexion on peut aussi faire:
sudo systemctl daemon-reload


# sur les MASTER et WORKER
sudo modprobe br_netfilter
sudo sysctl net.bridge.bridge-nf-call-iptables=1
# SUR LA MASTER :
kubectl apply -f https://github.com/coreos/flannel/raw/master/Documentation/kube-flannel.yml (installation protocole reseaux des pods)

# Pour vérifier sur le master qui est notre machine de control :
kubectl get pods --all-namespaces
kubectl get nodes

## Pour joindre le worker au cluster, sur le worker exécuter le kubeadm join donner à la fin de l’init.

kubeadm join 192.168.1.200:6443 ………
```

## DEBUG INIT kKUBEADM

```Sh
###-- Si INIT ne se fait pas ------------
echo "deb [signed-by=/usr/share/keyrings/cloud.google.gpg] https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list
sudo apt-get update
sudo apt-get install -y kubelet kubeadm kubectl
sudo apt-get install -y apt-transport-https ca-certificates curl gnupg
sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.31/deb/Release.key | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpg
sudo chmod 644 /etc/apt/keyrings/kubernetes-apt-keyring.gpg
echo "deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.31/deb/ /" | sudo tee /etc/apt/sources.list.d/kubernetes.list
sudo chmod 644 /etc/apt/sources.list.d/kubernetes.list
sudo apt-get update
sudo apt-get install -y kubelet kubeadm kubectl
sudo snap start kubelet && sudo snap services kubelet

# ajouter dans /var/lib/kubelet/config.yaml
sudo nano /var/lib/kubelet/config.yaml
containerRuntimeEndpoint: "unix:///var/run/containerd/containerd.sock"  # Ajouté
podInfraContainerImage: "k8s.gcr.io/pause:3.8"  # Ajouté
#---  Pour modifier le fichier yaml on peut aussi le faire automatiquement ---
# Met à jour ou ajoute containerRuntimeEndpoint
sudo sed -i '/^containerRuntimeEndpoint:/c\containerRuntimeEndpoint: "unix:///var/run/containerd/containerd.sock"' /var/lib/kubelet/config.yaml
# Met à jour ou ajoute podInfraContainerImage
sudo sed -i '/^podInfraContainerImage:/c\podInfraContainerImage: "k8s.gcr.io/pause:3.8"' /var/lib/kubelet/config.yaml
# Met à jour ou ajoute cgroupDriver
sudo sed -i '/^cgroupDriver:/c\cgroupDriver: systemd' /var/lib/kubelet/config.yaml
#  verification
cat /var/lib/kubelet/config.yaml | grep -E 'containerRuntimeEndpoint|podInfraContainerImage|cgroupDriver'
# /var/lib/kubelet/config.yaml:
"
kind: KubeletConfiguration
apiVersion: kubelet.config.k8s.io/v1beta1
cgroupDriver: systemd
containerRuntimeEndpoint: "unix:///var/run/containerd/containerd.sock"
podInfraContainerImage: "k8s.gcr.io/pause:3.8"
"

sudo chown root:root /var/lib/kubelet/config.yaml
sudo chmod 644 /var/lib/kubelet/config.yaml
sudo systemctl stop kubelet
sudo systemctl disable kubelet
#---  FIN modification du fichier config.yaml ---


# ensuite Redémarrer le Service kubelet
sudo systemctl daemon-reload
sudo systemctl restart kubelet


sudo kubeadm reset
sudo lsof -i :10250   //recuperer le PID
sudo kill -9 10471
# à la place de ces 2 commandes on peut faire:
sudo fuser -k 10250/tcp

sudo systemctl stop snap.kubelet.daemon.service
sudo systemctl disable snap.kubelet.daemon.service
sudo systemctl stop kubelet
sudo systemctl disable kubelet

sudo systemctl restart kubelet
sudo kubeadm init --apiserver-advertise-address=192.168.1.79 --node-name $HOSTNAME --pod-network-cidr=10.244.0.0/16 --ignore-preflight-errors=FileAvailable--etc-kubernetes-manifests-kube-apiserver.yaml,Port-10250

###-- FIN INIT KO ------------------

```

## -----------------DEBUG OK pour le init fonctionnel -------------------------

```Shell

sudo systemctl stop kubelet
sudo systemctl disable kubelet
sudo fuser -k 10250/tcp
sudo systemctl stop kubelet
sudo systemctl disable kubelet
sudo systemctl list-units --type=service --state=running
sudo kubeadm reset
sudo systemctl stop snap.kubelet.daemon.service
sudo systemctl disable snap.kubelet.daemon.service
sudo fuser -k 10250/tcp
sudo kubeadm reset
sudo kubeadm init --pod-network-cidr=10.244.0.0/16 --apiserver-advertise-address=192.168.1.79

```

### l'init nous donne

```Shell
kubeadm join 192.168.1.79:6443 --token 6aep37.psqrv7j4g1bytql3 --discovery-token-ca-cert-hash sha256:3945b98fc1eefdd9bb6c1b8279de39d96de7f98d1994e25c949def994c6fd7f8

# Pour obtenir le token et le hash :
kubeadm token list
# Pour creer un nouveau token :
kubeadm token create --print-join-command
# Pour obtenir le hash :
openssl x509 -in /etc/kubernetes/pki/ca.crt -noout -pubkey | openssl rsa -pubin -outform DER 2>/dev/null | sha256sum | cut -d' ' -f1
```

## ----------------- FIN DEBUG OK -------------------------

### Configuration de kubectl

```Shell
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

```

## 8. Installation d'un plugin réseau (par exemple Flannel)

```Shell
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
```
## -----------------  DEBUG FLANNEL OK -------------------------

```Shell
kubectl delete -f https://raw.githubusercontent.com/flannel-io/flannel/master/Documentation/kube-flannel.yml
# Suppression du namespace
kubectl delete namespace kube-flannel
# Nettoyage des fichiers Flannel
sudo rm -rf /etc/cni/net.d/10-flannel*
sudo rm -rf /run/flannel
# Suppression de Calico
kubectl delete -f https://raw.githubusercontent.com/projectcalico/calico/v3.25.0/manifests/calico.yaml
# Suppression des CRDs Calico
kubectl delete crd felixconfigurations.crd.projectcalico.org
kubectl delete crd bgpconfigurations.crd.projectcalico.org
kubectl delete crd ippools.crd.projectcalico.org
kubectl delete crd ipamblocks.crd.projectcalico.org
kubectl delete crd blockaffinities.crd.projectcalico.org
kubectl delete crd hostendpoints.crd.projectcalico.org
kubectl delete crd clusterinformations.crd.projectcalico.org
kubectl delete crd networkpolicies.crd.projectcalico.org
kubectl delete crd networksets.crd.projectcalico.org
# Suppression des configurations CNI existantes
sudo rm -rf /etc/cni/net.d/*
sudo rm -rf /var/lib/cni/
# Application de la configuration Flannel
kubectl apply -f https://raw.githubusercontent.com/flannel-io/flannel/master/Documentation/kube-flannel.yml
sudo systemctl restart kubelet
# Vérification des pods
kubectl get pods -n kube-flannel
# Vérification des logs
kubectl get nodes -o wide
# Vérifiez que le DaemonSet Flannel est correctement déployé
kubectl get daemonset -n kube-flannel

```

## ----------------- FIN DEBUG FLANNEL OK -------------------------



## 9 Ajout des Worker Nodes au Cluster

-  Sur chaque nœud worker, exécutez la commande fournie à la fin de l'initialisation du master :

```Shell
sudo kubeadm join <IP_MASTER>:6443 --token <TOKEN> --discovery-token-ca-cert-hash sha256:<HASH>
# Remplacez <TOKEN> et <HASH> par les valeurs fournies lors de l'initialisation.
sudo kubeadm join 192.168.1.79:6443 --token 6aep37.psqrv7j4g1bytql3 --discovery-token-ca-cert-hash sha256:3945b98fc1eefdd9bb6c1b8279de39d96de7f98d1994e25c949def994c6fd7f8
```

## 10 Vérification de l'installation

- Pour vérifier que le cluster fonctionne correctement :

```Shell
kubectl get nodes
kubectl get pods --all-namespaces
```

## Déploiement d'une application simple
- Pour tester votre cluster, déployez une application simple comme Nginx :
```Shell
kubectl create deployment nginx --image=nginx
kubectl expose deployment nginx --port=80 --type=NodePort
kubectl get svc
```


```Shell
```
