#!/bin/bash

# Docstring
# Ce script démarre le kubelet avec les configurations spécifiées.
# Les paramètres de configuration sont définis en tant que variables au début du script.

# Variables
# Variables pour le répertoire personnel
USER_HOME="$HOME/$USER" # Définition du répertoire personnel de l'utilisateur
KUBECONFIG_FILE="${USER_HOME}/admin.conf"     # Fichier de configuration Kubernetes pour l'authentification
KUBELET_BIN="sudo ${USER_HOME}/bin/kubelet"  # Chemin vers l'exécutable kubelet avec sudo
KUBECONFIG_FILE="${USER_HOME}/admin.conf"     # Fichier de configuration Kubernetes pour l'authentification
CONTAINER_RUNTIME_ENDPOINT="unix:///${USER_HOME}/var/run/containerd/containerd.sock"  # Point de terminaison pour le runtime de conteneurs

# Fonction d'aide
function usage() {
    echo "Usage: $0"
    echo "Ce script démarre le kubelet avec les configurations spécifiées."
    exit 1
}

# Vérification des arguments
if [ "$#" -ne 0 ]; then
    usage
fi

# Démarrer le kubelet avec les paramètres spécifiés
$KUBELET_BIN --kubeconfig $KUBECONFIG_FILE  --container-runtime-endpoint=$CONTAINER_RUNTIME_ENDPOINT
# Si votre serveur a swap (mais nous devrions l'avoir désactivé)
# --fail-swap-on=false

