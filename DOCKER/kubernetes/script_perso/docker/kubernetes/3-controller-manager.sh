#!/bin/bash

# Docstring
# Démarre le kube-controller-manager avec les options de certificat et les configurations réseau.

# Variables de configuration
CERTS_DIR="certs"
CA_FILE="${CERTS_DIR}/ca.pem"
ADMIN_KEY="${CERTS_DIR}/ca-key.pem"
KUBECONFIG="admin.conf"
CLUSTER_CIDR="10.0.0.0/16"
CONTROLLER_MANAGER_BIN="bin/kube-controller-manager"

# Helper pour afficher l'usage
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
