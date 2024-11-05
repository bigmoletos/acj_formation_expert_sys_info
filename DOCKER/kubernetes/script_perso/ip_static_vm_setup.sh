#!/bin/bash

# Fonction d'aide
show_help() {
    echo "Usage: $0 [options]"
    echo
    echo "Ce script permet de paramétrer une IP statique sur la VM."
    echo
    echo "Options:"
    echo "  -h, --help     Affiche cette aide"
}

# Afficher l'aide si demandé
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    show_help
    exit 0
fi

# Récupérer l'adresse IP actuelle de l'interface réseau
CURRENT_IP=$(ip -4 addr show enp0s3 | grep -oP '(?<=inet\s)\d+(\.\d+){3}')

# Récupérer l'adresse IP de la passerelle par défaut
# GATEWAY_IP=$(ip route | grep default | awk '{print $3}')
GATEWAY_IP=$(ip route | grep default)

# Demande à l'utilisateur l'adresse IP à configurer
read -p "Entrez l'adresse IP que vous souhaitez mettre en statique [$CURRENT_IP]: " STATIC_IP
STATIC_IP=${STATIC_IP:-$CURRENT_IP}  # Utiliser l'adresse IP actuelle si aucune entrée

# Demande à l'utilisateur l'adresse IP de la passerelle
read -p "Entrez l'adresse IP de la passerelle [$GATEWAY_IP]: " USER_GATEWAY_IP
GATEWAY_IP=${USER_GATEWAY_IP:-$GATEWAY_IP}  # Utiliser la passerelle par défaut si aucune entrée

# Création du fichier de configuration Netplan
cat <<EOF | sudo tee /etc/netplan/00-installer-config.yaml
network:
  version: 2
  ethernets:
    enp0s3:
      dhcp4: no
      addresses:
        - $STATIC_IP/24  # IP que l'on souhaite mettre en statique
      routes:
        - to: default
          via: 192.168.1.255  # IP de la box
      nameservers:
        addresses:
          - 8.8.8.8
EOF

# Appliquer la configuration
sudo netplan apply

echo "Configuration de l'IP statique terminée."