#!/bin/bash

# Docstring
# Ce script démarre le processus containerd pour la gestion des conteneurs.
# Il utilise des variables pour toutes les valeurs configurables afin de faciliter la maintenance.

# Variables
CONTAINERD_BIN="bin/containerd"  # Chemin vers l'exécutable containerd

# Fonction d'aide
function usage() {
    echo "Usage: $0"
    echo "Ce script démarre le processus containerd."
    exit 1
}

# Vérification des arguments
if [ "$#" -ne 0 ]; then
    usage
fi

# Démarrer le processus containerd
sudo $CONTAINERD_BIN