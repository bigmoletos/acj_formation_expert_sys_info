#!/bin/bash

"""
Script de configuration d'une adresse IP statique sur une VM.

Ce script permet de configurer une adresse IP statique pour l'interface réseau `enp0s3` en utilisant Netplan.
Il vérifie d'abord s'il existe d'autres fichiers Netplan configurant `enp0s3` pour éviter les conflits, puis
permet à l'utilisateur de saisir l'adresse IP statique et l'adresse de la passerelle. La configuration est
ensuite appliquée.

Fonctionnalités :
- Vérification de la présence d'autres fichiers YAML de configuration pour `enp0s3`.
- Demande interactive à l'utilisateur pour obtenir l'adresse IP et la passerelle.
- Création d'un fichier Netplan pour appliquer la nouvelle configuration.

Utilisation :
- Exécuter le script et suivre les instructions interactives.
- Utiliser l'option -h ou --help pour obtenir des informations d'utilisation.

"""
# Variables pour le répertoire personnel
USER_HOME="$HOME/$USER" # Définition du répertoire personnel de l'utilisateur
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

# Vérifier la présence d'autres fichiers YAML configurant l'interface enp0s3
conflict_files=$(grep -rl "enp0s3" /etc/netplan/*.yaml)

if [[ -n "$conflict_files" ]]; then
    echo "Erreur : D'autres fichiers de configuration Netplan définissent déjà des paramètres pour l'interface 'enp0s3'."
    echo "Fichiers en conflit :"
    echo "$conflict_files"
    echo "Veuillez supprimer ou modifier ces fichiers avant de continuer."
    exit 1
fi

# Récupérer l'adresse IP actuelle de l'interface réseau
CURRENT_IP=$(ip -4 addr show enp0s3 | grep -oP '(?<=inet\s)\d+(\.\d+){3}')

# Récupérer l'adresse IP de la passerelle par défaut
GATEWAY_IP=$(ip route | grep default | awk '{print $3}')

# Demande à l'utilisateur l'adresse IP à configurer
read -p "Entrez l'adresse IP que vous souhaitez mettre en statique [$CURRENT_IP]: " STATIC_IP
STATIC_IP=${STATIC_IP:-$CURRENT_IP}  # Utiliser l'adresse IP actuelle si aucune entrée

# Demande à l'utilisateur l'adresse IP de la passerelle
read -p "Entrez l'adresse IP de la passerelle [$GATEWAY_IP]: " USER_GATEWAY_IP
GATEWAY_IP=${USER_GATEWAY_IP:-$GATEWAY_IP}  # Utiliser la passerelle par défaut si aucune entrée

# Création d'un fichier Netplan dans le répertoire personnel
cat <<EOF | sudo tee $USER_HOME/etcd/netplan/00-installer-config.yaml
network:
  version: 2
  ethernets:
    enp0s3:
      dhcp4: no
      addresses:
        - $STATIC_IP/24  # IP que l'on souhaite mettre en statique
      routes:
        - to: default
          via: $GATEWAY_IP  # Utiliser la passerelle définie par l'utilisateur ou la valeur par défaut
      nameservers:
        addresses:
          - 8.8.8.8
EOF

# Appliquer la configuration
sudo netplan apply

echo "Configuration de l'IP statique terminée."
