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
# suppression des apts qu pourraient entrer en conflit
for pkg in docker.io docker-doc docker-compose docker-compose-v2 podman-docker containerd runc; do sudo apt-get remove $pkg; done
# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" |  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin


# curl -fsSL https://get.docker.com | sh;
sudo usermod -aG docker $USER
sudo chmod 644 /etc/group

echo "dockremap:500000:65536" >> /etc/subuid && echo "dockremap:500000:65536" >> sudo /etc/subgid
echo "dockremap:500000:65536" | sudo tee -a /etc/subuid
echo "dockremap:500000:65536" | sudo tee -a /etc/subgid

sudo nano /etc/docker/daemon.json
systemctl daemon-reload && systemctl restart docker

sudo nano /etc/docker/daemon.json

{
"exec-opts":["native.cgroupdriver=systemd"]
}


systemctl daemon-reload && systemctl restart docker
sudo swapoff -a

sudo nano /etc/fstab
# commenter la ligne
#/swapfile                                 none            swap    sw              0       0

# Avant l’init.
# Edition sur les deux machines :
sudo nano /etc/containerd/config.toml
# Changer disabled_plugins = ["cri"] par
enabled_plugins = ["cri"]
sudo  systemctl restart containerd.service




```

## installation kubernetes


```bash
#  install kube
sudo apt-get update && sudo apt-get install -y apt-transport-https curl

curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.30/deb/Release.key | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpg
echo 'deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.30/deb/ /' | sudo tee /etc/apt/sources.list.d/kubernetes.list

sudo chmod 644 /etc/apt/sources.list.d/kubernetes.list

# curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
# sudo add-apt-repository "https://apt.kubernetes.io/ kubernetes-xenial main"

sudo nano /etc/apt/sources.list.d/kubernetes.list
ll /etc/apt/sources.list
sudo nano /etc/apt/sources.list

sudo apt-get update
sudo apt-get install -y kubectl

echo 'source <(kubectl completion bash)' >> ~/.bashrc
echo 'alias k=kubectl' >> ~/.bashrc
echo 'complete -o default -F __start_kubectl k' >> ~/.bashrc
source ~/.bashrc

sudo apt-get install -y kubelet kubeadm kubectl
# sudo nano /etc/apt/sources.list.d/kubernetes.list

# sudo rm /etc/apt/sources.list.d/kubernetes.list
# sudo nano /etc/apt/sources.list.d/kubernetes.list
# sudo apt-get update
# sudo apt-get install -y apt-transport-https ca-certificates curl

# curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
# echo "deb https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list

# sudo nano /etc/apt/sources.list.d/kubernetes.list
```

### Autre solution pour installer kubelet on peut utiliser snap

```shell

# sudo apt-get update
kubectl version --client
kubeadm version
kubelet --version

sudo snap install kubectl
sudo snap install kubectl --classic
sudo snap install kubeadm --classic
sudo snap install kubelet --classic
export PATH=$PATH:/snap/bin
echo 'export PATH=$PATH:/snap/bin' >> ~/.bashrc
source ~/.bashrc


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
enabled_plugins = ["cri"]
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
#(installation protocole reseaux des pods)
kubectl apply -f https://github.com/coreos/flannel/raw/master/Documentation/kube-flannel.yml

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

# sudo snap start kubelet && sudo snap services kubelet

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
#sudo mkdir -p /etc/systemd/system/kubelet.service.d/  #si le fichier n'existe pas il faut le créer

sudo nano /etc/systemd/system/kubelet.service.d/10-kubeadm.conf

[Service]
Environment="KUBELET_EXTRA_ARGS=--node-ip=192.168.1.178 --cgroup-driver=systemd"
Environment="KUBELET_KUBECONFIG_ARGS=--kubeconfig=/etc/kubernetes/kubelet.conf"
Environment="KUBELET_CONFIG_ARGS=--config=/var/lib/kubelet/config.yaml"
Environment="KUBELET_NETWORK_PLUGIN_ARGS=--network-plugin=cni"
ExecStart=
ExecStart=/usr/bin/kubelet $KUBELET_EXTRA_ARGS $KUBELET_KUBECONFIG_ARGS $KUBELET_CONFIG_ARGS $KUBELE>

