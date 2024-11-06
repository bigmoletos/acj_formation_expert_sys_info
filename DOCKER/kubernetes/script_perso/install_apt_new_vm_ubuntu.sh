#!/bin/bash

: << 'END_DOC'
Script d'installation de paquets pour Ubuntu.

Ce script permet d'installer une liste de paquets spécifiée dans un fichier texte sur une nouvelle VM Ubuntu.
Il vérifie si chaque paquet est déjà installé avant de tenter de l'installer.

Usage:
  ./install_apt_new_vm_ubuntu.sh <path_to_package_list.txt> [-y]

Arguments:
  <path_to_package_list.txt> : Chemin vers le fichier contenant la liste des paquets à installer.
  -y                          : (Optionnel) Installer les paquets sans demander de confirmation.

Exemples:
  ./install_apt_new_vm_ubuntu.sh liste_apt_installed_manualy.txt
  ./install_apt_new_vm_ubuntu.sh liste_apt_installed_manualy.txt -y
END_DOC

# Vérification de l'argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <path_to_package_list.txt>"
    exit 1
fi

PACKAGE_LIST_FILE="$1"

# Vérification de l'existence du fichier
if [ ! -f "$PACKAGE_LIST_FILE" ]; then
    echo "Le fichier $PACKAGE_LIST_FILE n'existe pas."
    exit 1
fi

# Fonction d'aide
function show_help {
    echo "Script d'installation de paquets pour Ubuntu."
    echo "Usage: $0 <path_to_package_list.txt> [-y]"
    echo "Options:"
    echo "  -y    Installer les paquets sans confirmation."
}

# Vérification de l'option -y
FORCE_INSTALL=false
if [[ "$2" == "-y" ]]; then
    FORCE_INSTALL=true
fi

# Lecture du fichier de paquets et installation
while IFS= read -r package; do
    # Vérification si le paquet est déjà installé
    if dpkg -l | grep -q "^ii  $package"; then
        echo "Le paquet '$package' est déjà installé."
    else
        echo "Installation du paquet '$package'..."
        if $FORCE_INSTALL; then
            sudo apt-get install -y "$package"
        else
            sudo apt-get install "$package"
        fi
    fi
done < "$PACKAGE_LIST_FILE"

echo "Installation terminée."