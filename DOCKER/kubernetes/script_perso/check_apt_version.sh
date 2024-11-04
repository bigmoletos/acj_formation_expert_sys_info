#!/bin/bash

# Variables
LOG_FILE="apt_versions.log"

# Fonction pour logger les actions
log_action() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a $LOG_FILE
}

# Fonction pour vérifier les versions des paquets
check_package_versions() {
    log_action "Vérification des versions des paquets requis..."

    local packages=("conntrack" "ethtool" "crictl" "kubeadm" "kubelet" "kubectl" "docker" "snapd")
    for pkg in "${packages[@]}"; do
        if dpkg -s $pkg &> /dev/null; then
            local version=$(dpkg -s $pkg | grep Version | awk '{print $2}')
            log_action "Paquet: $pkg, Version: $version"
        else
            if [ "$pkg" = "docker" ]; then
                if command -v docker &> /dev/null; then
                    local version=$(docker --version | awk '{print $3}' | sed 's/,//')
                    log_action "Paquet: $pkg, Version: $version"
                else
                    log_action "Paquet: $pkg non installé"
                fi
            else
                log_action "Paquet: $pkg non installé"
            fi
        fi
    done
}

# Script principal
main() {
    # Vérification des droits root
    if [ "$EUID" -ne 0 ]; then
        echo "Ce script doit être exécuté en tant que root"
        exit 1
    fi

    # Vérification des versions des paquets
    check_package_versions
}

# Lancement du script
main
