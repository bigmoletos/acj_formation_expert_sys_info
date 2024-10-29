# Installation kubernetes
* Recommandations :

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
```bash
# mettre master sur une des machines et worker sur l'autre
sudo nano /etc/hostname
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
sudo kubeadm init --apiserver-advertise-address=192.168.1.79 --node-name $HOSTNAME --pod-network-cidr=10.244.0.0/16
# 192.168.1.79 etant l’ip de mon master
# SUR LE MASTER :
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

# Puis : sur les deux machines
modprobe br_netfilter
sysctl net.bridge.bridge-nf-call-iptables=1
# SUR LA MASTER :
kubectl apply -f https://github.com/coreos/flannel/raw/master/Documentation/kube-flannel.yml (installation protocole reseaux des pods)

# Pour vérifier sur le master qui est notre machine de control :
kubectl get pods --all-namespaces
kubectl get nodes

Pour joindre le worker au cluster, sur le worker exécuter le kubeadm join donner à la fin de l’init.

kubeadm join 192.168.1.200:6443 ………
```