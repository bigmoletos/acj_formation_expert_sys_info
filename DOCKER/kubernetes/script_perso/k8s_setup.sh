#!/bin/bash

# Variables globales
LOG_FILE="k8s_setup.log"
SUMMARY_FILE="k8s_setup_summary.md"
AUTO_APPROVE=false
FORCE_REINSTALL=false
NODE_TYPE=""
MASTER_IP=""
WORKER_IP=""
MASTER_HOSTNAME="master"
WORKER_HOSTNAME="worker"
CURRENT_IP=""

# Couleurs pour les messages
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Fonction d'aide
show_help() {
    cat << EOF
Usage: $0 [options]

Script de configuration Kubernetes pour master et worker nodes

Options:
  -h, --help        Affiche cette aide
  -y, --yes         Mode automatique (pas de confirmation)
  -f, --force       Force la réinstallation
  -t, --type        Type de nœud (master/worker)
  -i, --ip          IP du master (optionnel)

Exemples:
  $0 -t master                  Configure un nœud master
  $0 -t worker -i 192.168.1.10  Configure un worker avec l'IP du master
  $0 -t worker -y              Configure un worker en mode automatique

Note: Ce script doit être exécuté en tant que root.
EOF
}

# Fonction de logging améliorée
log_action() {
    local level=$1
    local message=$2
    local timestamp=$(date '+%Y-%m-%d %H:%M:%S')

    case $level in
        "INFO")
            echo -e "${GREEN}[INFO]${NC} $message"
            ;;
        "WARN")
            echo -e "${YELLOW}[WARN]${NC} $message"
            ;;
        "ERROR")
            echo -e "${RED}[ERROR]${NC} $message"
            ;;
    esac

    echo "$timestamp - [$level] $message" >> $LOG_FILE
}

# Fonction de vérification des erreurs
check_error() {
    if [ $? -ne 0 ]; then
        log_action "ERROR" "Erreur lors de: $1"
        if [ "$2" = "FATAL" ]; then
            log_action "ERROR" "Erreur fatale, arrêt du script"
            exit 1
        fi
        return 1
    fi
    return 0
}

# Fonction de confirmation améliorée
confirm() {
    if [ "$AUTO_APPROVE" = true ]; then
        return 0
    fi
    local message="${1:-Continuer ?}"
    while true; do
        read -p "$message (o/n) : " response
        case $response in
            [oO]) return 0 ;;
            [nN]) return 1 ;;
            *) echo "Veuillez répondre par 'o' ou 'n'" ;;
        esac
    done
}

# Fonction de détection de l'IP
detect_ip() {
    # Détecte l'IP principale de la machine
    CURRENT_IP=$(ip -4 addr show | grep -oP '(?<=inet\s)\d+(\.\d+){3}' | grep -v '127.0.0.1' | head -n 1)
    if [ -z "$CURRENT_IP" ]; then
        log_action "ERROR" "Impossible de détecter l'IP de la machine"
        return 1
    fi
    log_action "INFO" "IP détectée: $CURRENT_IP"
    return 0
}

# Configuration du hostname
setup_hostname() {
    log_action "INFO" "Configuration du hostname..."

    local new_hostname=""
    if [ "$NODE_TYPE" = "master" ]; then
        new_hostname="master"
    else
        while true; do
            read -p "Entrez le numéro du worker (1-99): " worker_num
            if [[ "$worker_num" =~ ^[1-9][0-9]?$ ]]; then
                new_hostname="worker-$worker_num"
                break
            else
                log_action "WARN" "Numéro invalide. Utilisez un nombre entre 1 et 99."
            fi
        done
    fi

    # Sauvegarde et mise à jour des fichiers
    cp /etc/hostname /etc/hostname.bak || log_action "WARN" "Impossible de sauvegarder hostname"
    cp /etc/hosts /etc/hosts.bak || log_action "WARN" "Impossible de sauvegarder hosts"

    echo "$new_hostname" > /etc/hostname

    # Mise à jour de /etc/hosts
    cat > /etc/hosts << EOF
127.0.0.1   localhost
$CURRENT_IP   $new_hostname
EOF

    # Application du hostname
    hostnamectl set-hostname "$new_hostname"

    log_action "INFO" "Hostname configuré: $new_hostname"

    # Au lieu de exec bash, on exporte la variable
    export HOSTNAME="$new_hostname"

    # Vérification
    if [ "$(hostname)" != "$new_hostname" ]; then
        log_action "WARN" "Le hostname n'a pas été appliqué immédiatement, il sera effectif au prochain redémarrage"
    fi
}

