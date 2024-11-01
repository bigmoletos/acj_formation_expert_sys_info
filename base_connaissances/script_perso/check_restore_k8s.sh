#!/bin/bash

# Variables globales
LOG_FILE="k8s_restore.log"
SUMMARY_FILE="k8s_restore_summary.md"
AUTO_APPROVE=false

# Fonction d'aide
show_help() {
    cat << EOF
Usage: $0 [options]

Script de vérification et restauration d'un cluster Kubernetes après reboot

Options:
    -h, --help      Affiche cette aide
    -y, --yes       Mode automatique (pas de demande de confirmation)
    -n, --new-token Génère un nouveau token de jointure
    -f, --force     Force la reconfiguration même si tout semble OK

Description:
    Ce script vérifie l'état du cluster Kubernetes et effectue les actions nécessaires
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
GENERATE_TOKEN=false
FORCE_RECONFIG=false

while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            ;;
        -y|--yes)
            AUTO_APPROVE=true
            shift
            ;;
        -n|--new-token)
            GENERATE_TOKEN=true
            shift
            ;;
        -f|--force)
            FORCE_RECONFIG=true
            shift
            ;;
        *)
            echo "Option invalide: $1"
            show_help
            ;;
    esac
done

# Initialisation du fichier de résumé
cat > $SUMMARY_FILE << EOF
# Restauration Kubernetes - Résumé

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

# Vérification de la configuration kubectl
if [ ! -f "$HOME/.kube/config" ] || [ "$FORCE_RECONFIG" = true ]; then
    log_action "Configuration de kubectl..."
    mkdir -p $HOME/.kube
    cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
    chown $(id -u):$(id -g) $HOME/.kube/config
fi

# Vérification des pods système
log_action "Vérification des pods système..."
if ! kubectl get pods -n kube-system &>/dev/null; then
    log_action "ERREUR: Impossible d'accéder aux pods système"
    if confirm "Voulez-vous reconfigurer kubectl ?"; then
        mkdir -p $HOME/.kube
        cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
        chown $(id -u):$(id -g) $HOME/.kube/config
    fi
fi

# Vérification du réseau Flannel
log_action "Vérification du réseau Flannel..."
if ! kubectl get pods -n kube-system | grep -q 'flannel'; then
    log_action "Flannel non détecté. Installation..."
    kubectl apply -f https://github.com/coreos/flannel/raw/master/Documentation/kube-flannel.yml
fi

# Génération d'un nouveau token si demandé
if [ "$GENERATE_TOKEN" = true ]; then
    log_action "Génération d'un nouveau token de jointure..."
    TOKEN_CMD=$(kubeadm token create --print-join-command)
    echo -e "\nNouvelle commande de jointure :"
    echo "$TOKEN_CMD"
    echo -e "\nCommande de jointure:" >> $SUMMARY_FILE
    echo "\`\`\`bash" >> $SUMMARY_FILE
    echo "$TOKEN_CMD" >> $SUMMARY_FILE
    echo "\`\`\`" >> $SUMMARY_FILE
fi

# Récupération et formatage des informations de jointure
get_join_info() {
    local master_ip=$(kubectl get nodes -o wide | grep master | awk '{print $6}')
    local token=$(kubeadm token list | awk 'NR==2{print $1}')
    local hash=$(openssl x509 -pubkey -in /etc/kubernetes/pki/ca.crt | \
                openssl rsa -pubin -outform der 2>/dev/null | \
                openssl dgst -sha256 -hex | sed 's/^.* //')

    echo -e "\n=== INFORMATIONS DE JOINTURE ===\n"
    echo "Pour joindre un worker au cluster, exécutez la commande suivante sur le nœud worker :"
    echo -e "\nsudo kubeadm join ${master_ip}:6443 --token ${token} --discovery-token-ca-cert-hash sha256:${hash}\n"

    # Ajout au fichier de résumé
    echo -e "\n## Commande de jointure pour les workers" >> $SUMMARY_FILE
    echo "\`\`\`bash" >> $SUMMARY_FILE
    echo "sudo kubeadm join ${master_ip}:6443 --token ${token} --discovery-token-ca-cert-hash sha256:${hash}" >> $SUMMARY_FILE
    echo "\`\`\`" >> $SUMMARY_FILE
}

# Vérification finale
log_action "Vérification finale du cluster..."
echo -e "\nÉtat des nodes :"
kubectl get nodes
echo -e "\nÉtat des pods système :"
kubectl get pods -n kube-system

# Ajout des informations de vérification au résumé
echo -e "\n## État final du cluster" >> $SUMMARY_FILE
echo "\`\`\`" >> $SUMMARY_FILE
echo "Nodes:" >> $SUMMARY_FILE
kubectl get nodes >> $SUMMARY_FILE
echo -e "\nPods système:" >> $SUMMARY_FILE
kubectl get pods -n kube-system >> $SUMMARY_FILE
echo "\`\`\`" >> $SUMMARY_FILE

# Récupération et affichage des informations de jointure
get_join_info

# Résumé des résultats de kubeadm init
if [ -f "/var/log/kubeadm.init.log" ]; then
    echo -e "\n=== RÉSULTATS DE KUBEADM INIT ===\n"
    cat /var/log/kubeadm.init.log

    echo -e "\n## Résultats de kubeadm init" >> $SUMMARY_FILE
    echo "\`\`\`" >> $SUMMARY_FILE
    cat /var/log/kubeadm.init.log >> $SUMMARY_FILE
    echo "\`\`\`" >> $SUMMARY_FILE
fi

log_action "Vérification et restauration terminées"
echo -e "\nConsultez $SUMMARY_FILE pour le résumé des actions effectuées."

# Affichage final formaté
echo -e "\n=== RÉSUMÉ DES ACTIONS ==="
echo "1. Vérification et restauration du cluster terminées"
echo "2. Les logs détaillés sont disponibles dans : $LOG_FILE"
echo "3. Le résumé complet est disponible dans : $SUMMARY_FILE"
echo "4. Utilisez la commande de jointure ci-dessus pour ajouter des workers"
echo -e "\nPour voir à nouveau la commande de jointure : ./$(basename $0) -n\n"