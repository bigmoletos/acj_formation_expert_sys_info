#!/bin/bash

"""
Ce script prépare l'environnement pour l'installation de Kubernetes et de ses composants associés.
Il effectue les actions suivantes :
1. Vérifie et définit l'architecture du système.
2. Met à jour le système et installe les paquets nécessaires.
3. Télécharge et extrait les binaires de Kubernetes, etcd, containerd, runc, Cilium CLI et les plugins CNI.
4. Configure les chemins d'accès et les permissions nécessaires.
5. Prépare le fichier d'ingress pour le déploiement.

Utilisation :
    ./0-prereqs.sh [architecture]
    Si aucune architecture n'est spécifiée, 'amd64' est utilisé par défaut.
"""

# Fonction pour afficher un message d'erreur et quitter le script
function error_exit {
    echo "$1" 1>&2
    exit 1
}

# Variables pour l'architecture
USER_HOME="$HOME" # Définition du répertoire personnel de l'utilisateur

DEFAULT_ARCH="amd64" # Architecture par défaut si aucune n'est spécifiée
ARCH=${1:-$DEFAULT_ARCH} # Architecture spécifiée par l'utilisateur ou par défaut

# Vérification de l'architecture du système
SYSTEM_ARCH=$(uname -i) # Architecture du système
if [[ "$SYSTEM_ARCH" == 'aarch64' ]]; then
    ARCH="arm64" # Changement d'architecture pour ARM si le système est aarch64
elif [[ "$SYSTEM_ARCH" == 'x86_64' ]]; then
    ARCH="amd64" # Changement d'architecture pour x86_64
else
    echo "Architecture non supportée : $SYSTEM_ARCH. Utilisez amd64 ou arm64." # Message d'erreur pour architecture non supportée
    exit 1
fi

# Récupération des dernières modifications du dépôt
GIT_ORIGIN="origin" # Nom de l'origine du dépôt Git
GIT_BRANCH="main" # Branche principale du dépôt Git
git fetch $GIT_ORIGIN
git reset --hard $GIT_ORIGIN/$GIT_BRANCH

# Mise à jour et installation des paquets nécessaires
APT_UPDATE_CMD="sudo apt update -y" # Commande pour mettre à jour la liste des paquets
APT_UPGRADE_CMD="sudo apt upgrade -y" # Commande pour mettre à niveau les paquets installés
APT_INSTALL_CMD="sudo apt install tmux curl golang-cfssl linux-image-generic-hwe-22.04 netfilter-persistent -y" # Commande pour installer les paquets nécessaires
$APT_UPDATE_CMD
$APT_UPGRADE_CMD
$APT_INSTALL_CMD

# Versions des composants Kubernetes
K8S_VERSION="1.31.0-alpha.0" # Version de Kubernetes à installer
ETCD_VERSION="3.5.14" # Version d'etcd à installer
CONTAINERD_VERSION="1.7.18" # Version de containerd à installer
RUNC_VERSION="1.2.0-rc.1" # Version de runc à installer
CILIUM_CLI_VERSION="0.16.10" # Version de Cilium CLI à installer
CNI_PLUGINS_VERSION="1.5.0" # Version des plugins CNI à installer

# Variables pour le répertoire personnel
# USER_HOME="$HOME" # Définition du répertoire personnel de l'utilisateur

# Création du répertoire pour les binaires
BIN_DIR="${USER_HOME}/bin/" # Répertoire pour stocker les binaires téléchargés
sudo sudo mkdir -p $BIN_DIR # Création du répertoire pour les binaires

# URL d'hôte pour ingress
HOST_DOMAIN="dk.zwindler.fr" # Domaine d'hôte pour l'accès aux services via Ingress

# Installation de Helm
HELM_INSTALL_URL="https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3" # URL pour installer Helm
sudo curl $HELM_INSTALL_URL | bash

# Téléchargement et extraction de Kubernetes
K8S_TAR_URL="https://dl.k8s.io/v$K8S_VERSION/kubernetes-server-linux-$ARCH.tar.gz" # URL de téléchargement de Kubernetes
sudo curl -L $K8S_TAR_URL -o kubernetes-server-linux-$ARCH.tar.gz
tar -zxf kubernetes-server-linux-${ARCH}.tar.gz

# Déplacement des binaires Kubernetes
for BINARY in kubectl kube-apiserver kube-scheduler kube-controller-manager kubelet kube-proxy; do
    sudo mv kubernetes/server/bin/${BINARY} $BIN_DIR # Déplacement des binaires dans le répertoire personnel
done

# Nettoyage des fichiers temporaires
sudo rm kubernetes-server-linux-${ARCH}.tar.gz # Suppression de l'archive tar de Kubernetes
sudo rm -rf kubernetes # Suppression du répertoire extrait de Kubernetes

# Déplacement de kubectl dans le répertoire local
KUBECTL_PATH="$BIN_DIR/kubectl" # Chemin où kubectl sera installé
sudo mv kubectl $KUBECTL_PATH

# Ajout de l'autocomplétion pour kubectl
BASHRC_FILE="$HOME/.bashrc" # Fichier de configuration bash de l'utilisateur
echo 'source <(kubectl completion bash)' >> $BASHRC_FILE # Ajout de l'autocomplétion à .bashrc

# Déplacement des autres binaires
sudo mv kube* $BIN_DIR # Déplacement des autres binaires dans le répertoire bin/