sudo systemctl daemon-reload
sudo systemctl restart kubelet
sudo systemctl status kubelet




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

# install etcd
sudo apt-get update
sudo apt-get install -y etcd
sudo mkdir -p /var/lib/etcd/default
sudo chown -R etcd:etcd /var/lib/etcd
sudo dpkg --configure -a

sudo nano /etc/etcd/etcd.conf.yml

'
name: 'master'
data-dir: /var/lib/etcd
initial-cluster-state: 'new'
initial-cluster-token: 'etcd-cluster'
initial-cluster: 'master=https://192.168.1.79:2380'
initial-advertise-peer-urls: 'https://192.168.1.79:2380'
listen-peer-urls: 'https://192.168.1.79:2380'
listen-client-urls: 'https://127.0.0.1:2379,https://192.168.1.79:2379'
advertise-client-urls: 'https://192.168.1.79:2379'

'
sudo systemctl enable etcd
sudo systemctl start etcd
sudo systemctl status etcd
sudo systemctl restart kubelet
sudo systemctl restart etcd

sudo systemctl status etcd



sudo kubeadm init --apiserver-advertise-address=192.168.1.79 --node-name $HOSTNAME --pod-network-cidr=10.244.0.0/16 --ignore-preflight-errors=FileAvailable--etc-kubernetes-manifests-kube-apiserver.yaml,Port-10250

###-- FIN INIT KO ------------------

