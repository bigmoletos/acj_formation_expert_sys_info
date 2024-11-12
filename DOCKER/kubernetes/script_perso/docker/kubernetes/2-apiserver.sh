#!/bin/bash

# Docstring
# Ce script lance le kube-apiserver avec les configurations de certificat
# et de connexion etcd nécessaires pour le fonctionnement d'un cluster Kubernetes sécurisé.
# Les options d'autorisation incluent les modes Node et RBAC, permettant une gestion
# granulaire des permissions et des privilèges.

# Variables
USER_HOME="$HOME/$USER" # Définition du répertoire personnel de l'utilisateur
CERTS_DIR="${USER_HOME}/certs/"  # Répertoire contenant les certificats
CLIENT_CA_FILE="${CERTS_DIR}ca.pem"  # Fichier CA client pour la validation des certificats
TLS_CERT_FILE="${CERTS_DIR}admin.pem"  # Fichier de certificat TLS pour le serveur
TLS_PRIVATE_KEY_FILE="${CERTS_DIR}admin-key.pem"  # Clé privée TLS correspondante
SERVICE_ACCOUNT_KEY_FILE="${CERTS_DIR}admin.pem"  # Fichier de clé pour le compte de service
SERVICE_ACCOUNT_SIGNING_KEY_FILE="${CERTS_DIR}admin-key.pem"  # Clé de signature pour le compte de service
SERVICE_ACCOUNT_ISSUER="https://kubernetes.default.svc.cluster.local"  # Émetteur du compte de service
ETCD_CAFILE="${CERTS_DIR}ca.pem"  # Fichier CA pour etcd
ETCD_CERTFILE="${CERTS_DIR}admin.pem"  # Fichier de certificat TLS pour etcd
ETCD_KEYFILE="${CERTS_DIR}admin-key.pem"  # Clé privée TLS pour etcd
ETCD_SERVERS="https://127.0.0.1:2379"  # URL du serveur etcd

# Variables pour le répertoire personnel

# Helper pour afficher l'usage du script
function usage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  --help                      Affiche ce message d'aide"
    echo "  --client-ca-file <path>     Chemin vers le fichier CA client (par défaut: ${CLIENT_CA_FILE})"
    echo "  --etcd-server <url>         URL du serveur etcd (par défaut: ${ETCD_SERVERS})"
}

# Variables par défaut pour les options personnalisables
CLIENT_CA_FILE="${CLIENT_CA_FILE}"
ETCD_SERVER="${ETCD_SERVERS}"

# Parse les arguments
while [[ "$1" != "" ]]; do
    case $1 in
        --help )
            usage
            exit
            ;;
        --client-ca-file )
            shift
            CLIENT_CA_FILE=$1
            ;;
        --etcd-server )
            shift
            ETCD_SERVER=$1
            ;;
        * )
            echo "Option inconnue: $1"
            usage
            exit 1
    esac
    shift
done

# Mise à jour des options en fonction des arguments
CERTS_OPTS="--client-ca-file=${CLIENT_CA_FILE} \
    --tls-cert-file=${TLS_CERT_FILE} \
    --tls-private-key-file=${TLS_PRIVATE_KEY_FILE} \
    --service-account-key-file=${SERVICE_ACCOUNT_KEY_FILE} \
    --service-account-signing-key-file=${SERVICE_ACCOUNT_SIGNING_KEY_FILE} \
    --service-account-issuer=${SERVICE_ACCOUNT_ISSUER}"

ETCD_OPTS="--etcd-cafile=${ETCD_CAFILE} \
    --etcd-certfile=${ETCD_CERTFILE} \
    --etcd-keyfile=${ETCD_KEYFILE} \
    --etcd-servers=${ETCD_SERVER}"

# Exécution du kube-apiserver avec les options spécifiées
bin/kube-apiserver ${CERTS_OPTS} ${ETCD_OPTS} \
    --allow-privileged \
    --authorization-mode=Node,RBAC

# Commandes suggérées pour tester
# kubectl version --short
# kubectl api-resources | head
# kubectl create deployment web --image=nginx
