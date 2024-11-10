#!/bin/bash

# Docstring
# Ce script configure Kubernetes en utilisant kubectl et cfssl pour la gestion des certificats.
# Il génère les certificats nécessaires, configure les clusters, les identifiants et les contextes
# et configure kubectl pour utiliser ces configurations. Il gère également la sélection de l'architecture
# et les mises à jour de certaines versions de composants. Une option permet d'utiliser ce script
# sur un environnement Windows via WSL.

# Helper pour afficher l'usage du script
function usage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  --help                      Affiche ce message d'aide"
    echo "  --ca-config <path>          Chemin vers le fichier de configuration CA (par défaut: $CA_CONFIG)"
    echo "  --admin-config <path>       Chemin vers le fichier de configuration admin (par défaut: $ADMIN_CONFIG)"
    echo "  --windows                   Configure le script pour une utilisation sur Windows (via WSL) ou sur linux"
}

# Variables par défaut pour les options personnalisables
CA_CONFIG="ca-config.json"  # Chemin vers le fichier de configuration CA
ADMIN_CONFIG="admin.conf"    # Chemin vers le fichier de configuration admin
ARCH="amd64"                  # Par défaut, on considère une architecture amd64

# Versions des composants
K8S_VERSION="1.27.0"         # Version de Kubernetes à installer
ETCD_VERSION="3.5.7"         # Version d'ETCD à installer
CONTAINERD_VERSION="1.7.0"   # Version de Containerd à installer
RUNC_VERSION="1.1.4"         # Version de Runc à installer
CILIUM_VERSION="0.13.2"      # Version de Cilium à installer
CNI_PLUGINS_VERSION="1.2.0"  # Version des plugins CNI à installer

# Mise à jour et installation des paquets
PACKAGES=("tmux" "curl" "golang-cfssl" "linux-image-generic-hwe-22.04")

# Parse les arguments
while [[ "$1" != "" ]]; do
    case $1 in
        --help )
            usage
            exit
            ;;
        --ca-config )
            shift
            CA_CONFIG=$1
            ;;
        --admin-config )
            shift
            ADMIN_CONFIG=$1
            ;;
        --windows )
            ARCH="amd64"  # Forcer l'architecture sur amd64 pour Windows
            ;;
        * )
            echo "Option inconnue: $1"
            usage
            exit 1
    esac
    shift
done

# Vérification de l'architecture pour les systèmes non-Windows
if [[ -z "$1" && "$ARCH" != "amd64" ]]; then
    if [[ `uname -i` == 'aarch64' ]]; then
        ARCH="arm64"
    else
        ARCH="amd64"
    fi
fi

# Mise à jour et installation des paquets
git fetch origin
git reset --hard origin/main
sudo apt update -y
sudo apt upgrade -y
for PACKAGE in "${PACKAGES[@]}"; do
    sudo apt install $PACKAGE -y
done

# Création du répertoire bin si non existant
mkdir -p bin/

# Téléchargement de Helm
curl -s https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash

# Téléchargement de Kubernetes
K8S_TAR_URL="https://dl.k8s.io/v${K8S_VERSION}/kubernetes-server-linux-${ARCH}.tar.gz"
curl -L $K8S_TAR_URL -o kubernetes-server-linux-${ARCH}.tar.gz
tar -zxf kubernetes-server-linux-${ARCH}.tar.gz
for BINARY in kubectl kube-apiserver kube-scheduler kube-controller-manager kubelet; do
    mv kubernetes/server/bin/${BINARY} bin/
done

# Configuration KUBECONFIG
export KUBECONFIG=$ADMIN_CONFIG
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

# Création et copie de la configuration
mkdir -p ~/.kube && cp $ADMIN_CONFIG ~/.kube/config
