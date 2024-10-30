#!/bin/bash
# Ce script nettoie la variable PATH en supprimant les doublons.

# Affiche le PATH actuel pour référence
echo "PATH avant nettoyage:"
echo "$PATH"
echo

# Supprime les doublons dans PATH et met à jour la variable
export PATH=$(echo "$PATH" | awk -v RS=':' '!seen[$0]++' | paste -sd ':' -)

# Affiche le PATH après nettoyage
echo "PATH après nettoyage:"
echo "$PATH"
