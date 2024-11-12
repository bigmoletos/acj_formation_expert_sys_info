#!/bin/bash

# Docstring
# Ce script démarre le kube-controller-manager avec les options de certificat et les configurations réseau.
# Les chemins et options sont définis par des variables pour faciliter la configuration.

# Variables de configuration
USER_HOME="$HOME" # Définition du répertoire personnel de l'utilisateur
CERTS_DIR="${USER_HOME}/certs"  # Répertoire contenant les certificats
CA_FILE="${CERTS_DIR}/ca.pem"  # Fichier du certificat d'autorité
ADMIN_KEY="${CERTS_DIR}/ca-key.pem"  # Clé privée de l'administrateur
KUBECONFIG="${USER_HOME}/admin.conf"  # Fichier de configuration Kubernetes par défaut
CLUSTER_CIDR="10.0.0.0/16"  # Plage CIDR pour le cluster
CONTROLLER_MANAGER_BIN="${USER_HOME}/bin/kube-controller-manager"  # Chemin vers l'exécutable du kube-controller-manager

# Fonction d'aide
function usage() {
    echo "Usage: $0"
    echo "Options:"
    echo "  --help                      Affiche ce message d'aide"
    echo "  --kubeconfig <path>         Chemin vers kubeconfig (par défaut: ${KUBECONFIG})"
    echo "  --cluster-cidr <CIDR>       Plage CIDR pour le cluster (par défaut: ${CLUSTER_CIDR})"
}

# Parse les arguments
while [[ "$1" != "" ]]; do
    case $1 in
        --help )
            usage
            exit
            ;;
        --kubeconfig )
            shift
            KUBECONFIG=$1
            ;;
        --cluster-cidr )
            shift
            CLUSTER_CIDR=$1
            ;;
        * )
            echo "Option inconnue: $1"
            usage
            exit 1
    esac
    shift
done

# Démarrage de kube-controller-manager
${CONTROLLER_MANAGER_BIN} \
    --kubeconfig="${KUBECONFIG}" \
    --cluster-signing-cert-file="${CA_FILE}" \
    --cluster-signing-key-file="${ADMIN_KEY}" \
    --cluster-cidr="${CLUSTER_CIDR}" \
    --allocate-node-cidrs=true
