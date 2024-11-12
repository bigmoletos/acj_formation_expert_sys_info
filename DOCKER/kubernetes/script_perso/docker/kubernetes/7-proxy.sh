#!/bin/bash

# Docstring
# Ce script démarre le kube-proxy avec la configuration spécifiée.
# Il utilise des variables pour éviter les valeurs "dures" dans le code.
# Assurez-vous que le fichier de configuration admin.conf est présent dans le répertoire courant.

# Variables
# KUBE_PROXY_BIN="sudo bin/kube-proxy"  # Chemin vers l'exécutable kube-proxy avec élévation de privilèges
# KUBE_CONFIG="admin.conf"  # Fichier de configuration pour kube-proxy
# Variables pour le répertoire personnel
USER_HOME="$HOME" # Définition du répertoire personnel de l'utilisateur
KUBE_PROXY_BIN="sudo ${USER_HOME}/bin/kube-proxy"  # Chemin vers l'exécutable kube-proxy avec élévation de privilèges
KUBE_CONFIG="${USER_HOME}/admin.conf"  # Fichier de configuration pour kube-proxy

# Fonction d'aide
function usage() {
    echo "Usage: $0"
    echo "Ce script démarre le kube-proxy avec la configuration spécifiée."
    exit 1
}

# Vérification des arguments
if [ "$#" -ne 0 ]; then
    usage
fi

# Démarrer kube-proxy
$KUBE_PROXY_BIN --kubeconfig $KUBE_CONFIG

# Commentaires pour les commandes kubectl
# kubectl apply -f service.yaml  # Appliquer la configuration du service
# try this
# kubectl expose deployment web --port=80  # Exposer le déploiement web sur le port 80
# kubectl get svc  # Obtenir la liste des services
