#!/bin/bash

# Docstring
# Ce script installe Cilium et expose un déploiement Kubernetes.
# Les valeurs de configuration sont définies en tant que variables au début du script.

# Variables
# Variables pour le répertoire personnel
USER_HOME="$HOME/$USER" # Définition du répertoire personnel de l'utilisateur
SERVICE_YAML="${USER_HOME}/service.yaml"  # Nom du fichier YAML de service à appliquer
CILIUM_BIN="${USER_HOME}/bin/cilium"  # Chemin vers l'exécutable de Cilium
# SERVICE_YAML="service.yaml"  # Nom du fichier YAML de service à appliquer
DEPLOYMENT_NAME="web"  # Nom du déploiement Kubernetes à exposer
EXPOSE_PORT=80  # Port sur lequel le déploiement sera exposé

# Fonction d'aide
function usage() {
    echo "Usage: $0"
    echo "Ce script installe Cilium et expose un déploiement Kubernetes."
    exit 1
}

# Vérification des arguments
if [ "$#" -ne 0 ]; then
    usage
fi

# Installation de Cilium
$CILIUM_BIN install

# Application du fichier de service
# kubectl apply -f $SERVICE_YAML

# Exposition du déploiement
# kubectl expose deployment $DEPLOYMENT_NAME --port=$EXPOSE_PORT
