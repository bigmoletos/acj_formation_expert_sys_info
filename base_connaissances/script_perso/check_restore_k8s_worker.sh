#!/bin/bash

# Variables globales
LOG_FILE="k8s_worker_restore.log"
SUMMARY_FILE="k8s_worker_restore_summary.md"
AUTO_APPROVE=false

# Fonction d'aide
show_help() {
    cat << EOF
Usage: $0 [options] [master_ip] [token] [hash]

Script de vérification et restauration d'un worker Kubernetes après reboot

Options:
    -h, --help      Affiche cette aide
    -y, --yes       Mode automatique (pas de demande de confirmation)
    -f, --force     Force la reconfiguration même si tout semble OK
    -r, --rejoin    Force une nouvelle jointure au cluster

Arguments optionnels:
    master_ip       IP du master (ex: 192.168.1.100)
    token          Token de jointure
    hash           Hash de découverte (sha256:...)

Description:
    Ce script vérifie l'état du worker Kubernetes et effectue les actions nécessaires
    pour le restaurer après un reboot.

Logs:
    - Journal détaillé : $LOG_FILE
    - Résumé : $SUMMARY_FILE
EOF
    exit 0
}

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

# Traitement des arguments
FORCE_RECONFIG=false
FORCE_REJOIN=false
MASTER_IP=""
TOKEN=""
HASH=""

while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            ;;
        -y|--yes)
            AUTO_APPROVE=true
            shift
            ;;
        -f|--force)
            FORCE_RECONFIG=true
            shift
            ;;
        -r|--rejoin)
            FORCE_REJOIN=true
            shift
            ;;
        *)
            if [ -z "$MASTER_IP" ]; then
                MASTER_IP=$1
            elif [ -z "$TOKEN" ]; then
                TOKEN=$1
            elif [ -z "$HASH" ]; then
                HASH=$1
            else
                echo "Option invalide: $1"
                show_help
            fi
            shift
            ;;
    esac
done

# Initialisation du fichier de résumé
cat > $SUMMARY_FILE << EOF
# Restauration Kubernetes Worker - Résumé

## Informations système
- Date: $(date)
- Hostname: $(hostname)
- IP: $(ip route get 1 | awk '{print $7}')

## Actions réalisées
EOF

# Vérification des droits root
if [ "$EUID" -ne 0 ]; then
    echo "Ce script doit être exécuté en tant que root"
    exit 1
fi

# Vérification de kubelet
log_action "Vérification du service kubelet..."
if ! systemctl is-active --quiet kubelet; then
    log_action "Kubelet n'est pas actif. Démarrage du service..."
    systemctl start kubelet
    systemctl enable kubelet
    if ! systemctl is-active --quiet kubelet; then
        log_action "ERREUR: Impossible de démarrer kubelet"
        exit 1
    fi
fi

# Vérification de la connexion au cluster
check_cluster_connection() {
    if ! kubectl get nodes &>/dev/null; then
        return 1
    fi
    return 0
}

# Reset du node si nécessaire
reset_node() {
    log_action "Reset du node Kubernetes..."
    kubeadm reset -f
    systemctl stop kubelet
    systemctl stop docker
    rm -rf /var/lib/cni/
    rm -rf /var/lib/kubelet/*
    rm -rf /etc/cni/
    ifconfig cni0 down
    ifconfig flannel.1 down
    ip link delete cni0
    ip link delete flannel.1
    systemctl start docker
    systemctl start kubelet
}

# Rejoindre le cluster
join_cluster() {
    if [ -z "$MASTER_IP" ] || [ -z "$TOKEN" ] || [ -z "$HASH" ]; then
        log_action "Informations de jointure manquantes"
        echo "Veuillez fournir les informations de jointure :"
        read -p "IP du master : " MASTER_IP
        read -p "Token : " TOKEN
        read -p "Hash (sha256:...) : " HASH
    fi

    log_action "Tentative de jointure au cluster..."
    if kubeadm join ${MASTER_IP}:6443 --token ${TOKEN} --discovery-token-ca-cert-hash ${HASH}; then
        log_action "Jointure au cluster réussie"
        return 0
    else
        log_action "ERREUR: Échec de la jointure au cluster"
        return 1
    fi
}

# Vérification principale
if [ "$FORCE_REJOIN" = true ] || ! check_cluster_connection; then
    log_action "Node non connecté au cluster"
    if confirm "Voulez-vous réinitialiser et rejoindre le cluster ?"; then
        reset_node
        join_cluster
    fi
fi

# Vérification finale
log_action "Vérification finale du node..."
if check_cluster_connection; then
    log_action "Node correctement connecté au cluster"
    kubectl get nodes | grep $(hostname)
else
    log_action "ATTENTION: Le node n'est toujours pas connecté au cluster"
fi

# Ajout des informations au résumé
echo -e "\n## État final du node" >> $SUMMARY_FILE
echo "\`\`\`" >> $SUMMARY_FILE
kubectl get nodes | grep $(hostname) >> $SUMMARY_FILE 2>/dev/null || echo "Non connecté au cluster" >> $SUMMARY_FILE
echo "\`\`\`" >> $SUMMARY_FILE

# Affichage final
echo -e "\n=== RÉSUMÉ DES ACTIONS ==="
echo "1. Vérification et restauration du worker terminées"
echo "2. Les logs détaillés sont disponibles dans : $LOG_FILE"
echo "3. Le résumé complet est disponible dans : $SUMMARY_FILE"

if ! check_cluster_connection; then
    echo -e "\nPour rejoindre le cluster, utilisez :"
    echo "./$(basename $0) -r [master_ip] [token] [hash]"
fi

echo -e "\nConsultez $SUMMARY_FILE pour le résumé des actions effectuées.\n" 