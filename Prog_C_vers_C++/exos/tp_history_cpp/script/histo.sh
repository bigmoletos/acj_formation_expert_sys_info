#!/bin/bash
# Ce script permet de récupérer l'historique en le nettoyant et en retirant les doublons

# Vérifier si l'utilisateur a demandé de l'aide
if [[ "$1" == "--help" || "$1" == "--h" || "$1" == "-h" || "$1" == "-H" ]]; then
    echo "Utilisation : $0 [NOMBRE_LIGNES]"
    echo
    echo "Ce script récupère les dernières commandes de l'historique, les nettoie,"
    echo "et les enregistre dans deux fichiers texte."
    echo
    echo "Arguments :"
    echo "  NOMBRE_LIGNES    Nombre de lignes d'historique à récupérer (par défaut : 100)"
    echo
    echo "Exemples :"
    echo "  $0              Récupère les 100 dernières lignes de l'historique"
    echo "  $0 20           Récupère les 20 dernières lignes de l'historique"
    exit 0
fi

# Chemin du fichier de destination
output_file="fichier_historique"
output_file_sans_doublon="${output_file}_sans_doublon"
extension=".txt"

# Définir le nombre de lignes par défaut ou utiliser l'argument
nombre_ligne=${1:-100}

# Forcer la mise à jour de l'historique dans le fichier ~/.bash_history
history -a

# Lire les dernières lignes de ~/.bash_history et ajouter dans le fichier de sortie
tail -n "$nombre_ligne" ~/.bash_history | sed 's/^[[:space:]]*[0-9]\+[[:space:]]\+//' | grep . >> "$output_file$extension"

# Supprimer les doublons en gardant l'ordre d'apparition et écrire dans le fichier sans doublons
awk '!seen[$0]++' "$output_file$extension" > "$output_file_sans_doublon$extension"

# Message de confirmation
echo "Fichiers: '$output_file$extension' et '$output_file_sans_doublon$extension' sauvegardés."
