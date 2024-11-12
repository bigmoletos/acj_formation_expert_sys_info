#!/bin/bash

# Docstring
# Ce script configure les certificats pour Kubernetes en générant une autorité de certification (CA)
# et un certificat administrateur. Il crée également une configuration kubeconfig pour l'accès à un
# cluster Kubernetes sécurisé. Ce script est destiné à être exécuté dans un environnement sécurisé.

# Variables de configuration
USER_HOME="$HOME" # Définition du répertoire personnel de l'utilisateur
CERTS_DIR="${USER_HOME}/certs"                    # Répertoire où les certificats seront stockés
CA_CONFIG_FILE="ca-config.json"       # Fichier de configuration pour la CA
CA_CSR_FILE="ca-csr.json"             # Fichier CSR pour la CA
CA_CERT_PREFIX="ca"                   # Préfixe pour le nom du certificat de la CA
ADMIN_CSR_FILE="admin-csr.json"       # Fichier CSR pour l'utilisateur admin
ADMIN_CERT_PREFIX="admin"             # Préfixe pour le nom du certificat admin
KUBECONFIG_FILE="admin.conf"          # Fichier de configuration kubeconfig pour l'utilisateur admin
CLUSTER_NAME="demystifions-kubernetes" # Nom du cluster Kubernetes
K8S_SERVER="https://127.0.0.1:6443"   # URL du serveur Kubernetes
ADMIN_USER="admin"                    # Nom d'utilisateur pour l'accès admin
HOSTNAMES="127.0.0.1,10.0.0.1,10.244.0.1,kubernetes,kubernetes.default,kubernetes.default.svc,kubernetes.default.svc.cluster,kubernetes.svc.cluster.local"  # Noms d'hôtes pour le certificat

# Variables supplémentaires pour éviter les valeurs "en dur"
EXPIRY_DURATION="8760h"                # Durée d'expiration des certificats (1 an)
COUNTRY="FR"                           # Code du pays pour le certificat
LOCALITY="Pessac"                      # Localité pour le certificat
ORG_NAME="Kubernetes"                  # Nom de l'organisation pour le certificat
ORG_UNIT="CA"                          # Unité d'organisation pour le certificat
STATE="Nouvelle Aquitaine"             # État pour le certificat

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
sudo mkdir -p "$CERTS_DIR" && cd "$CERTS_DIR"

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
      "O": "$ORG_NAME",
      "OU": "$ORG_UNIT",
      "ST": "$STATE"
    }
  ]
}
EOF

    # Génération du certificat admin avec cfssl
    cfssl gencert -ca "$CA_CERT_PREFIX.pem" -ca-key "$CA_CERT_PREFIX-key.pem" -config "$CA_CONFIG_FILE" -profile "kubernetes" "$ADMIN_CSR_FILE" | cfssljson -bare "$ADMIN_CERT_PREFIX"

    # Création de la configuration kubeconfig
    cat > "$KUBECONFIG_FILE" <<EOF
apiVersion: v1
clusters:
- cluster:
    certificate-authority: "$CERTS_DIR/$CA_CERT_PREFIX-key.pem"
    server: "$K8S_SERVER"
  name: "$CLUSTER_NAME"
contexts:
- context:
    cluster: "$CLUSTER_NAME"
    user: "$ADMIN_USER"
  name: "$CLUSTER_NAME"
current-context: "$CLUSTER_NAME"
kind: Config
preferences: {}
users:
- name: "$ADMIN_USER"
  user:
    client-certificate: "$CERTS_DIR/$ADMIN_CERT_PREFIX.pem"
    client-key: "$CERTS_DIR/$ADMIN_CERT_PREFIX-key.pem"
EOF
}
