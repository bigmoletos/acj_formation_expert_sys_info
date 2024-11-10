#!/bin/bash
CERTS_OPTS="--client-cert-auth \
           --cert-file=certs/admin.pem \
           --key-file=certs/admin-key.pem \
           --trusted-ca-file=certs/ca.pem"

# By default, etcd will server HTTP, not HTTPS
FORCE_HTTPS_OPTS="--advertise-client-urls https://127.0.0.1:2379 \
                  --listen-client-urls https://127.0.0.1:2379"

bin/etcd --data-dir etcd-data $CERTS_OPTS $FORCE_HTTPS_OPTS


#!/bin/bash

# Docstring
# Lance le serveur etcd avec les certificats nécessaires en HTTPS

# Variables de configuration
ETCD_DIR="etcd-data"                  # Répertoire des données etcd
CERTS_DIR="certs"
ADMIN_CERT="${CERTS_DIR}/admin.pem"
ADMIN_KEY="${CERTS_DIR}/admin-key.pem"
CA_FILE="${CERTS_DIR}/ca.pem"
HTTPS_HOST="127.0.0.1"
HTTPS_PORT="2379"

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
bin/etcd --data-dir ${ETCD_DIR} \
    --client-cert-auth \
    --cert-file=${ADMIN_CERT} \
    --key-file=${ADMIN_KEY} \
    --trusted-ca-file=${CA_FILE} \
    --advertise-client-urls https://${HTTPS_HOST}:${HTTPS_PORT} \
    --listen-client-urls https://${HTTPS_HOST}:${HTTPS_PORT}
