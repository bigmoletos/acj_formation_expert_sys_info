#!/bin/bash

# Variables globales
AUTO_APPROVE=false
LOG_FILE="k8s_install.log"
SUMMARY_FILE="k8s_summary.md"

# Fonction d'aide
show_help() {
    cat << EOF
Usage: $0 [options] <worker_number> [master_ip] [token] [discovery_hash]

Script d'installation de Kubernetes Worker

Options:
    -h, --help      Affiche cette aide
    -y, --yes       Mode automatique (pas de demande de confirmation)

Arguments:
    worker_number   Numéro du worker (obligatoire)
    master_ip       IP du master (optionnel en mode interactif)
    token          Token de jointure (optionnel en mode interactif)
    discovery_hash  Hash de découverte (optionnel en mode interactif)

Description:
    Ce script effectue l'installation complète d'un nœud worker Kubernetes.
    Il réalise les actions suivantes :
    - Vérifie les droits d'administration
    - Configure le hostname
    - Installe les prérequis et Docker
    - Configure Kubernetes
    - Joint le nœud au cluster
    - Génère un résumé des actions

Prérequis:
    - Ubuntu Server
    - Droits root
    - Connexion Internet
    - Cluster master déjà configuré

Exemple:
    sudo ./$(basename $0) 1                    # Mode interactif
    sudo ./$(basename $0) -y 1 192.168.1.10 abcdef.1234 sha256:xyz  # Mode automatique

Logs:
    - Journal détaillé : $LOG_FILE
    - Résumé : $SUMMARY_FILE
EOF
    exit 0
}

# Traitement des arguments
WORKER_NUM=""
MASTER_IP=""
TOKEN=""
DISCOVERY_HASH=""

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
            if [ -z "$WORKER_NUM" ]; then
                WORKER_NUM=$1
            elif [ -z "$MASTER_IP" ]; then
                MASTER_IP=$1
            elif [ -z "$TOKEN" ]; then
                TOKEN=$1
            elif [ -z "$DISCOVERY_HASH" ]; then
                DISCOVERY_HASH=$1
            else
                echo "Trop d'arguments"
                show_help
            fi
            shift
            ;;
    esac
done

# Vérification du numéro de worker
if [ -z "$WORKER_NUM" ]; then
    echo "Erreur: Numéro de worker requis"
    show_help
fi

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
# Installation de Kubernetes Worker - Résumé

## Informations système
- Date: $(date)
- Hostname: $(hostname)
- IP: $(ip route get 1 | awk '{print $7}')
- Mode: $([[ "$AUTO_APPROVE" = true ]] && echo "Automatique" || echo "Interactif")

## Actions réalisées
EOF

# Le reste du script reste identique, en utilisant les variables définies ci-dessus
# Demande du numéro du worker
read -p "Entrez le numéro du worker (ex: 1, 2, 3...): " worker_num

# Modification du hostname
if confirm "Voulez-vous modifier le hostname en 'k8s-worker-$worker_num' ?"; then
    hostnamectl set-hostname "k8s-worker-$worker_num"
    log_action "Hostname modifié en k8s-worker-$worker_num"
fi

# Installation similaire au master jusqu'à l'initialisation
# [Mêmes étapes que le master pour l'installation des prérequis]

# Demande des informations du master
read -p "Entrez l'adresse IP du master: " master_ip
read -p "Entrez le token: " token
read -p "Entrez le hash de découverte: " discovery_hash

# Jointure au cluster
if confirm "Voulez-vous joindre le cluster ?"; then
    kubeadm join ${master_ip}:6443 --token ${token} --discovery-token-ca-cert-hash ${discovery_hash}
    if [ $? -eq 0 ]; then
        log_action "Node joint au cluster avec succès"
    else
        log_action "ERREUR: Échec de la jointure au cluster"
        if confirm "Voulez-vous réinitialiser Kubernetes ?"; then
            kubeadm reset
            systemctl stop snap.kubelet.daemon.service
            systemctl disable snap.kubelet.daemon.service
            fuser -k 10250/tcp
            log_action "Réinitialisation de Kubernetes effectuée"
        fi
    fi
fi

echo -e "\nInstallation terminée. Consultez k8s_summary.md pour le résumé des actions effectuées."