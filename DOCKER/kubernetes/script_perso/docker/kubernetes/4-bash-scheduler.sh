#!/bin/bash

# Docstring
# Ce script démarre un proxy Kubernetes et exécute un script de planification.
# Les URL et les commandes sont définies dans des variables pour éviter les valeurs "dures".

# Variables
KUBECTL_PROXY_CMD="kubectl proxy"  # Commande pour démarrer le proxy Kubernetes
SCHEDULER_SCRIPT_URL="https://raw.githubusercontent.com/rothgar/bashScheduler/main/scheduler.sh"  # URL du script de planification
SCHEDULER_CMD="bash"  # Commande pour exécuter le script de planification

# Fonction d'aide
function usage() {
    echo "Usage: $0"
    echo "Ce script démarre un proxy Kubernetes et exécute le script de planification."
    exit 1
}

# Vérification des arguments
if [ "$#" -ne 0 ]; then
    usage
fi

# Démarrer le proxy Kubernetes
$KUBECTL_PROXY_CMD &

# Exécuter le script de planification
curl -sL $SCHEDULER_SCRIPT_URL | $SCHEDULER_CMD