# Téléchargement et installation d'etcd
ETCD_TAR_URL="https://github.com/etcd-io/etcd/releases/download/v${ETCD_VERSION}/etcd-v${ETCD_VERSION}-linux-${ARCH}.tar.gz" # URL de téléchargement d'etcd
curl -L $ETCD_TAR_URL | tar --strip-components=1 --wildcards -zx '*/etcd' # Extraction de etcd
sudo mv etcd /var/lib/etcd # Déplacement de etcd dans /var/lib/etcd

# Création du répertoire de données pour etcd
ETCD_DATA_DIR="${USER_HOME}/etcd-data" # Répertoire pour stocker les données d'etcd
sudo mkdir -p $ETCD_DATA_DIR # Création du répertoire de données
sudo chmod 700 $ETCD_DATA_DIR # Définition des pesudo rmissions du répertoire

# Téléchargement et installation de containerd
CONTAINERD_TAR_URL="https://github.com/containerd/containerd/releases/download/v${CONTAINERD_VERSION}/containerd-${CONTAINERD_VERSION}-linux-${ARCH}.tar.gz" # URL de téléchargement de containerd
wget $CONTAINERD_TAR_URL # Téléchargement de containerd
tar --strip-components=1 --wildcards -zx '*/ctr' '*/containerd' '*/containerd-shim-runc-v2' -f containerd-${CONTAINERD_VERSION}-linux-${ARCH}.tar.gz # Extraction des binaires de containerd
sudo rm containerd-${CONTAINERD_VERSION}-linux-${ARCH}.tar.gz # Suppression de l'archive tar de containerd
sudo mv containerd* ctr /usr/local/bin/ # Déplacement des binaires de containerd dans /usr/local/bin/

# Téléchargement et installation de runc
RUNC_URL="https://github.com/opencontainers/runc/releases/download/v${RUNC_VERSION}/runc.${ARCH}" # URL de téléchargement de runc
curl $RUNC_URL -L -o runc # Téléchargement de runc
sudo chmod +x runc # Rendre runc exécutable
sudo mv runc /usr/bin/ # Déplacement de runc dans /usr/bin/

# Téléchargement et installation de Cilium CLI
CILIUM_CLI_URL="https://github.com/cilium/cilium-cli/releases/download/v${CILIUM_CLI_VERSION}/cilium-linux-${ARCH}.tar.gz" # URL de téléchargement de Cilium CLI
wget $CILIUM_CLI_URL # Téléchargement de Cilium CLI
tar xzf cilium-linux-${ARCH}.tar.gz # Extraction de Cilium CLI
sudo rm cilium-linux-${ARCH}.tar.gz # Suppression de l'archive tar de Cilium CLI
sudo mv cilium /usr/local/bin/ # Déplacement de Cilium CLI dans /usr/local/bin/

# Installation des plugins CNI
CNI_PLUGINS_URL="https://github.com/containernetworking/plugins/releases/download/v${CNI_PLUGINS_VERSION}/cni-plugins-linux-${ARCH}-v${CNI_PLUGINS_VERSION}.tgz" # URL de téléchargement des plugins CNI
CNI_BIN_DIR="/opt/cni/bin" # Répertoire pour stocker les plugins CNI
sudo sudo mkdir -p $CNI_BIN_DIR # Création du répertoire pour les plugins CNI
curl -O -L $CNI_PLUGINS_URL # Téléchargement des plugins CNI
sudo tar -C $CNI_BIN_DIR -xzf cni-plugins-linux-${ARCH}-v${CNI_PLUGINS_VERSION}.tgz # Extraction des plugins CNI
sudo rm cni-plugins-linux-${ARCH}-v${CNI_PLUGINS_VERSION}.tgz # Suppression de l'archive tar des plugins CNI
sudo chown root: $CNI_BIN_DIR # Changement de propriétaire du répertoire des plugins CNI

# Désactivation de l'échange
SWAPOFF_CMD="sudo swapoff -a" # Commande pour désactiver l'échange
$SWAPOFF_CMD # Exécution de la commande pour désactiver l'échange

# Suppression du pare-feu sur Ubuntu dans le cloud Oracle
# NETFILTER_CMD="which netfilter-persistent" # Commande pour vérifier si netfilter-persistent est installé
# if [ $? -eq 0 ]; then
#     sudo iptables -F # Suppression des règles iptables
#     sudo netfilter-persistent save # Sauvegarde des règles iptables
# fi

# Préparation de la valeur d'hôte pour ingress
INGRESS_FILE="ingress.yaml" # Fichier de configuration d'ingress
HOST_VALUE="${HOST_DOMAIN}" # Valeur d'hôte pour ingress
sed -i "s/host: $HOST_DOMAIN/host: $HOST_VALUE/" $INGRESS_FILE # Modification de la valeur d'hôte dans le fichier ingress

# Exécution du script de génération de certificats
CERTS_SCRIPT="run/0-gen-certs.sh" # Script pour générer les certificats
if [ -f "$CERTS_SCRIPT" ]; then
    $CERTS_SCRIPT # Exécution du script de génération de certificats
else
    echo "Le script de génération de certificats n'existe pas à l'emplacement : $CERTS_SCRIPT" # Message d'erreur si le script n'existe pas
fi

# Création du répertoire pour les certificats kube
sudo mkdir -p ${USER_HOME}/.kube/certs # Création du répertoire pour les certificats
