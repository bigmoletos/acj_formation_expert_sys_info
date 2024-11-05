#!/bin/bash

# Fichier de configuration Docker
DOCKER_CONFIG="/etc/docker/daemon.json"

# Vérifier si le fichier de configuration existe
if [ ! -f "$DOCKER_CONFIG" ]; then
    echo "Le fichier $DOCKER_CONFIG n'existe pas. Création du fichier avec la configuration par défaut."
    echo '{}' | sudo tee "$DOCKER_CONFIG" > /dev/null
fi

# Vérifier si l'option exec-opts existe déjà
if grep -q '"exec-opts"' "$DOCKER_CONFIG"; then
    echo "L'option 'exec-opts' existe déjà dans $DOCKER_CONFIG."
else
    # Ajouter l'option exec-opts
    echo "Ajout de l'option 'exec-opts' à $DOCKER_CONFIG."
    sudo jq '. + {"exec-opts": ["native.cgroupdriver=systemd"]}' "$DOCKER_CONFIG" | sudo tee "$DOCKER_CONFIG" > /dev/null
fi

# Redémarrer les services Docker et Kubelet
echo "Redémarrage des services Docker et Kubelet..."
sudo systemctl daemon-reload
sudo systemctl restart docker
sudo systemctl restart kubelet

# Vérification de la configuration
echo "Vérification de la configuration Docker..."
docker info | grep -i cgroup

echo "Configuration terminée."