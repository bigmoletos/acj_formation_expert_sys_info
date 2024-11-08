# Installation d'une nouvelle VM ubuntu

## ajout droit sudo au user

```bash
su -
usermod -aG sudo master
echo "$USER ALL=(ALL:ALL) ALL" | sudo tee -a /etc/sudoers.d/$USER

```

## obtenir l'IP de la vm

```shell

ip route get 1.1.1.1 | awk '{print $7}'

```

## obtenir l'IP du gateway  de la vm

```shell

ip route | grep default | awk '{print $3}'

```

## Désactivation du swap

```shell
sudo swapoff -a
sudo sed -i '/^\/swapfile/s/^/# /' /etc/fstab

# commenter la ligne
#/swapfile                                 none            swap    sw              0       0

```

## configuration de containerd

(/etc/containerd/config.toml), confirme que le pilote de cgroups est également défini sur systemd
Changer disabled_plugins = ["cri"] par enabled_plugins = ["cri"]

```shell
# sudo nano /etc/containerd/config.toml

# enabled_plugins = ["cri"]

# [plugins."io.containerd.grpc.v1.cri".containerd.runtimes.runc.options]
#   SystemdCgroup = true

#   en 1 seule commande
sudo sed -i '/disabled_plugins = \["cri"\]/d; /disabled_plugins = \[\]/d' /etc/containerd/config.toml && echo 'enabled_plugins = ["cri"]' | sudo tee -a /etc/containerd/config.toml > /dev/null && sudo tee -a /etc/containerd/config.toml > /dev/null <<EOF

[plugins."io.containerd.grpc.v1.cri".containerd.runtimes.runc.options]
  SystemdCgroup = true
EOF

# verification
sudo cat /etc/containerd/config.toml

sudo systemctl restart containerd


```

## mise à jour et installation des apt

```shell

sudo apt update && sudo apt upgrade -y
for pkg in ca-certificates curl net-tools build-essential libncursesw5-dev libncurses-dev autoconf autoconf-archive automake make m4 gdb lcov pkg-config libbz2-dev libffi-dev libgdbm-dev libgdbm-compat-dev liblzma-dev libncurses5-dev libreadline6-dev libsqlite3-dev libssl-dev lzma lzma-dev tk-dev uuid-dev zlib1g-dev unzip ssh ufw htop dos2unix sshpass ansible apt-transport-https base-passwd conntrack dash diffutils ethtool findutils gnupg grep grub2-common gzip hostname hyphen-en-us init ipvsadm language-pack-fr language-pack-en-base language-pack-gnome-fr language-pack-gnome-fr-base libdebconfclient0 libfprint-2-tod1 libfwupdplugin1 libllvm9 libxmlb1 linux-generic-hwe-20.04 mythes-en-us ncurses-base ncurses-bin os-prober software-properties-common ssh terminator ubuntu-desktop-minimal ubuntu-minimal; do
    sudo apt-get install -y $pkg || echo "Échec d'installation pour $pkg"
done

# sudo apt-get install ca-certificates curl
# sudo apt install net-tools build-essential libncursesw5-dev libncurses-dev autoconf autoconf-archive automake make  m4 build-essential gdb lcov pkg-config   libbz2-dev libffi-dev libgdbm-dev libgdbm-compat-dev liblzma-dev   libncurses5-dev libreadline6-dev libsqlite3-dev libssl-dev  lzma lzma-dev tk-dev uuid-dev zlib1g-dev unzip  ssh ufw htop dos2unix sshpass  ansible apt-transport-https base-passwd ca-certificates conntrack curl dash diffutils ethtool findutils  gnupg grep grub2-common  gzip hostname htop hyphen-en-us init ipvsadm language-pack-fr language-pack-en-base language-pack-gnome-fr language-pack-gnome-fr-base libdebconfclient0 libfprint-2-tod1 libfwupdplugin1 libllvm9  libxmlb1 linux-generic-hwe-20.04 mythes-en-us ncurses-base ncurses-bin  os-prober software-properties-common ssh terminator  ubuntu-desktop-minimal ubuntu-minimal  -y

sudo apt update && sudo apt upgrade -y

```

## installation docker

```bash
# suppression des apts qu pourraient entrer en conflit
for pkg in docker.io docker-doc docker-compose docker-compose-v2 podman-docker containerd runc; do sudo apt-get remove $pkg; done
# Add Docker's official GPG key:
sudo apt-get update && sudo apt-get install -y ca-certificates curl && sudo install -m 0755 -d /etc/apt/keyrings && sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc && sudo chmod a+r /etc/apt/keyrings/docker.asc

# sudo apt-get update
# sudo apt-get install ca-certificates curl
# sudo install -m 0755 -d /etc/apt/keyrings
# sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
# sudo chmod a+r /etc/apt/keyrings/docker.asc

# https://docs.docker.com/engine/install/ubuntu/
# Add the repository to Apt sources:
echo  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" |  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
sudo apt-get install cri-tools docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin


# sudo snap install kube-apiserver --classic


# curl -fsSL https://get.docker.com | sh;
sudo usermod -aG docker $USER
sudo chmod 644 /etc/group

echo "dockremap:500000:65536" >> /etc/subuid && echo "dockremap:500000:65536" >> sudo /etc/subgid
echo "dockremap:500000:65536" | sudo tee -a /etc/subuid
echo "dockremap:500000:65536" | sudo tee -a /etc/subgid

systemctl daemon-reload && systemctl restart docker

# sudo nano /etc/docker/daemon.json

# {
# "exec-opts":["native.cgroupdriver=systemd"]
# }

sudo sh -c 'echo "{\"exec-opts\": [\"native.cgroupdriver=systemd\"]}" > /etc/docker/daemon.json'
#  verification
sudo cat /etc/docker/daemon.json

systemctl daemon-reload && systemctl restart docker

```