# Configuration système de base
setup_system() {
    log_action "INFO" "Configuration système de base..."

    # Désactivation du swap
    swapoff -a
    sed -i '/ swap / s/^/#/' /etc/fstab

    # Configuration de containerd
    mkdir -p /etc/containerd
    containerd config default > /etc/containerd/config.toml
    sed -i 's/disabled_plugins/enabled_plugins/' /etc/containerd/config.toml
    systemctl restart containerd.service

    # Configuration réseau
    modprobe br_netfilter
    echo "net.bridge.bridge-nf-call-iptables=1" >> /etc/sysctl.conf
    sysctl -p
}

# Fonction pour installer crictl
install_crictl() {
    log_action "INFO" "Installation de crictl..."

    # Vérifiez si crictl est déjà installé
    if ! command -v crictl &> /dev/null; then
        # Téléchargez la dernière version de crictl
        VERSION="v1.24.0" # Remplacez par la version souhaitée
        wget https://github.com/kubernetes-sigs/cri-tools/releases/download/$VERSION/crictl-$VERSION-linux-amd64.tar.gz

        # Extrayez le fichier
        tar -zxvf crictl-$VERSION-linux-amd64.tar.gz

        # Déplacez crictl dans /usr/local/bin
        sudo mv crictl /usr/local/bin/

        # Vérifiez l'installation
        if command -v crictl &> /dev/null; then
            log_action "INFO" "crictl installé avec succès."
        else
            log_action "ERROR" "Échec de l'installation de crictl."
            return 1
        fi
    else
        log_action "INFO" "crictl est déjà installé."
    fi
}

# Fonction de vérification et nettoyage
check_and_clean() {
    log_action "INFO" "Vérification et nettoyage du système..."

    # Vérification des processus utilisant le port 10250
    if lsof -i:10250 &> /dev/null; then
        log_action "WARN" "Port 10250 en cours d'utilisation. Tentative de nettoyage..."
        systemctl stop kubelet || true
        pkill -f kubelet || true
        fuser -k 10250/tcp || true
        fuser -k 10250/tcp || true
        fuser -k 10250/tcp || true
        sleep 2
    fi
        # Vérification si le port est toujours occupé
    if lsof -i:10250 &> /dev/null; then
        log_action "ERROR" "Le port 10250 est toujours occupé. Veuillez le libérer manuellement."
        return 1
    fi

    # Vérification des installations précédentes
    if [ "$FORCE_REINSTALL" = true ]; then
        log_action "INFO" "Suppression des installations précédentes..."

        # Arrêt des services
        systemctl stop kubelet || true
        systemctl stop docker || true

        # Reset kubeadm
        kubeadm reset -f || true

        # Suppression des configurations
        rm -rf /etc/kubernetes/
        rm -rf $HOME/.kube/
        rm -rf /var/lib/kubelet/
        rm -rf /var/lib/etcd/
        rm -rf /etc/cni/net.d/

        # Suppression des snaps Kubernetes
        snap remove kubelet || true
        snap remove kubectl || true
        snap remove kubeadm || true

        # Nettoyage des règles iptables
        iptables -F && iptables -t nat -F && iptables -t mangle -F && iptables -X
    fi

    # Installation des dépendances manquantes
    log_action "INFO" "Installation des dépendances requises..."
    apt-get update
    apt-get install -y \
        conntrack \
        ethtool \
        socat \
        ebtables \
        apt-transport-https \
        ca-certificates \
        curl \
        gnupg \
        lsb-release

    # Installation de crictl
    install_crictl

    # Vérification des installations
    local deps=(conntrack ethtool crictl)
    for dep in "${deps[@]}"; do
        if ! command -v $dep &> /dev/null; then
            log_action "ERROR" "Impossible d'installer $dep"
            return 1
        fi
    done

    return 0
}

