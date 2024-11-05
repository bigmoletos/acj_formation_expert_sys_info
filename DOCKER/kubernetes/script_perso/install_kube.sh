#!/bin/bash


# Ajout du dépôt Kubernetes
echo "Ajout du dépôt Kubernetes..."
echo "deb [signed-by=/usr/share/keyrings/cloud.google.gpg] https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list

# Mise à jour des paquets
echo "Mise à jour des paquets..."
sudo apt-get update

# Installation des paquets Kubernetes
echo "Installation de kubelet, kubeadm et kubectl..."
sudo apt-get install -y kubelet kubeadm kubectl
sudo apt-get install -y apt-transport-https ca-certificates curl gnupg

# Création du répertoire pour les clés APT
sudo mkdir -p /etc/apt/keyrings

# Ajout de la clé GPG
echo "Ajout de la clé GPG..."
curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.31/deb/Release.key | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpg
sudo chmod 644 /etc/apt/keyrings/kubernetes-apt-keyring.gpg

# Ajout du dépôt avec la clé
echo "Ajout du dépôt avec la clé..."
echo "deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.31/deb/ /" | sudo tee /etc/apt/sources.list.d/kubernetes.list
sudo chmod 644 /etc/apt/sources.list.d/kubernetes.list

# Mise à jour des paquets à nouveau
echo "Mise à jour des paquets après ajout du dépôt..."
sudo apt-get update

# Réinstallation des paquets Kubernetes
echo "Réinstallation de kubelet, kubeadm et kubectl..."
sudo apt-get install -y kubelet kubeadm kubectl

# Démarrage du service kubelet
echo "Démarrage du service kubelet..."
sudo snap start kubelet && sudo snap services kubelet

# Modification du fichier config.yaml
echo "Modification du fichier /var/lib/kubelet/config.yaml..."
sudo nano /var/lib/kubelet/config.yaml <<EOF
containerRuntimeEndpoint: "unix:///var/run/containerd/containerd.sock"  # Ajouté
podInfraContainerImage: "k8s.gcr.io/pause:3.8"  # Ajouté
EOF

# Mise à jour ou ajout des paramètres dans config.yaml
echo "Mise à jour des paramètres dans /var/lib/kubelet/config.yaml..."
sudo sed -i '/^containerRuntimeEndpoint:/c\containerRuntimeEndpoint: "unix:///var/run/containerd/containerd.sock"' /var/lib/kubelet/config.yaml
sudo sed -i '/^podInfraContainerImage:/c\podInfraContainerImage: "k8s.gcr.io/pause:3.8"' /var/lib/kubelet/config.yaml
sudo sed -i '/^cgroupDriver:/c\cgroupDriver: systemd' /var/lib/kubelet/config.yaml

# Vérification des modifications
echo "Vérification des modifications dans /var/lib/kubelet/config.yaml..."
cat /var/lib/kubelet/config.yaml | grep -E 'containerRuntimeEndpoint|podInfraContainerImage|cgroupDriver'

# Changement des permissions du fichier config.yaml
echo "Changement des permissions du fichier /var/lib/kubelet/config.yaml..."
sudo chown root:root /var/lib/kubelet/config.yaml
sudo chmod 644 /var/lib/kubelet/config.yaml

# Arrêt et désactivation du service kubelet
echo "Arrêt et désactivation du service kubelet..."
sudo systemctl stop kubelet
sudo systemctl disable kubelet

# Fonction pour vérifier et libérer le port 10250
release_port() {
    echo "Vérification du port 10250..."
    while sudo lsof -i :10250 > /dev/null; do
        echo "Le port 10250 est occupé. Tentative de libération..."
        sudo fuser -k 10250/tcp
        sleep 1  # Attendre 1 seconde avant de vérifier à nouveau
    done
    echo "Le port 10250 est maintenant libre."
}

# Appel de la fonction pour libérer le port
release_port
# Redémarrage du service kubelet
echo "Redémarrage du service kubelet..."
sudo systemctl daemon-reload
sudo systemctl restart kubelet

# Arrêt et désactivation du service snap.kubelet.daemon.service
echo "Arrêt et désactivation du service snap.kubelet.daemon.service..."
sudo systemctl stop snap.kubelet.daemon.service
sudo systemctl disable snap.kubelet.daemon.service

# Fin du script
echo "Script terminé."