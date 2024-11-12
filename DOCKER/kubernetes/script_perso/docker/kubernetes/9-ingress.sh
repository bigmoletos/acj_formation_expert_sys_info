#!/bin/bash

# Docstring
# Ce script installe Traefik en utilisant Helm et applique une configuration d'ingress.
# Les valeurs de configuration sont définies en tant que variables au début du script.

# Variables
HELM_REPO_URL="https://traefik.github.io/charts"  # URL du dépôt Helm pour Traefik
HELM_RELEASE_NAME="traefik"                         # Nom de la release Helm pour Traefik
HELM_CHART_NAME="traefik/traefik"                  # Nom du chart Helm pour Traefik
NODE_PORT_WEB=30080                                 # Port pour le service web
NODE_PORT_WEBSECURE=30443                           # Port pour le service web sécurisé
# INGRESS_FILE="ingress.yaml"                         # Fichier de configuration d'ingress

# Variables pour le répertoire personnel
USER_HOME="$HOME/$USER" # Définition du répertoire personnel de l'utilisateur
INGRESS_FILE="${USER_HOME}/ingress.yaml" # Fichier de configuration d'ingress

# Fonction d'aide
function usage() {
    echo "Usage: $0"
    echo "Ce script installe Traefik et applique la configuration d'ingress."
    exit 1
}

# Vérification des arguments
if [ "$#" -ne 0 ]; then
    usage
fi

# Ajouter le dépôt Helm
helm repo add traefik $HELM_REPO_URL

# Installer Traefik avec les ports configurés
helm install $HELM_RELEASE_NAME $HELM_CHART_NAME \
    --set ports.web.nodePort=$NODE_PORT_WEB \
    --set ports.websecure.nodePort=$NODE_PORT_WEBSECURE

# Appliquer la configuration d'ingress
kubectl apply -f $INGRESS_FILE
