#!/bin/bash

# Variables globales
LOG_FILE="k8s_worker_restore.log"
SUMMARY_FILE="k8s_worker_restore_summary.md"
AUTO_APPROVE=false
FORCE_REINSTALL=false

# Fonction pour logger les actions
log_action() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a $LOG_FILE
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> $SUMMARY_FILE
}

# Fonction pour afficher l'aide
show_help() {
    echo "Usage: $0 [-h] [-y] [-f]"
    echo "Options:"
    echo "  -h    Affiche cette aide"
    echo "  -y    Mode automatique (pas de confirmation)"
    echo "  -f    Force la réinstallation"
}

# Fonction pour confirmer une action
confirm() {
    if [ "$AUTO_APPROVE" = true ]; then
        return 0
    fi

    local message="${1:-Continuer ?}"
    read -p "$message (o/n) : " response
    [[ "$response" =~ ^[oO]$ ]]
}

# Fonction pour créer un résumé
summarize() {
    local title="$1"
    local content="$2"
    local date=$(date '+%Y-%m-%d %H:%M:%S')

    echo "# $title - $date" >> $SUMMARY_FILE
    echo "" >> $SUMMARY_FILE
    echo "## Actions effectuées" >> $SUMMARY_FILE
    echo "\`\`\`" >> $SUMMARY_FILE
    echo "$content" >> $SUMMARY_FILE
    echo "\`\`\`" >> $SUMMARY_FILE
    echo "" >> $SUMMARY_FILE
}

# Installation des dépendances
install_dependencies() {
    log_action "Installation des dépendances nécessaires..."
    apt-get update
    apt-get install -y \
        conntrack \
        ethtool \
        socat \
        ebtables \
        crictl
}

# Fonction pour vérifier snap
check_snap() {
    log_action "Vérification de snap..."
    if ! command -v snap &> /dev/null; then
        log_action "Installation de snap..."
        apt-get update
        apt-get install -y snapd
        systemctl enable --now snapd.socket
        sleep 5
    fi
}

# Fonction pour vérifier le service kubelet
check_kubelet_service() {
    log_action "Vérification du service kubelet..."

    # Création du service kubelet
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

    # Arrêt du service s'il est en cours d'exécution
    systemctl stop kubelet || true

    # Nettoyage du port 10250 si nécessaire
    if lsof -i :10250 >/dev/null 2>&1; then
        log_action "Nettoyage du port 10250..."
        fuser -k 10250/tcp || true
        sleep 2
    fi

    systemctl enable kubelet
    systemctl start kubelet

    if ! systemctl is-active --quiet kubelet; then
        log_action "ERREUR: Impossible de démarrer kubelet"
        return 1
    fi

    return 0
}

# Fonction pour installer Kubernetes via snap
install_kubernetes_snap() {
    log_action "Installation de Kubernetes via snap..."

    # Vérifier snap
    check_snap

    # Suppression des anciennes installations si elles existent
    snap remove kubectl kubeadm kubelet 2>/dev/null || true

    # Installation des composants
    log_action "Installation des composants via snap..."

    if ! snap install kubectl --classic; then
        log_action "ERREUR: Installation de kubectl échouée"
        return 1
    fi

    if ! snap install kubeadm --classic; then
        log_action "ERREUR: Installation de kubeadm échouée"
        return 1
    fi

    if ! snap install kubelet --classic; then
        log_action "ERREUR: Installation de kubelet échouée"
        return 1
    fi

    # Configuration du service kubelet
    if ! check_kubelet_service; then
        return 1
    fi

    return 0
}

# Fonction pour nettoyer l'installation
clean_kubernetes_installation() {
    log_action "Nettoyage complet de l'installation Kubernetes..."

    # Arrêt des services
    systemctl stop kubelet || true

    # Suppression des snaps
    snap remove kubectl kubeadm kubelet || true

    # Suppression des fichiers de configuration
    rm -rf /etc/kubernetes/
    rm -rf /var/lib/kubelet/
    rm -rf /var/lib/etcd/
    rm -f /etc/systemd/system/kubelet.service

    # Reload systemd
    systemctl daemon-reload

    return 0
}

# Fonction pour rejoindre le cluster
join_cluster() {
    log_action "Configuration pour rejoindre le cluster..."

    read -p "Entrez l'IP du master : " MASTER_IP
    read -p "Entrez le token : " TOKEN
    read -p "Entrez le hash (sha256:...) : " HASH

    if kubeadm join ${MASTER_IP}:6443 \
        --token ${TOKEN} \
        --discovery-token-ca-cert-hash ${HASH} \
        --ignore-preflight-errors=FileExisting-crictl,FileExisting-ethtool; then
        log_action "Node joint au cluster avec succès"
        return 0
    else
        log_action "ERREUR: Impossible de joindre le cluster"
        return 1
    fi
}

# Traitement des arguments
while getopts "hyf" opt; do
    case $opt in
        h)
            show_help
            exit 0
            ;;
        y)
            AUTO_APPROVE=true
            ;;
        f)
            FORCE_REINSTALL=true
            ;;
        \?)
            echo "Option invalide: -$OPTARG" >&2
            show_help
            exit 1
            ;;
    esac
done

# Vérification des droits root
if [ "$EUID" -ne 0 ]; then
    echo "Ce script doit être exécuté en tant que root"
    exit 1
fi

# Initialisation des fichiers de log
> $LOG_FILE
> $SUMMARY_FILE

# Script principal
log_action "Début de la restauration du worker Kubernetes"

# Installation des dépendances
install_dependencies

# Nettoyage et réinstallation
clean_kubernetes_installation
if ! install_kubernetes_snap; then
    log_action "ERREUR: Installation échouée"
    summarize "Restauration échouée" "$(cat $LOG_FILE)"
    exit 1
fi

# Vérification du service
if ! check_kubelet_service; then
    log_action "ERREUR: Problème avec le service kubelet"
    summarize "Restauration échouée" "$(cat $LOG_FILE)"
    exit 1
fi

# Proposition de rejoindre le cluster
if [ "$AUTO_APPROVE" = false ]; then
    if confirm "Voulez-vous rejoindre le cluster maintenant ?"; then
        if ! join_cluster; then
            summarize "Jointure au cluster échouée" "$(cat $LOG_FILE)"
            exit 1
        fi
    fi
fi

log_action "Restauration terminée avec succès"
summarize "Restauration réussie" "$(cat $LOG_FILE)"

# Rechargement du shell
exec bash
