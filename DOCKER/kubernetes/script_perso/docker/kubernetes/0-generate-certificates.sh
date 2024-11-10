#!/bin/bash

# Docstring
# Ce script configure les certificats pour Kubernetes en générant une autorité de certification (CA)
# et un certificat administrateur. Il crée également une configuration kubeconfig pour l'accès à un
# cluster Kubernetes sécurisé. Ce script est destiné à être exécuté dans un environnement sécurisé.

# Variables de configuration
CERTS_DIR="certs"                    # Répertoire pour les certificats
CA_CONFIG_FILE="ca-config.json"       # Fichier de configuration CA
CA_CSR_FILE="ca-csr.json"             # CSR pour la CA
CA_CERT_PREFIX="ca"                   # Préfixe pour les fichiers CA générés
ADMIN_CSR_FILE="admin-csr.json"       # CSR pour l'utilisateur admin
ADMIN_CERT_PREFIX="admin"             # Préfixe pour les fichiers admin générés
KUBECONFIG_FILE="admin.conf"          # Fichier kubeconfig généré
CLUSTER_NAME="demystifions-kubernetes" # Nom du cluster
K8S_SERVER="https://127.0.0.1:6443"   # Adresse du serveur Kubernetes
ADMIN_USER="admin"                    # Nom de l'utilisateur administrateur
HOSTNAMES="127.0.0.1,10.0.0.1,10.244.0.1,kubernetes,kubernetes.default,kubernetes.default.svc,kubernetes.default.svc.cluster,kubernetes.svc.cluster.local"  # Hostnames pour le certificat

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
      "expiry": "8760h"
    },
    "profiles": {
      "kubernetes": {
        "usages": ["signing", "key encipherment", "server auth", "client auth"],
        "expiry": "8760h"
      }
    }
  }
}
EOF

    # Génération de la CSR (Certificate Signing Request) pour la CA
    cat > "$CA_CSR_FILE" <<EOF
{
  "CN": "Kubernetes",
  "key": {
    "algo": "rsa",
    "size": 2048
  },
  "names": [
    {
      "C": "FR",
      "L": "Pessac",
      "O": "Kubernetes",
      "OU": "CA",
      "ST": "Nouvelle Aquitaine"
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
      "C": "FR",
      "L": "Pessac",
      "O": "system:masters",
      "OU": "Démystifions Kubernetes",
      "ST": "Nouvelle Aquitaine"
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
