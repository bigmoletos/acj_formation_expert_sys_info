#!/bin/bash

# Variables globales
LOG_FILE="k8s_master_install.log"
SUMMARY_FILE="k8s_master_install_summary.md"

# Fonction pour logger les actions
log_action() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a $LOG_FILE
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> $SUMMARY_FILE
}

# Vérification des droits root
if [ "$EUID" -ne 0 ]; then
    echo "Ce script doit être exécuté en tant que root"
    exit 1
fi

# Configuration du hostname
read -p "Entrez le nouveau hostname (master/worker1/worker2) : " new_hostname

# Validation du hostname
case $new_hostname in
    master|worker1|worker2)
        # Modification du hostname
        hostnamectl set-hostname $new_hostname
        echo "127.0.0.1 $new_hostname" >> /etc/hosts
        log_action "Hostname configuré : $new_hostname"

        echo "Hostname configuré. Le shell va être rechargé."
        exec bash
        ;;
    *)
        echo "Hostname invalide. Utilisez master, worker1 ou worker2"
        exit 1
        ;;
esac

install_kubernetes_snap() {
    log_action "Installation de Kubernetes via snap..."

    # Vérification/Installation de snap
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

# Installation de Docker
install_docker() {
    log_action "Installation de Docker..."
    apt-get update
    apt-get install -y docker.io
    systemctl enable docker
    systemctl start docker
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
install_kubernetes_snap

# Configuration du master
setup_master

log_action "Installation du master terminée"

# Rechargement du shell
exec bash 