# si echec de l'init il faut nettoyer tout ce que la tentative à créée
sudo rm -f /etc/kubernetes/manifests/kube-apiserver.yaml
sudo rm -f /etc/kubernetes/manifests/kube-controller-manager.yaml
sudo rm -f /etc/kubernetes/manifests/kube-scheduler.yaml
sudo rm -f /etc/kubernetes/manifests/etcd.yaml
sudo lsof -i :2379
sudo lsof -i :2380
sudo lsof -i :10250
sudo fuser -k 10250/tcp
sudo systemctl stop etcd
sudo systemctl stop kubelet
sudo rm -rf /var/lib/etcd/*
sudo kubeadm reset -f

# relancer le init
sudo kubeadm init --apiserver-advertise-address=192.168.1.79 --node-name $HOSTNAME --pod-network-cidr=10.244.0.0/16 --ignore-preflight-errors=FileAvailable--etc-kubernetes-manifests-kube-apiserver.yaml,Port-10250



# WORKER
# depuis le master copier le fichier config sur le worker
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

# sur le worker le config doit ressembler à :
apiVersion: v1
clusters:
- cluster:
    server: https://192.168.1.79:6443
  name: kubernetes
contexts:
- context:
    cluster: kubernetes
    user: system:node:worker1
  name: system:node:worker1@kubernetes
current-context: system:node:worker1@kubernetes
kind: Config
users:
- name: system:node:worker1
  user:
    client-certificate-data: ...
    client-key-data: ...

# sur le worker
sudo nano /var/lib/kubelet/config.yaml
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
podInf
"

sudo nano /etc/kubernetes/kubelet.conf
# copie le fichier kubeconfig depuis le maître ou exécute kubeadm join pour le créer automatiquement.




```

## -----------------DEBUG OK pour le init fonctionnel -------------------------

```Shell

sudo systemctl stop kubelet
sudo systemctl disable kubelet
sudo fuser -k 10250/tcp
sudo systemctl stop kubelet
sudo systemctl disable kubelet
# sudo systemctl list-units --type=service --state=running
sudo kubeadm reset
sudo systemctl stop snap.kubelet.daemon.service
sudo systemctl disable snap.kubelet.daemon.service
sudo fuser -k 10250/tcp
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
# kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
kubectl apply -f https://github.com/flannel-io/flannel/raw/master/Documentation/kube-flannel.yml

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
sudo systemctl enable kubelet
sudo kubeadm join <IP_MASTER>:6443 --token <TOKEN> --discovery-token-ca-cert-hash sha256:<HASH>
# Remplacez <TOKEN> et <HASH> par les valeurs fournies lors de l'initialisation.
sudo kubeadm join 192.168.1.79:6443 --token 6aep37.psqrv7j4g1bytql3 --discovery-token-ca-cert-hash sha256:3945b98fc1eefdd9bb6c1b8279de39d96de7f98d1994e25c949def994c6fd7f8 --timeout=10m0s
```

## 10 Vérification de l'installation

- Pour vérifier que le cluster fonctionne correctement :

```Shell
kubectl get nodes
kubectl get pods --all-namespaces
# pour voir en live l'evolution des pods on peut aussi faire
watch kubectl get pods --all-namespaces
```

## Déploiement d'une application simple

- Pour tester votre cluster, déployez une application simple comme Nginx :

```Shell
kubectl create deployment nginx --image=nginx
kubectl expose deployment nginx --port=80 --type=NodePort
kubectl get svc
```

### Debug probleme de connexion cela vient surement du modprobe br_netfilter

```Shell
# errreur E1104 09:19:34.403049       1 main.go:267] Failed to check br_netfilter: stat /proc/sys/net/bridge/bridge-nf-call-iptables: no such file or directory

sudo modprobe br_netfilter
lsmod | grep br_netfilter
echo "br_netfilter" | sudo tee /etc/modules-load.d/k8s.conf
cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
net.ipv4.ip_forward = 1
EOF
sudo sysctl --system
sudo systemctl restart kubelet
kubectl delete pod kube-flannel-ds-lztxk -n kube-flannel
kubectl get pods -n kube-system
kubectl get pods -n kube-flannel

```

### Nettoyage

```Shell
sudo fuser -k 10250/tcp | sudo fuser -k 10250/tcp  | sudo kubeadm reset

sudo fuser -k 10250/tcp
sudo kubeadm reset
sudo rm -rf /etc/kubernetes
sudo rm -rf /var/lib/etcd
sudo rm -rf /var/lib/kubelet
sudo rm -rf /var/lib/dockershim
sudo rm -rf /etc/cni/net.d
sudo iptables -F
sudo iptables -t nat -F
sudo iptables -t mangle -F
sudo iptables -X
sudo ipvsadm --clear
sudo ip link delete cni0
sudo ip link delete flannel.1
ps aux | grep kube
sudo pkill kubelet
sudo pkill kube-proxy
sudo pkill kube
sudo docker rm -f $(sudo docker ps -a -q)
CONTAINERS=$(sudo docker ps -a -q)
if [ -n "$CONTAINERS" ]; then   sudo docker rm -f $CONTAINERS; else   echo "Aucun conteneur à supprimer."; fi
sudo systemctl stop kubelet
sudo systemctl disable kubelet
sudo fuser -k 10250/tcp
sudo fuser -k 10250/tcp

# suppression de kube via apt et snap

sudo apt-get purge -y kubelet kubeadm kubectl
sudo apt-get autoremove -y
sudo apt-get clean
sudo rm -rf /etc/kubernetes
sudo rm -rf /var/lib/kubelet
sudo rm /etc/systemd/system/kubelet.service
sudo rm -rf /etc/systemd/system/kubelet.service.d/
sudo rm /usr/local/bin/kubectl
sudo rm /usr/local/bin/kubeadm
sudo rm /usr/local/bin/kubelet

#snap
sudo rm -rf /etc/kubernetes
sudo rm -rf /var/lib/kubelet
sudo rm -rf /var/lib/etcd
sudo rm -rf /etc/cni
sudo snap remove kubelet
sudo snap remove kubectl
sudo snap remove kubeadm
sudo snap remove kubelet

ls /etc/systemd/system/ | grep kubelet
sudo systemctl daemon-reload
which kubectl
which kubeadm
which kubelet


```