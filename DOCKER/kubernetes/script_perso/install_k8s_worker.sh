#!/bin/bash

# Variables globales
LOG_FILE="k8s_worker_install.log"
SUMMARY_FILE="k8s_worker_install_summary.md"

# Fonction pour logger les actions
log_action() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a $LOG_FILE
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> $SUMMARY_FILE
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

# Installation de snap
install_snap() {
    log_action "Vérification de snap..."
    if ! command -v snap &> /dev/null; then
        log_action "Installation de snap..."
        apt-get update
        apt-get install -y snapd
        systemctl enable --now snapd.socket
        sleep 5
    fi
}

# Installation de Docker
install_docker() {
    log_action "Installation de Docker..."
    apt-get update
    apt-get install -y docker.io
    systemctl enable docker
    systemctl start docker
}

# Installation des composants Kubernetes via snap
install_kubernetes_components() {
    log_action "Installation des composants Kubernetes via snap..."

    # Suppression des anciennes installations si elles existent
    snap remove kubectl kubeadm kubelet 2>/dev/null || true

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

    # Arrêt du service s'il est en cours d'exécution
    systemctl stop kubelet || true

    # Nettoyage du port 10250 si nécessaire
    if lsof -i :10250 >/dev/null 2>&1; then
        log_action "Nettoyage du port 10250..."
        fuser -k 10250/tcp || true
        sleep 2
    fi

    # Démarrage du service
    systemctl start kubelet
}

# Configuration du worker
setup_worker() {
    log_action "Configuration du worker..."

    # Demander les informations de jointure
    read -p "Entrez l'adresse IP du master : " master_ip
    read -p "Entrez le token : " token
    read -p "Entrez le hash de découverte (sha256:...) : " hash

    # Jointure au cluster avec ignore des erreurs non fatales
    if kubeadm join ${master_ip}:6443 \
        --token ${token} \
        --discovery-token-ca-cert-hash ${hash} \
        --ignore-preflight-errors=FileExisting-crictl,FileExisting-ethtool; then
        log_action "Worker joint au cluster avec succès"
    else
        log_action "ERREUR: Impossible de joindre le cluster"
        exit 1
    fi
}

# Script principal
log_action "Début de l'installation du worker Kubernetes"

# Installation des composants
install_dependencies
install_snap
install_docker
install_kubernetes_components

# Configuration du worker
setup_worker

log_action "Installation du worker terminée"

# Affichage des informations
echo -e "\nInstallation terminée !"
echo "Pour vérifier l'état du worker, exécutez 'kubectl get nodes' sur le master"

# Rechargement du shell
exec bash