## installation kubernetes

```shell

# suppression des paquets kubeernetes installés par snap qu pourraient entrer en conflit
for pkg in kubectl kube-apiserver kubelet kubeadm etcd ; do sudo snap  remove $pkg; done
for dir in /etc/kubernetes /var/lib/kubelet /var/lib/etcd /etc/cni; do sudo rm -rf "$dir" && echo "$dir supprimé avec succès" || echo "Erreur lors de la suppression de $dir"; done

# Add Docker's official GPG key:
# sudo rm -rf /etc/kubernetes
# sudo rm -rf /var/lib/kubelet
# sudo rm -rf /var/lib/etcd
# sudo rm -rf /etc/cni
# sudo snap remove kubelet
# sudo snap remove kubectl
# sudo snap remove kubeadm
# sudo snap remove kube-apiserver kubelet kubectl kubeadm


# installation kube
sudo apt update
sudo apt install -y virtualbox virtualbox-ext-pack
export PATH=$PATH:/usr/bin

VERSION="v1.25.0"  # ou la dernière version disponible
wget https://github.com/kubernetes-sigs/cri-tools/releases/download/$VERSION/crictl-$VERSION-linux-amd64.tar.gz
sudo tar zxvf crictl-$VERSION-linux-amd64.tar.gz -C /usr/local/bin
rm crictl-$VERSION-linux-amd64.tar.gz
crictl --version


sudo apt install -y curl apt-transport-https
curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
chmod +x minikube
sudo mv minikube /usr/local/bin/

curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
chmod +x kubectl
sudo mv kubectl /usr/local/bin/
minikube start --driver=virtualbox

curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
ls -lh kubectl
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubeadm"
ls -lh kubeadm
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubelet"
ls -lh kubelet
chmod +x kubeadm kubelet kubectl
sudo mv kubeadm kubelet kubectl /usr/local/bin/

kubeadm version
kubectl version --client
kubelet --version

sudo tee /etc/systemd/system/kubelet.service > /dev/null <<EOF
[Unit]
Description=kubelet: The Kubernetes Node Agent
Documentation=https://kubernetes.io/docs/
After=network.target

[Service]
ExecStart=/usr/local/bin/kubelet
Restart=always
StartLimitInterval=0
RestartSec=10

[Install]
WantedBy=multi-user.target
EOF

sudo mkdir -p /etc/default
sudo tee /etc/default/kubelet > /dev/null <<EOF
KUBELET_EXTRA_ARGS="--container-runtime=remote --container-runtime-endpoint=unix:///var/run/containerd/containerd.sock"
EOF
sudo systemctl daemon-reload
sudo systemctl enable kubelet
sudo systemctl stop kubelet
sudo systemctl status kubelet


# relancer le init
# sudo kubeadm init --apiserver-advertise-address=192.168.1.79 --node-name $HOSTNAME --pod-network-cidr=10.244.0.0/16 --ignore-preflight-errors=FileAvailable--etc-kubernetes-manifests-kube-apiserver.yaml,Port-10250
IP=$(hostname -I | awk '{print $1}')
echo $IP - $HOSTNAME
sudo kubeadm init --apiserver-advertise-address=$IP --node-name $HOSTNAME --pod-network-cidr=10.244.0.0/16 --ignore-preflight-errors=FileAvailable--etc-kubernetes-manifests-kube-apiserver.yaml

sudo systemctl start kubelet

```

## si erreur lors du kubeadm init

```shell

sudo systemctl stop kubelet
sudo rm -rf /etc/kubernetes/

sudo rm -rf /etc/kubernetes/manifests/*
sudo rm -rf /etc/kubernetes/manifests/kube-apiserver.yaml
sudo rm -rf /etc/kubernetes/manifests/kube-controller-manager.yaml
sudo rm -rf /etc/kubernetes/manifests/kube-scheduler.yaml
sudo rm -rf /etc/kubernetes/manifests/etcd.yaml
sudo rm -rf /var/lib/etcd
# sudo rm -rf /var/lib/kubelet
sudo rm -rf /etc/cni/net.d

sudo lsof -i :10259
sudo lsof -i :10257
sudo lsof -i :10250
sudo lsof -i :2379
sudo lsof -i :2380
sudo fuser -k 10250/tcp
sudo kubeadm reset -f

# si besoin
sudo kill -9   <pid>

sudo mkdir -p /var/lib/kubelet


sudo systemctl start kubelet

```