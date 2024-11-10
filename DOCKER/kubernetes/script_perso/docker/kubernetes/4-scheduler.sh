#!/bin/bash

# Docstring
# Ce script lance le planificateur Kubernetes (kube-scheduler) avec la configuration spécifiée.
# Les chemins et les fichiers de configuration sont définis en tant que variables au début du script.

# Variables
KUBE_SCHEDULER_BIN="bin/kube-scheduler"  # Chemin vers l'exécutable du planificateur Kubernetes
KUBE_CONFIG="admin.conf"                  # Fichier de configuration Kubernetes à utiliser

# Fonction d'aide
function usage() {
    echo "Usage: $0"
    echo "Ce script démarre le kube-scheduler avec le fichier de configuration spécifié."
    exit 1
}

# Vérification des arguments
if [ "$#" -ne 0 ]; then
    usage
fi

# Lancer le kube-scheduler
$KUBE_SCHEDULER_BIN --kubeconfig $KUBE_CONFIG
