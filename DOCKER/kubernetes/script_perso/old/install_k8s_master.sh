#!/bin/bash

# Variables globales
LOG_FILE="k8s_master_install.log"
SUMMARY_FILE="k8s_master_install_summary.md"

# Fonction d'aide
show_help() {
    cat << EOF
Usage: $0 [options]

Script d'installation de Kubernetes Master

Options:
    -h, --help      Affiche cette aide
    -y, --yes       Mode automatique (pas de demande de confirmation)

Description:
    Ce script effectue l'installation complète d'un nœud master Kubernetes.
    Il réalise les actions suivantes :
    - Vérifie les droits d'administration
    - Configure le hostname
    - Installe les prérequis et Docker
    - Configure Kubernetes
    - Initialise le cluster
    - Génère un résumé des actions

Prérequis:
    - Ubuntu Server
    - Droits root
    - Connexion Internet

Exemple:
    sudo ./$(basename $0)         # Mode interactif
    sudo ./$(basename $0) -y      # Mode automatique

Logs:
    - Journal détaillé : $LOG_FILE
    - Résumé : $SUMMARY_FILE
EOF
    exit 0
}

# Traitement des arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            ;;
        -y|--yes)
            AUTO_APPROVE=true
            shift
            ;;
        *)
            echo "Option invalide: $1"
            show_help
            ;;
    esac
done

# Fonction pour logger les actions
log_action() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a $LOG_FILE
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> $SUMMARY_FILE
}

# Fonction pour demander confirmation
confirm() {
    if [ "$AUTO_APPROVE" = true ]; then
        return 0
    fi
    read -p "$1 (o/n): " response
    case "$response" in
        [oO]) return 0 ;;
        *) return 1 ;;
    esac
}

# Vérification des droits root
if [ "$EUID" -ne 0 ]; then
    echo "Ce script doit être exécuté en tant que root"
    exit 1
fi

# Initialisation du fichier de résumé
cat > $SUMMARY_FILE << EOF
# Installation de Kubernetes Master - Résumé

## Informations système
- Date: $(date)
- Hostname: $(hostname)
- IP: $(ip route get 1 | awk '{print $7}')
- Mode: $([[ "$AUTO_APPROVE" = true ]] && echo "Automatique" || echo "Interactif")

## Actions réalisées
EOF
# Installation de Docker
install_docker() {
    log_action "Installation de Docker..."
    apt-get update
    apt-get install -y docker.io
    systemctl enable docker
    systemctl start docker
}

# Installation via snap
install_kubernetes_components() {
    log_action "Installation des composants Kubernetes via snap..."

    # Installation de snap si nécessaire
    if ! command -v snap &> /dev/null; then
        apt-get update
        apt-get install -y snapd
        systemctl enable --now snapd.socket
    fi

    # Installation des composants
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


# Configuration du master
setup_master() {
    log_action "Configuration du nœud master..."

    # Initialisation du cluster
    kubeadm init --pod-network-cidr=10.244.0.0/16 | tee /var/log/kubeadm.init.log

    # Configuration de kubectl
    mkdir -p $HOME/.kube
    cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
    chown $(id -u):$(id -g) $HOME/.kube/config

    # Installation de Flannel
    kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
}

# Script principal
log_action "Début de l'installation du master Kubernetes"

# Installation des composants
install_docker
install_kubernetes_components

# Configuration du master
setup_master

log_action "Installation du master terminée"

# Rechargement du shell
exec bash