#!/bin/bash

# Docstring
# Ce script configure les certificats pour Kubernetes en générant une autorité de certification (CA)
# et un certificat administrateur. Il crée également une configuration kubeconfig pour l'accès à un
# cluster Kubernetes sécurisé. Ce script est destiné à être exécuté dans un environnement sécurisé.

# Variables de configuration
USER_HOME="$HOME/$USER" # Définition du répertoire personnel de l'utilisateur
# CERTS_DIR="certs"                    # Répertoire où les certificats seront stockés
CA_CONFIG_FILE="ca-config.json"      # Fichier de configuration pour l'autorité de certification
CA_CSR_FILE="ca-csr.json"            # Fichier de demande de signature de certificat pour la CA
CA_CERT_PREFIX="ca"                   # Préfixe pour le nom des fichiers de certificat de la CA
ADMIN_CSR_FILE="admin-csr.json"      # Fichier de demande de signature de certificat pour l'utilisateur admin
ADMIN_CERT_PREFIX="admin"             # Préfixe pour le nom des fichiers de certificat de l'utilisateur admin
KUBECONFIG_FILE="admin.conf"          # Fichier de configuration kubeconfig pour l'utilisateur admin
CLUSTER_NAME="demystifions-kubernetes" # Nom du cluster Kubernetes
K8S_SERVER="https://127.0.0.1:6443"  # URL du serveur Kubernetes
ADMIN_USER="admin"                    # Nom d'utilisateur pour l'administrateur
HOSTNAMES="127.0.0.1,10.0.0.1,10.244.0.1,kubernetes,kubernetes.default,kubernetes.default.svc,kubernetes.default.svc.cluster,kubernetes.svc.cluster.local"  # Noms d'hôtes pour le certificat

# Variables supplémentaires pour éviter les valeurs "en dur"
EXPIRY_DURATION="8760h"               # Durée d'expiration des certificats
COUNTRY="FR"                          # Code du pays pour le certificat
LOCALITY="Pessac"                     # Localité pour le certificat
ORG_NAME="Kubernetes"                 # Nom de l'organisation pour le certificat
ORG_UNIT="CA"                         # Unité d'organisation pour le certificat
STATE="Nouvelle Aquitaine"            # État pour le certificat

# Variables pour le répertoire personnel
CERTS_DIR="${USER_HOME}/certs" # Répertoire où les certificats seront stockés

# Helper pour afficher l'usage du script
function usage() {
    echo "Usage: $0"
    echo "Ce script génère les certificats pour Kubernetes, configure la CA et crée une configuration kubeconfig."
    echo "Options:"
    echo "  --help                      Affiche ce message d'aide"
}

# Vérifie si l'option --help est fournie
if [[ "$1" == "--help" ]]; then
    usage
    exit 0
fi

# Création du répertoire de certificats
mkdir -p "$CERTS_DIR" && cd "$CERTS_DIR"

{
    # Génération du fichier de configuration CA
    cat > "$CA_CONFIG_FILE" <<EOF
{
  "signing": {
    "default": {
      "expiry": "$EXPIRY_DURATION"
    },
    "profiles": {
      "kubernetes": {
        "usages": ["signing", "key encipherment", "server auth", "client auth"],
        "expiry": "$EXPIRY_DURATION"
      }
    }
  }
}
EOF

    # Génération de la CSR (Certificate Signing Request) pour la CA
    cat > "$CA_CSR_FILE" <<EOF
{
  "CN": "$ORG_NAME",
  "key": {
    "algo": "rsa",
    "size": 2048
  },
  "names": [
    {
      "C": "$COUNTRY",
      "L": "$LOCALITY",
      "O": "$ORG_NAME",
      "OU": "$ORG_UNIT",
      "ST": "$STATE"
    }
  ]
}
EOF

    # Génération du certificat de la CA avec cfssl
    cfssl gencert -initca "$CA_CSR_FILE" | cfssljson -bare "$CA_CERT_PREFIX"
}

{
    # Génération de la CSR pour l'utilisateur admin
    cat > "$ADMIN_CSR_FILE" <<EOF
{
  "CN": "$ADMIN_USER",
  "key": {
    "algo": "rsa",
    "size": 2048
  },
  "names": [
    {
      "C": "$COUNTRY",
      "L": "$LOCALITY",
      "O": "system:masters",
      "OU": "Démystifions Kubernetes",
      "ST": "$STATE"
    }
  ]
}
EOF

    # Génération du certificat admin avec cfssl
    cfssl gencert \
      -ca="$CA_CERT_PREFIX.pem" \
      -ca-key="$CA_CERT_PREFIX-key.pem" \
      -config="$CA_CONFIG_FILE" \
      -hostname="$HOSTNAMES" \
      -profile="kubernetes" \
      "$ADMIN_CSR_FILE" | cfssljson -bare "$ADMIN_CERT_PREFIX"
}

# Retour au répertoire parent
cd ..

# Configuration kubeconfig pour utiliser les certificats générés

# Définir le fichier kubeconfig
export KUBECONFIG="$KUBECONFIG_FILE"

# Configuration du cluster dans kubeconfig
kubectl config set-cluster "$CLUSTER_NAME" \
  --certificate-authority="${CERTS_DIR}/${CA_CERT_PREFIX}.pem" \
  --embed-certs=true \
  --server="$K8S_SERVER"

# Configuration des identifiants admin dans kubeconfig
kubectl config set-credentials "$ADMIN_USER" \
  --embed-certs=true \
  --client-certificate="${CERTS_DIR}/${ADMIN_CERT_PREFIX}.pem" \
  --client-key="${CERTS_DIR}/${ADMIN_CERT_PREFIX}-key.pem"

# Configuration du contexte pour admin dans kubeconfig
kubectl config set-context "$ADMIN_USER" \
  --cluster="$CLUSTER_NAME" \
  --user="$ADMIN_USER"

# Utiliser le contexte admin par défaut
kubectl config use-context "$ADMIN_USER"

# Copier le fichier de configuration dans le répertoire .kube
mkdir -p ~/.kube && cp "$KUBECONFIG_FILE" ~/.kube/config
