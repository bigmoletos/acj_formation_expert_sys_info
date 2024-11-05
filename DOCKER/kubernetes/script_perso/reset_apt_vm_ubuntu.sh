#!/bin/bash

: <<'END_DOC'
Ce script permet de réinitialiser les paquets installés manuellement sur une machine virtuelle Ubuntu.

Fonctionnalités :
- Liste les paquets installés manuellement.
- Compare cette liste avec les paquets inclus dans l'installation minimale d'Ubuntu.
- Propose de supprimer les paquets installés par l'utilisateur.

Usage :
  ./reset_apt_vm_ubuntu.sh [options]

Options :
  -h, --help    Affiche cette aide.
  -a, --all     Supprime tous les paquets sans confirmation.
  -s, --single   Supprime les paquets un par un.
END_DOC

# Fonction pour afficher un message d'information
log_action() {
    echo "[INFO] $1"
}

# Fonction d'aide
show_help() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -h, --help    Affiche cette aide"
    echo "  -a, --all     Supprime tous les paquets sans confirmation"
    echo "  -s, --single   Supprime les paquets un par un"
    echo ""
    echo "Ce script"
    echo "  - Liste les paquets installés manuellement, puis"
    echo "  - Compare cette liste avec ceux inclus dans l’installation minimale d’Ubuntu et"
    echo "  - Supprime ceux installés par l'utilisateur."
}

# Vérification des arguments
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    show_help
    exit 0
fi

# Fichiers de sortie
APT_LISTE_APT_MANUALY="liste_apt_installed_manualy.txt"
APT_LISTE_APT_MINIMALE="liste_apt_minimal_installed_ubuntu.txt"
APT_LISTE_APT_MINIMALE_DEFAULT="liste_paquets_minimale.txt"
APT_LISTE_APT_COMPARED="liste_apt_compared_to_desintall.txt"
APT_DELETED_FILE="apt_deleted.txt"
CHOIX="n"  # choix par defaut

# Lister les paquets installés manuellement
log_action "Lister les paquets installés manuellement sur la VM Ubuntu"
apt-mark showmanual | sort > $APT_LISTE_APT_MANUALY
log_action "Les paquets installés manuellement ont été enregistrés dans $APT_LISTE_APT_MANUALY"

# Vérifier si le fichier minimal d'Ubuntu existe
if [ -f /usr/share/ubuntu-server-seeds/minimal ]; then
    log_action "Le fichier minimal d'Ubuntu est présent. Liste des paquets d'installation minimale sur Ubuntu."
    grep -o '^[^#]*' /usr/share/ubuntu-server-seeds/minimal | sort > $APT_LISTE_APT_MINIMALE
    log_action "Les paquets d'installation minimale ont été enregistrés dans $APT_LISTE_APT_MINIMALE"
else
    log_action "Le fichier minimal d'Ubuntu n'est pas présent. Utilisation de $APT_LISTE_APT_MINIMALE_DEFAULT."
    sort $APT_LISTE_APT_MINIMALE_DEFAULT > $APT_LISTE_APT_MINIMALE
    log_action "Les paquets d'installation minimale par défaut ont été enregistrés dans $APT_LISTE_APT_MINIMALE"
fi

# Comparer avec la liste des paquets d'installation minimale
log_action "Comparer la liste des paquets installés manuellement avec ceux inclus dans l’installation minimale d’Ubuntu"
comm -23 <(sort $APT_LISTE_APT_MANUALY) <(sort $APT_LISTE_APT_MINIMALE) > $APT_LISTE_APT_COMPARED
log_action "La comparaison a été enregistrée dans $APT_LISTE_APT_COMPARED"

# Supprimer les paquets installés par l'utilisateur
log_action "Supprimer les paquets installés par l'utilisateur."
read -p "Voulez-vous supprimer les paquets installés manuellement (o/n) ? Attention, cette action est irréversible. [Défaut: n] " CHOIX

# Si l'utilisateur ne répond pas, utiliser le choix par défaut
CHOIX=${CHOIX:-n}

# Vérifier les paquets à supprimer
PAQUETS_A_SUPPRIMER=$(comm -23 <(sort $APT_LISTE_APT_MANUALY) <(sort $APT_LISTE_APT_MINIMALE))

if [[ "$1" == "-a" || "$1" == "--all" ]]; then
    log_action "Suppression de tous les paquets installés manuellement sans confirmation."

    # Vérifier si des paquets essentiels sont dans la liste
    ESSENTIELS=$(echo "$PAQUETS_A_SUPPRIMER" | grep -E '^(base-passwd|libdebconfclient0)$')

    if [ -n "$ESSENTIELS" ]; then
        log_action "Avertissement : Les paquets essentiels suivants seront supprimés : $ESSENTIELS"
        log_action "Cette action peut rendre votre système instable."
        read -p "Êtes-vous sûr de vouloir continuer malgré cet avertissement ? (o/n) " CONFIRMATION
        if [ "$CONFIRMATION" != "o" ]; then
            log_action "Suppression annulée par l'utilisateur."
            exit 0
        fi
    fi

    echo "$PAQUETS_A_SUPPRIMER" | xargs sudo apt-get -y remove
    echo "$PAQUETS_A_SUPPRIMER" > $APT_DELETED_FILE
    log_action "Tous les paquets installés manuellement ont été supprimés et enregistrés dans $APT_DELETED_FILE."
    exit 0
elif [[ "$1" == "-s" || "$1" == "--single" ]]; then
    log_action "Suppression des paquets un par un."
    for PAQUET in $PAQUETS_A_SUPPRIMER; do
        # Vérifier si le paquet est essentiel
        if echo "$PAQUET" | grep -E '^(base-passwd|libdebconfclient0)$' > /dev/null; then
            log_action "Avertissement : Le paquet essentiel $PAQUET ne sera pas supprimé."
            continue
        fi

        read -p "Voulez-vous supprimer le paquet $PAQUET ? (o/n) " CONFIRMATION
        if [[ "$CONFIRMATION" == "o" ]]; then
            sudo apt-get remove -y "$PAQUET"
            echo "$PAQUET" >> $APT_DELETED_FILE
            log_action "Le paquet $PAQUET a été supprimé."
        else
            log_action "Le paquet $PAQUET n'a pas été supprimé."
        fi
    done
    log_action "La suppression des paquets un par un est terminée."
else
    if [ "$CHOIX" == "o" ]; then
        log_action "Suppression des paquets installés manuellement."
        echo "$PAQUETS_A_SUPPRIMER" | xargs sudo apt-get -y remove
        echo "$PAQUETS_A_SUPPRIMER" > $APT_DELETED_FILE
        log_action "Les paquets installés manuellement ont été supprimés et enregistrés dans $APT_DELETED_FILE."
    else
        log_action "Commande non exécutée. Vous pouvez la copier et l'exécuter manuellement."
    fi
fi

# INFO
# comm -23 : La commande comm compare deux fichiers ou listes, ligne par ligne, et affiche les différences. Elle fonctionne uniquement avec des fichiers (ou listes) triés par ordre alphabétique. Elle a trois options principales :
# -2 : Supprime les lignes qui sont seulement dans le fichier 2 de la sortie.
# -3 : Supprime les lignes qui sont communes aux deux fichiers de la sortie.