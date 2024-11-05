#!/bin/bash

# Fonction d'aide
show_help() {
    echo "Usage: $0 [options]"
    echo
    echo "Ce script facilite la jointure d'un nœud worker à un cluster Kubernetes."
    echo
    echo "Options:"
    echo "  -h, --help     Affiche cette aide"
    echo "  -i, --ip       Spécifie l'IP du master (par défaut: détection automatique)"
    echo "  -t, --token    Spécifie le token (par défaut: extrait du master)"
    echo "  --hash         Spécifie le hash (par défaut: calculé depuis le certificat)"
    echo
    echo "Exemple:"
    echo "  $0"
    echo "  $0 -i 192.168.1.79"
    echo "  $0 -i 192.168.1.178 -t abcdef.0123456789abcdef"
}

# Valeurs par défaut
MASTER_IP=$(kubectl config view -o jsonpath='{.clusters[0].cluster.server}' | cut -d'/' -f3 | cut -d':' -f1)
TOKEN=$(kubeadm token list | awk 'NR==2 {print $1}')
HASH=$(openssl x509 -in /etc/kubernetes/pki/ca.crt -noout -pubkey | openssl rsa -pubin -outform DER 2>/dev/null | sha256sum | cut -d' ' -f1)

# Traitement des arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -i|--ip)
            MASTER_IP="$2"
            shift 2
            ;;
        -t|--token)
            TOKEN="$2"
            shift 2
            ;;
        --hash)
            HASH="$2"
            shift 2
            ;;
        *)
            echo "Option invalide: $1"
            show_help
            exit 1
            ;;
    esac
done

# Vérification des valeurs
echo "Configuration actuelle:"
echo "IP du master: $MASTER_IP"
echo "Token: $TOKEN"
echo "Hash: $HASH"
echo
echo "Voulez-vous modifier ces valeurs? (o/N)"
read -r response

if [[ "$response" =~ ^[Oo]$ ]]; then
    echo "Entrez l'IP du master [$MASTER_IP]: "
    read -r new_ip
    MASTER_IP=${new_ip:-$MASTER_IP}

    echo "Entrez le token [$TOKEN]: "
    read -r new_token
    TOKEN=${new_token:-$TOKEN}

    echo "Entrez le hash [$HASH]: "
    read -r new_hash
    HASH=${new_hash:-$HASH}
fi

# Génération de la commande
JOIN_CMD="sudo kubeadm join ${MASTER_IP}:6443 --token ${TOKEN} --discovery-token-ca-cert-hash sha256:${HASH}"

echo
echo "Commande qui sera exécutée:"
echo "$JOIN_CMD"
echo
echo "Voulez-vous exécuter cette commande? (o/N)"
read -r execute

if [[ "$execute" =~ ^[Oo]$ ]]; then
    eval "$JOIN_CMD"
else
    echo "Commande non exécutée. Vous pouvez la copier et l'exécuter manuellement."
fi