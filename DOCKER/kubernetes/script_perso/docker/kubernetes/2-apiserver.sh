#!/bin/bash

# Docstring
# Ce script lance le kube-apiserver avec les configurations de certificat
# et de connexion etcd nécessaires pour le fonctionnement d'un cluster Kubernetes sécurisé.
# Les options d'autorisation incluent les modes Node et RBAC, permettant une gestion
# granulaire des permissions et des privilèges.

# Initialisation des options de certificat
CERTS_OPTS="--client-ca-file=certs/ca.pem \
    --tls-cert-file=certs/admin.pem \
    --tls-private-key-file=certs/admin-key.pem \
    --service-account-key-file=certs/admin.pem \
    --service-account-signing-key-file=certs/admin-key.pem \
    --service-account-issuer=https://kubernetes.default.svc.cluster.local"

# Initialisation des options etcd
ETCD_OPTS="--etcd-cafile=certs/ca.pem \
    --etcd-certfile=certs/admin.pem \
    --etcd-keyfile=certs/admin-key.pem \
    --etcd-servers=https://127.0.0.1:2379"

# Helper pour afficher l'usage du script
function usage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  --help                      Affiche ce message d'aide"
    echo "  --client-ca-file <path>     Chemin vers le fichier CA client (par défaut: certs/ca.pem)"
    echo "  --etcd-server <url>         URL du serveur etcd (par défaut: https://127.0.0.1:2379)"
}

# Variables par défaut pour les options personnalisables
CLIENT_CA_FILE="certs/ca.pem"
ETCD_SERVER="https://127.0.0.1:2379"

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
    --tls-cert-file=certs/admin.pem \
    --tls-private-key-file=certs/admin-key.pem \
    --service-account-key-file=certs/admin.pem \
    --service-account-signing-key-file=certs/admin-key.pem \
    --service-account-issuer=https://kubernetes.default.svc.cluster.local"

ETCD_OPTS="--etcd-cafile=${CLIENT_CA_FILE} \
    --etcd-certfile=certs/admin.pem \
    --etcd-keyfile=certs/admin-key.pem \
    --etcd-servers=${ETCD_SERVER}"

# Exécution du kube-apiserver avec les options spécifiées
bin/kube-apiserver ${CERTS_OPTS} ${ETCD_OPTS} \
    --allow-privileged \
    --authorization-mode=Node,RBAC

# Commandes suggérées pour tester
# kubectl version --short
# kubectl api-resources | head
# kubectl create deployment web --image=nginx
