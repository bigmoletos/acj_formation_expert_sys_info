#!/bin/bash

# Activer le service kubelet pour qu'il démarre au démarrage
echo "Activation du service kubelet..."
sudo systemctl enable kubelet

# Vérification de l'état du service kubelet
echo "État du service kubelet :"
sudo systemctl status kubelet