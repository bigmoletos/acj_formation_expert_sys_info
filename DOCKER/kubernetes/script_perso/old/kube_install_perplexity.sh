#!/bin/bash

# Variables globales
LOG_FILE="k8s_setup.log"
AUTO_APPROVE=false
NODE_TYPE=""
MASTER_IP=""
MASTER_HOSTNAME="master"
WORKER_HOSTNAME_PREFIX="worker"

# Versions cibles
TARGET_CONNTRACK_VERSION="1:1.4.5-2"
TARGET_ETHTOOL_VERSION="1:5.4-1"
TARGET_CRICTL_VERSION="v1.24.0"  # Version à installer pour crictl
TARGET_KUBEADM_VERSION="1.31.2-1.1"
TARGET_KUBELET_VERSION="1.31.2-1.1"
TARGET_KUBECTL_VERSION="1.31.2-1.1"
TARGET_DOCKER_VERSION="27.3.1"

# Fonction d'aide
show_help() {
    echo "Usage: $0 [-h] [-y] [-t type] [-a]"
    echo
    echo "Script de configuration Kubernetes pour master et worker nodes"
    echo
    echo "Options:"
    echo "  -h, --help        Affiche cette aide"
    echo "  -y, --yes         Mode automatique (pas de confirmation)"
    echo "  -t, --type        Type de nœud (master/worker)"
    echo "  -a, --auto        Récupérer automatiquement IP, TOKEN et HASH sur le master"
}

# Fonction pour logger les actions
log_action() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a $LOG_FILE
}

