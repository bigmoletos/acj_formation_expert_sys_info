#!/bin/bash

# Script de test de connectivité entre le master et les workers Kubernetes
LOG_FILE="test_kubernetes_connectivity.log"

# Fonction pour logger les actions
log_action() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a $LOG_FILE
}

# Fonction pour tester la connectivité des nodes
check_node_status() {
    log_action "Vérification du statut des nœuds Kubernetes..."
    local nodes_status=$(kubectl get nodes --no-headers 2>&1)
    if [ $? -ne 0 ]; then
        log_action "Erreur lors de la connexion au cluster Kubernetes : $nodes_status"
        if echo "$nodes_status" | grep -q "The connection to the server localhost:8080 was refused"; then
            log_action "Erreur : Impossible de se connecter au serveur API Kubernetes. Vérifiez si kube-apiserver est en cours d'exécution et si le contexte kubectl est correctement configuré."
        fi
        exit 1
    fi
    echo "$nodes_status" | tee -a $LOG_FILE
    if echo "$nodes_status" | grep -q 'NotReady'; then
        log_action "Attention : Un ou plusieurs nœuds sont en statut 'NotReady'."
        exit 1
    else
        log_action "Tous les nœuds sont en statut 'Ready'."
    fi
}

# Fonction pour tester la connectivité des pods
check_pod_status() {
    log_action "Vérification du statut des pods..."
    local pods_status=$(kubectl get pods --all-namespaces --no-headers 2>&1)
    if [ $? -ne 0 ]; then
        log_action "Erreur lors de la récupération des informations des pods : $pods_status"
        if echo "$pods_status" | grep -q "The connection to the server localhost:8080 was refused"; then
            log_action "Erreur : Impossible de se connecter au serveur API Kubernetes. Vérifiez si kube-apiserver est en cours d'exécution et si le contexte kubectl est correctement configuré."
        fi
        exit 1
    fi
    echo "$pods_status" | tee -a $LOG_FILE
    if echo "$pods_status" | grep -q 'Pending\|Error\|CrashLoopBackOff'; then
        log_action "Attention : Un ou plusieurs pods ont un statut indiquant un problème (Pending, Error, CrashLoopBackOff)."
        exit 1
    else
        log_action "Tous les pods sont en bon état."
    fi
}

# Fonction principale
main() {
    # Vérifier si kubectl est installé
    if ! command -v kubectl &> /dev/null; then
        log_action "Erreur : kubectl n'est pas installé. Assurez-vous que kubectl est installé sur le master."
        exit 1
    fi

    # Vérifier le contexte kubectl
    local current_context=$(kubectl config current-context 2>&1)
    if [ $? -ne 0 ]; then
        log_action "Erreur : Aucun contexte Kubernetes valide n'est défini. Configurez kubectl avec 'kubectl config set-context'."
        exit 1
    else
        log_action "Contexte Kubernetes actuel : $current_context"
    fi

    # Tester la connectivité des nodes et des pods
    check_node_status
    check_pod_status
}

# Lancer le script principal
main
