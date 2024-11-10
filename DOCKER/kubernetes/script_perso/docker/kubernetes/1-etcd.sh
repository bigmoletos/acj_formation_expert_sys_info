#!/bin/bash

# Docstring
# Ce script lance le serveur etcd avec les certificats nécessaires en HTTPS.
# Il utilise des variables pour la configuration afin d'éviter les valeurs "dures".
# Les options de configuration sont définies en haut du script pour une meilleure lisibilité et maintenabilité.

# Variables de configuration
ETCD_BIN="bin/etcd"                      # Chemin vers l'exécutable etcd
ETCD_DATA_DIR="etcd-data"                # Répertoire des données etcd
CERTS_DIR="certs"                        # Répertoire des certificats
ADMIN_CERT="${CERTS_DIR}/admin.pem"      # Chemin vers le certificat admin
ADMIN_KEY="${CERTS_DIR}/admin-key.pem"   # Chemin vers la clé admin
CA_FILE="${CERTS_DIR}/ca.pem"            # Chemin vers le fichier CA
HTTPS_HOST="127.0.0.1"                   # Hôte pour HTTPS
HTTPS_PORT="2379"                         # Port pour HTTPS

# Helper pour afficher l'usage
function usage() {
    echo "Usage: $0"
    echo "Ce script configure et lance etcd avec HTTPS et les certificats spécifiés."
    echo "Options:"
    echo "  --help                      Affiche ce message d'aide"
}

# Vérifie si l'option --help est fournie
if [[ "$1" == "--help" ]]; then
    usage
    exit 0
fi

# Lancer etcd en HTTPS avec les certificats fournis
$ETCD_BIN --data-dir ${ETCD_DATA_DIR} \
    --client-cert-auth \
    --cert-file=${ADMIN_CERT} \
    --key-file=${ADMIN_KEY} \
    --trusted-ca-file=${CA_FILE} \
    --advertise-client-urls https://${HTTPS_HOST}:${HTTPS_PORT} \
    --listen-client-urls https://${HTTPS_HOST}:${HTTPS_PORT}
