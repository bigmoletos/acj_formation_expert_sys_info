# Cheat Sheet pour Installer Kubernetes sur une Nouvelle VM

## Prérequis

- Une VM avec Ubuntu (ou une distribution Linux compatible).
- Accès root ou sudo.
- Connexion Internet.

## Étapes d'Installation

### 1. Mise à jour et installation des dépendances

```bash
sudo apt update
sudo apt install -y apt-transport-https ca-certificates curl

2. Installation de Docker
bash
sudo apt install -y docker.io
sudo systemctl enable --now docker

3. Ajout de la clé et du dépôt Kubernetes
bash
curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list
sudo apt update

4. Installation de kubeadm, kubelet et kubectl
bash
sudo apt install -y kubeadm kubelet kubectl
sudo systemctl enable --now kubelet

5. Désactivation du swap
bash
sudo swapoff -a
sudo sed -i '/ swap / s/^$$.*$$$/#\1/g' /etc/fstab

6. Initialisation du Master Node
bash
sudo kubeadm init --pod-network-cidr=10.244.0.0/16 --apiserver-advertise-address=<IP_MASTER>

Remplacez <IP_MASTER> par l'adresse IP de votre nœud master.
7. Configuration de kubectl
bash
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

8. Installation d'un plugin réseau (par exemple Flannel)
bash
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml

9. Ajout des Worker Nodes au Cluster
Sur chaque nœud worker, exécutez la commande fournie à la fin de l'initialisation du master :
bash
sudo kubeadm join <IP_MASTER>:6443 --token <TOKEN> --discovery-token-ca-cert-hash sha256:<HASH>

Remplacez <TOKEN> et <HASH> par les valeurs fournies lors de l'initialisation.
Vérification de l'installation
Pour vérifier que le cluster fonctionne correctement :
bash
kubectl get nodes
kubectl get pods --all-namespaces

Déploiement d'une application simple
Pour tester votre cluster, déployez une application simple comme Nginx :
bash
kubectl create deployment nginx --image=nginx
kubectl expose deployment nginx --port=80 --type=NodePort
kubectl get svc

Visitez http://<NODE_IP>:<NODE_PORT> dans votre navigateur pour accéder à l'application Nginx.
text

## Instructions pour créer le fichier `cheatsheet.md`

1. Ouvrez un éditeur de texte (comme `nano`, `vim`, ou un éditeur graphique).
2. Copiez le contenu ci-dessus.
3. Collez-le dans l'éditeur.
4. Enregistrez le fichier sous le nom `cheatsheet.md`.

Vous pouvez ensuite partager ou télécharger ce fichier selon vos besoins.
```

## DEBUG pour le init

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