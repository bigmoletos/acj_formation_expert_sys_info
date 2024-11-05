#!/bin/bash

# Fonction d'aide
show_help() {
    echo "Usage: $0 [options]"
    echo
    echo "Ce script facilite la jointure d'un nœud worker à un cluster Kubernetes."
    echo
    echo "Options:"
    echo "  -h, --help     Affiche cette aide"
}

# Fichier de sortie
OUTPUT_FILE="kubeadm_join.txt"

# Demande si on est sur le master ou le worker
read -p "Êtes-vous sur le master (m) ou le worker (w)? " NODE_TYPE

# Valeurs par défaut
MASTER_IP="192.168.1.79"
TOKEN=""
HASH=""

if [[ "$NODE_TYPE" == "m" ]]; then
    # Si on est sur le master, récupérer le token et le hash
    TOKEN=$(kubeadm token list | awk 'NR==2 {print $1}')
    HASH=$(openssl x509 -in /etc/kubernetes/pki/ca.crt -noout -pubkey | openssl rsa -pubin -outform DER 2>/dev/null | sha256sum | cut -d' ' -f1)

    # Génération de la commande
    JOIN_CMD="sudo kubeadm join ${MASTER_IP}:6443 --token ${TOKEN} --discovery-token-ca-cert-hash sha256:${HASH}"

    # Enregistrement des informations dans le fichier
    echo "IP du master: $MASTER_IP" > "$OUTPUT_FILE"
    echo "Token: $TOKEN" >> "$OUTPUT_FILE"
    echo "Hash: $HASH" >> "$OUTPUT_FILE"
    echo "Commande: $JOIN_CMD" >> "$OUTPUT_FILE"

    echo "Informations enregistrées dans $OUTPUT_FILE."
    echo "Voici la commande à exécuter sur un worker :"
    echo "$JOIN_CMD"

elif [[ "$NODE_TYPE" == "w" ]]; then
    # Si on est sur le worker, vérifier si le fichier existe
    if [[ -f "$OUTPUT_FILE" ]]; then
        # Lire les informations du fichier
        source "$OUTPUT_FILE"

        # Génération de la commande
        JOIN_CMD="sudo kubeadm join ${MASTER_IP}:6443 --token ${TOKEN} --discovery-token-ca-cert-hash sha256:${HASH}"

        echo "Informations récupérées depuis $OUTPUT_FILE :"
        echo "IP du master: $MASTER_IP"
        echo "Token: $TOKEN"
        echo "Hash: $HASH"
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
    else
        echo "Le fichier $OUTPUT_FILE n'existe pas. Veuillez exécuter le script sur le master d'abord."
    fi
else
    echo "Option invalide. Veuillez choisir 'm' pour master ou 'w' pour worker."
    exit 1
fi