# Installation des composants Kubernetes
install_kubernetes() {
    log_action "INFO" "Installation de Kubernetes..."

    # Installation de snap si nécessaire
    if ! command -v snap &> /dev/null; then
        apt-get update
        apt-get install -y snapd
        systemctl enable --now snapd.socket
    fi

    # Installation des composants K8s
    snap install kubectl --classic
    snap install kubeadm --classic
    snap install kubelet --classic

    # Configuration du service kubelet
    cat > /etc/systemd/system/kubelet.service << EOF
[Unit]
Description=kubelet: The Kubernetes Node Agent
Documentation=https://kubernetes.io/docs/
Wants=network-online.target
After=network-online.target

[Service]
ExecStart=/snap/bin/kubelet
Restart=always
StartLimitInterval=0
RestartSec=10

[Install]
WantedBy=multi-user.target
EOF

    systemctl daemon-reload
    systemctl enable kubelet
    systemctl start kubelet
}

# Initialisation du master
init_master() {
    log_action "INFO" "Initialisation du master node..."

    kubeadm init --pod-network-cidr=10.244.0.0/16 --apiserver-advertise-address=$CURRENT_IP

    # Configuration de kubectl
    mkdir -p $HOME/.kube
    cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
    chown $(id -u):$(id -g) $HOME/.kube/config

    # Installation de Flannel
    kubectl apply -f https://raw.githubusercontent.com/flannel-io/flannel/master/Documentation/kube-flannel.yml

    # Récupération des informations pour le join
    TOKEN=$(kubeadm token list | awk 'NR==2 {print $1}')
    HASH=$(openssl x509 -in /etc/kubernetes/pki/ca.crt -noout -pubkey | openssl rsa -pubin -outform DER 2>/dev/null | sha256sum | cut -d' ' -f1)

    log_action "INFO" "Informations pour joindre le cluster:"
    echo "kubeadm join ${CURRENT_IP}:6443 --token $TOKEN --discovery-token-ca-cert-hash sha256:$HASH"
}

# Configuration du worker
setup_worker() {
    log_action "INFO" "Configuration du worker node..."

    if [ -z "$MASTER_IP" ]; then
        read -p "Entrez l'IP du master: " MASTER_IP
    fi

    read -p "Entrez le token: " TOKEN
    read -p "Entrez le hash: " HASH

    kubeadm join ${MASTER_IP}:6443 --token $TOKEN --discovery-token-ca-cert-hash sha256:$HASH
}

# Script principal
main() {
    # Vérification des droits root
    if [ "$EUID" -ne 0 ]; then
        log_action "ERROR" "Ce script doit être exécuté en tant que root"
        exit 1
    fi

    # Détection de l'IP
    detect_ip

    # Demande du type de nœud si non spécifié
    if [ -z "$NODE_TYPE" ]; then
        read -p "Type de nœud (master/worker): " NODE_TYPE
    fi

    # Vérification et nettoyage
    if ! check_and_clean; then
        log_action "ERROR" "Échec de la préparation du système"
        exit 1
    fi

    # Configuration du hostname
    setup_hostname

    # Configuration système
    setup_system

    # Installation de Kubernetes
    install_kubernetes

    # Configuration spécifique selon le type de nœud
    if [ "$NODE_TYPE" = "master" ]; then
        init_master
    else
        setup_worker
    fi

    log_action "INFO" "Configuration terminée avec succès"
}

# Traitement des arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -y|--yes)
            AUTO_APPROVE=true
            shift
            ;;
        -f|--force)
            FORCE_REINSTALL=true
            shift
            ;;
        -t|--type)
            NODE_TYPE="$2"
            shift 2
            ;;
        -i|--ip)
            MASTER_IP="$2"
            shift 2
            ;;
        *)
            echo "Option invalide: $1"
            show_help
            exit 1
            ;;
    esac
done

# Lancement du script
main

# Fin du script avec message de succès
log_action "INFO" "Script terminé avec succès"
exit 0