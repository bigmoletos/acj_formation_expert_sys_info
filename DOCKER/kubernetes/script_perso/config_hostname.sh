#!/bin/bash

# Variables globales
LOG_FILE="hostname_config.log"
SUMMARY_FILE="hostname_config_summary.md"

# Fonction pour logger les actions
log_action() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a $LOG_FILE
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> $SUMMARY_FILE
}

# Vérification des droits root
if [ "$EUID" -ne 0 ]; then
    echo "Ce script doit être exécuté en tant que root"
    exit 1
fi

# Configuration du hostname
read -p "Entrez le nouveau hostname (master/worker1/worker2) : " new_hostname

# Validation du hostname
case $new_hostname in
    master|worker1|worker2)
        # Modification du hostname
        hostnamectl set-hostname $new_hostname
        echo "127.0.0.1 $new_hostname" >> /etc/hosts
        log_action "Hostname configuré : $new_hostname"

        echo "Hostname configuré. Le shell va être rechargé."
        exec bash
        ;;
    *)
        echo "Hostname invalide. Utilisez master, worker1 ou worker2"
        exit 1
        ;;
esac 