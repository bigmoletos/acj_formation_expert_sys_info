#!/bin/bash

# Docstring
# Ce script crée un namespace Kubernetes pour Flannel, applique une étiquette de sécurité,
# et installe Flannel à l'aide de Helm. Toutes les valeurs sont définies en tant que variables
# au début du script pour faciliter la modification.

# Variables
# Variables pour le répertoire personnel
USER_HOME="$HOME" # Définition du répertoire personnel de l'utilisateur
NAMESPACE="kube-flannel"  # Nom du namespace Kubernetes pour Flannel
LABEL_KEY="pod-security.kubernetes.io/enforce"  # Clé de l'étiquette de sécurité à appliquer
LABEL_VALUE="privileged"  # Valeur de l'étiquette de sécurité
HELM_CHART_URL="https://github.com/flannel-io/flannel/releases/latest/download/flannel.tgz"  # URL du chart Helm pour Flannel


# Fonction d'aide
function usage() {
    echo "Usage: $0"
    echo "Ce script installe Flannel dans un namespace Kubernetes."
    exit 1
}

# Vérification des arguments
if [ "$#" -ne 0 ]; then
    usage
fi

# Création du namespace
kubectl create ns $NAMESPACE

# Application de l'étiquette de sécurité
kubectl label --overwrite ns $NAMESPACE $LABEL_KEY=$LABEL_VALUE

# Installation de Flannel avec Helm
sudo helm install flannel \
        --namespace $NAMESPACE \
        $HELM_CHART_URL