# Partie 2 : Vérification des Commandes et Gestion des Paquets
# Vérifier l'état d'une commande précédente
check_command_status() {
    if [ $? -ne 0 ]; then
        log_action "Erreur lors de l'exécution de la dernière commande."
        exit 1
    fi

# Vérifier si un paquet est installé, sinon proposer son installation
check_and_install_package() {
    local package=$1
    if ! command -v $package &> /dev/null; then
        log_action "$package n'est pas installé. Voulez-vous l'installer ? (o/n)"
        read -p "Réponse : " response
        if [[ "$response" =~ ^[oO]$ ]]; then
            apt-get update && apt-get install -y $package || { log_action "Erreur lors de l'installation de $package"; exit 1; }
            log_action "$package installé avec succès."
        else
            log_action "Installation de $package annulée."
            exit 1
        fi
    else
        log_action "$package est déjà installé."
    fi
}

# Partie 3 : Nettoyage des Installations Précédentes
# Supprimer les installations précédentes de Kubernetes et Docker
cleanup_previous_installations() {
    log_action "Suppression des installations précédentes de Kubernetes et Docker..."

    apt-get remove --purge -y kubeadm kubectl kubelet docker.io || { log_action "Erreur lors de la suppression des paquets"; exit 1; }
    apt-get autoremove -y || { log_action "Erreur lors du nettoyage des paquets"; exit 1; }

    # Suppression des fichiers de configuration restants
    rm -rf /etc/kubernetes /var/lib/etcd /var/lib/kubelet /etc/cni/net.d /etc/docker /var/run/kubernetes || { log_action "Erreur lors de la suppression des fichiers restants"; exit 1; }

    log_action "Installations précédentes supprimées avec succès."
}

# Partie 4 : Configuration du Hostname et Réseau
# Changer le hostname et mettre à jour /etc/hosts
change_hostname() {
    local new_hostname=$1

    log_action "Changement du hostname en $new_hostname..."

    # Changer le hostname
    hostnamectl set-hostname "$new_hostname"
    check_command_status

    # Mettre à jour /etc/hosts
    local ip=$(hostname -I | awk '{print $1}')

    # Backup du fichier hosts
    cp /etc/hosts /etc/hosts.bak

    # Remplacer ou ajouter l'entrée pour le nouveau hostname
    if grep -q "$new_hostname" /etc/hosts; then
        sed -i "s/.*$new_hostname/$ip $new_hostname/" /etc/hosts
    else
        echo "$ip $new_hostname" >> /etc/hosts
    fi

    log_action "Hostname changé avec succès en $new_hostname."
}

# Configuration du hostname et hosts
setup_network_config() {
    log_action "Configuration réseau..."

    if [ "$NODE_TYPE" = "master" ]; then
        read -p "*** Entrez l'IP du master: ***" MASTER_IP

        # Changement du hostname pour le master
        change_hostname "$MASTER_HOSTNAME"

    else
        read -p "*** Entrez l'IP du master: ***" MASTER_IP

        # Générer un nom de worker basé sur un numéro séquentiel ou une entrée utilisateur.
        local worker_number=""
        read -p "*** Entrez le numéro du worker (ex: 1 pour worker-1): ***" worker_number

        # Changement du hostname pour le worker
        change_hostname "${WORKER_HOSTNAME_PREFIX}-${worker_number}"

        # Ne pas redemander l'IP du master ici, elle est déjà saisie.
    fi

    log_action "/etc/hosts configuré."
}

# Partie 5 : Désactivation du Swap et Configuration Sudo
# Désactivation du swap
disable_swap() {
    log_action "Désactivation du swap..."

    swapoff -a || { log_action "Erreur lors de la désactivation du swap"; exit 1; }

    sed -i '/ swap / s/^/#/' /etc/fstab || { log_action "Erreur lors de la modification de /etc/fstab"; exit 1; }
}

# Configuration des droits sudo
setup_sudo_rights() {
    log_action "Configuration des droits sudo..."

    local username=$(whoami)

    usermod -aG sudo $username || { log_action "Erreur lors de l'ajout à sudo"; exit 1; }

    echo "$username ALL=(ALL:ALL) NOPASSWD: ALL" | sudo tee /etc/sudoers.d/$username || { log_action "Erreur lors de la modification des droits sudo"; exit 1; }
}

# Partie 6 : Configuration Containerd et Installation Docker

# Configuration de containerd
setup_containerd() {
    log_action "Configuration de containerd..."

    mkdir -p /etc/containerd || { log_action "Erreur lors de la création du répertoire containerd"; exit 1; }

    containerd config default > /etc/containerd/config.toml || { log_action "Erreur lors de la création du fichier config.toml"; exit 1; }

    sed -i 's/disabled_plugins/enabled_plugins/' /etc/containerd/config.toml || { log_action "Erreur lors de la modification du fichier config.toml"; exit 1; }

    systemctl restart containerd.service || { log_action "Erreur lors du redémarrage de containerd"; exit 1; }
}

# Installation de Docker avec vérification des dépôts et installation automatique si nécessaire.
install_docker() {
     # Vérification et ajout du dépôt Docker si nécessaire.
     if ! grep -q "^deb .*docker.com" /etc/apt/sources.list; then
         apt-get update && apt-get install -y \
             apt-transport-https \
             ca-certificates \
             curl \
             software-properties-common || { log_action "Erreur lors de la mise à jour des paquets"; exit 1; }

         curl -fsSL https://download.docker.com/linux/ubuntu/gpg | apt-key add - || { log_action "Erreur lors de l'ajout de la clé GPG"; exit 1; }

         add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" || { log_action "Erreur lors de l'ajout du dépôt Docker"; exit 1; }

         apt-get update || { log_action "Erreur lors de la mise à jour des paquets après ajout du dépôt"; exit 1; }

         check_and_install_package docker.io || { log_action "Erreur lors de l'installation automatique de Docker"; exit 1; }

     else
         check_and_install_package docker.io
     fi
}

# Partie 7 : Installation Kubernetes et Initialisation
# Installation de Kubernetes via snap.
install_kubernetes() {
   log_action "Installation de Kubernetes..."

   # Installation des composants K8s via snap si nécessaire
   for package in kubectl kubeadm kubelet; do
       if ! snap list | grep -q "$package"; then
           snap install $package --classic || { log_action "Erreur lors de l'installation des composants Kubernetes"; exit 1; }
           log_action "$package installé."
       else
           log_action "$package est déjà installé."
       fi
   done

   # Configuration du service kubelet
   cat > /etc/systemd/system/kubelet.service << EOF
[Unit]
Description=kubelet: The Kubernetes Node Agent
Documentation=https://kubernetes.io/docs/
Wants=network-online.target
After=network-online.target

[Service]
ExecStart=/snap/bin/kubelet
Restart=always
StartLimitInterval=0
RestartSec=10

[Install]
WantedBy=multi-user.target
EOF

   systemctl daemon-reload || { log_action "Erreur lors du rechargement des services systemd"; exit 1; }
   systemctl enable kubelet || { log_action "Erreur lors de l'activation du service kubelet"; exit 1; }
   systemctl start kubelet || { log_action "Erreur lors du démarrage du service kubelet"; exit 1; }
}

# Initialisation du master.
init_master() {
   log_action "Initialisation du master node..."

   kubeadm init --pod-network-cidr=10.244.0.0/16 --apiserver-advertise-address=$MASTER_IP || { log_action "Erreur lors de l'initialisation du master"; exit 1; }

   # Configuration kubectl pour l'utilisateur courant.
   mkdir -p $HOME/.kube
   cp -i /etc/kubernetes/admin.conf $HOME/.kube/config || { log_action "Erreur lors de la configuration kubectl"; exit 1; }
   chown $(id -u):$(id -g) $HOME/.kube/config

   # Configuration réseau
   modprobe br_netfilter || { log_action "Erreur lors du chargement du module br_netfilter"; exit 1; }
   echo 'net.bridge.bridge-nf-call-iptables=1' >> /etc/sysctl.conf || { log_action "Erreur lors de la modification de sysctl.conf"; exit 1; }
   sysctl -p || { log_action "Erreur lors du rechargement des paramètres sysctl"; exit 1; }

   # Installation Flannel
   kubectl apply -f https://raw.githubusercontent.com/flannel-io/flannel/master/Documentation/kube-flannel.yml || { log_action "Erreur lors de l'installation Flannel"; exit 1; }

   # Récupération des informations pour le join
   local token=$(kubeadm token list | awk 'NR==2 {print $1}')
   local hash=$(openssl x509 -in /etc/kubernetes/pki/ca.crt -noout -pubkey | openssl rsa -pubin -outform DER | sha256sum | cut '-d ' '-f' '1')

   echo ""
   echo "*** Informations pour joindre le cluster : ***"
   echo ""
   echo "kubeadm join ${MASTER_IP}:6443 --token $token --discovery-token-ca-cert-hash sha256:$hash"
}

# Configuration du worker.
setup_worker() {
   log_action "Configuration du worker node..."

   read -p "*** Entrez le token: ***" TOKEN
   read -p "*** Entrez le hash: ***" HASH

   kubeadm join ${MASTER_IP}:6443 --token $TOKEN --discovery-token-ca-cert-hash sha256:$HASH || { log_action "Erreur lors de la jonction au cluster en tant que worker"; exit 1; }
}

# Partie Finale : Vérifications et Exécution Principale
# Vérification des prérequis avant d'exécuter kubeadm join sur le worker.
check_worker_requirements() {
    log_action "Vérification des prérequis pour le worker..."

    check_and_install_package conntrack
    check_and_install_package crictl
    check_and_install_package ethtool

    if ! ss -tuln | grep ':10250'; then
        log_action "*** Port 10250 est libre. ***"
    else
        log_action "*** Port 10250 est déjà utilisé. Veuillez vérifier quel service utilise ce port. ***"
        exit 1;
    fi
}

# Vérification de l'état du cluster après initialisation ou jonction d'un worker.
check_cluster_status() {
    log_action "Vérification de l'état du cluster..."

    kubectl get nodes -o wide || { log_action "Erreur lors de la récupération des nœuds"; exit 1; }
    kubectl get pods --all-namespaces || { log_action "Erreur lors de la récupération des pods dans tous les namespaces"; exit 1; }
}

# Script principal.
main() {
     # Vérification des droits root
     if [ "$EUID" -ne 0 ]; then
         echo "*** Ce script doit être exécuté en tant que root ***"
         exit 1
     fi

     # Demande du type de nœud si non spécifié
     if [ -z "$NODE_TYPE" ]; then
         read -p "*** Type de nœud (master/worker): ***" NODE_TYPE
         if [[ ! "$NODE_TYPE" =~ ^(master|worker)$ ]]; then
             echo "*** Type invalide. Veuillez entrer 'master' ou 'worker'. ***"
             exit 1
         fi
     fi

     # Exécution des étapes communes
     cleanup_previous_installations # Ajout d'une étape pour nettoyer les installations précédentes.
     setup_network_config
     disable_swap
     setup_sudo_rights
     setup_containerd

     install_docker

     install_kubernetes

     # Exécution spécifique selon le type de nœud
     if [ "$NODE_TYPE" = "master" ]; then
         init_master
         check_cluster_status
     else
         check_worker_requirements # Vérification avant jonction comme worker.
         setup_worker
     fi
}

# Traitement des arguments
while [[ $# -gt 0 ]]; do
case $1 in
-h|--help)
     show_help
     exit 0
;;
-y|--yes)
     AUTO_APPROVE=true
     shift
;;
-t|--type)
     NODE_TYPE="$2"
     shift 2
;;
-a|--auto)
     if [ "$NODE_TYPE" = 'master' ]; then
         echo "*** Récupération automatique des informations IP, TOKEN et HASH... ***"
         MASTER_IP=$(hostname -I | awk '{print $1}')
         TOKEN=$(kubeadm token list | awk 'NR==2 {print $1}')
         HASH=$(openssl x509 -in /etc/kubernetes/pki/ca.crt -noout -pubkey | openssl rsa -pubin -outform DER | sha256sum | cut '-d ' '-f' '1')
         echo "*** IP: ${MASTER_IP} ***"
         echo "*** TOKEN: ${TOKEN} ***"
         echo "*** HASH: ${HASH} ***"
     else
         echo "*** L'option auto ne peut être utilisée que sur un nœud master. ***"
         exit 1
     fi
shift
;;
*)
     echo "*** Option invalide: $1 ***"
     show_help
     exit 1
;;
esac
done

# Lancement du script

main
