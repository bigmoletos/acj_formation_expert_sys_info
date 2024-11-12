#!/bin/bash

# Variables
HELM_REPO="https://projectcalico.docs.tigera.io/charts"  # URL du dépôt Helm de Calico
NAMESPACE="tigera-operator"                               # Nom du namespace pour l'opérateur Tigera
HELM_CHART="projectcalico/tigera-operator"               # Nom du chart Helm à installer
HELM_VERSION="v3.25.1"                                   # Version du chart Helm à installer

# Fonction d'installation de Calico
# Cette fonction ajoute le dépôt Helm, crée un namespace et installe Calico.
#
# Utilisation :
#   install_calico
#
# Prérequis :
#   - Helm doit être installé et configuré.
#   - kubectl doit être configuré pour accéder au cluster Kubernetes.
install_calico() {
    # Ajout du dépôt Helm
    sudo helm repo add projectcalico $HELM_REPO

    # Création du namespace
    sudo kubectl create namespace $NAMESPACE

    # Installation de Calico
    sudo helm install calico $HELM_CHART --version $HELM_VERSION --namespace $NAMESPACE
}

# Appel de la fonction d'installation
install_calico
