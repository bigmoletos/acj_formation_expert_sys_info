#!/bin/bash

# Fonction pour afficher un message d'information
log_action() {
    echo "[INFO] $1"
}

# Fonction d'aide
show_help() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -h, --help    Affiche cette aide"
    echo ""
    echo "Ce script désinstalle complètement Kubernetes, Docker, Flannel, Snap et toutes les dépendances associées."
}

# Vérification des arguments
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    show_help
    exit 0
fi

# Arrêter et désactiver les services Kubernetes et Docker
log_action "Arrêt des services Kubernetes et Docker..."
sudo systemctl stop kubelet
sudo systemctl disable kubelet
sudo systemctl stop snap.kubelet.daemon.service
sudo systemctl disable snap.kubelet.daemon.service
sudo systemctl stop docker
sudo systemctl disable docker

# Désinstaller les paquets Kubernetes
log_action "Désinstallation de kubelet, kubeadm et kubectl..."
sudo apt-get remove --purge -y kubelet kubeadm kubectl

# Désinstaller Docker
log_action "Désinstallation de Docker..."
sudo apt-get remove --purge -y docker docker-engine docker.io containerd runc

# Supprimer Flannel (si installé via Snap)
log_action "Désinstallation de Flannel..."
sudo snap remove flannel || true

# Supprimer les fichiers de configuration
log_action "Suppression des fichiers de configuration Kubernetes..."
sudo rm -rf /etc/kubernetes/
sudo rm -rf $HOME/.kube/
sudo rm -rf /var/lib/kubelet/
sudo rm -rf /var/lib/etcd/
sudo rm -rf /etc/cni/net.d/

# Supprimer les dépôts APT Kubernetes
log_action "Suppression des dépôts APT Kubernetes..."
sudo rm -f /etc/apt/sources.list.d/kubernetes.list

# Supprimer la clé GPG
log_action "Suppression de la clé GPG Kubernetes..."
sudo rm -f /usr/share/keyrings/cloud.google.gpg
sudo rm -f /etc/apt/keyrings/kubernetes-apt-keyring.gpg

# Nettoyer les paquets inutilisés
log_action "Nettoyage des paquets inutilisés..."
sudo apt-get autoremove -y
sudo apt-get clean

# Réinitialiser les règles iptables (optionnel)
log_action "Réinitialisation des règles iptables..."
sudo iptables -F
sudo iptables -t nat -F
sudo iptables -t mangle -F
sudo iptables -X

# Fin du script
log_action "Désinstallation terminée. La VM est maintenant dans un état propre."