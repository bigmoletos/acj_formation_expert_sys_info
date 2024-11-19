#!/bin/bash

# Variables globales
AUTO_APPROVE=false
LOG_FILE="k8s_install.log"
SUMMARY_FILE="k8s_summary.md"

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
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> $LOG_FILE
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> $SUMMARY_FILE
    echo "$1"
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

# [Le reste du script reste identique, en utilisant les variables définies ci-dessus]
# Modification du hostname
current_hostname=$(hostname)
if confirm "Voulez-vous modifier le hostname en 'k8s-master' ? (Actuel: $current_hostname)"; then
    hostnamectl set-hostname k8s-master
    log_action "Hostname modifié en k8s-master"
fi

# Vérification et mise à jour des paquets
if confirm "Voulez-vous mettre à jour la liste des paquets ?"; then
    apt update
    log_action "Mise à jour de la liste des paquets effectuée"
fi

# Installation des prérequis
if confirm "Voulez-vous installer les prérequis (apt-transport-https, ca-certificates, curl) ?"; then
    apt install -y apt-transport-https ca-certificates curl
    log_action "Installation des prérequis"
fi

# Installation de Docker
if ! command -v docker &> /dev/null; then
    if confirm "Docker n'est pas installé. Voulez-vous l'installer ?"; then
        apt install -y docker.io
        systemctl enable --now docker
        log_action "Installation et activation de Docker"
    fi
fi

# Configuration de Kubernetes
if confirm "Voulez-vous configurer les dépôts Kubernetes ?"; then
    curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | apt-key add -
    echo "deb https://apt.kubernetes.io/ kubernetes-xenial main" > /etc/apt/sources.list.d/kubernetes.list
    apt update
    log_action "Configuration des dépôts Kubernetes"
fi

# Installation des composants Kubernetes
if confirm "Voulez-vous installer kubeadm, kubelet et kubectl ?"; then
    apt install -y kubeadm kubelet kubectl
    systemctl enable --now kubelet
    log_action "Installation des composants Kubernetes"
fi

# Désactivation du swap
if confirm "Voulez-vous désactiver le swap ?"; then
    swapoff -a
    sed -i '/ swap / s/^\(.*\)$/#\1/g' /etc/fstab
    log_action "Désactivation du swap"
fi

# Récupération de l'IP
IP_ADDR=$(ip addr show | grep 'inet ' | grep -v '127.0.0.1' | awk '{print $2}' | cut -d/ -f1 | head -n 1)

# Configuration de kubeadm
if confirm "Voulez-vous initialiser le cluster Kubernetes (IP: $IP_ADDR) ?"; then
    # Création du fichier de configuration
    cat > kubeadm-config.yaml <<EOF
kind: KubeletConfiguration
apiVersion: kubelet.config.k8s.io/v1beta1
cgroupDriver: systemd
containerRuntimeEndpoint: "unix:///var/run/containerd/containerd.sock"
podInfraContainerImage: "k8s.gcr.io/pause:3.8"
EOF

    # Initialisation du cluster
    kubeadm init --pod-network-cidr=10.244.0.0/16 --apiserver-advertise-address=$IP_ADDR --config=kubeadm-config.yaml | tee kubeadm-init.log

    if [ $? -eq 0 ]; then
        log_action "Initialisation du cluster réussie"

        # Extraction des informations importantes
        JOIN_COMMAND=$(tail -n 2 kubeadm-init.log)
        echo "### Commande pour rejoindre le cluster:" >> k8s_summary.md
        echo "\`\`\`" >> k8s_summary.md
        echo "$JOIN_COMMAND" >> k8s_summary.md
        echo "\`\`\`" >> k8s_summary.md
    else
        log_action "ERREUR: Échec de l'initialisation du cluster"
        if confirm "Voulez-vous réinitialiser Kubernetes ?"; then
            kubeadm reset
            systemctl stop snap.kubelet.daemon.service
            systemctl disable snap.kubelet.daemon.service
            fuser -k 10250/tcp
            log_action "Réinitialisation de Kubernetes effectuée"
        fi
    fi
fi

# Configuration pour l'utilisateur courant
if confirm "Voulez-vous configurer kubectl pour l'utilisateur courant ?"; then
    mkdir -p $HOME/.kube
    cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
    chown $(id -u):$(id -g) $HOME/.kube/config
    log_action "Configuration de kubectl pour l'utilisateur courant"
fi

echo -e "\nInstallation terminée. Consultez k8s_summary.md pour le résumé des actions effectuées."