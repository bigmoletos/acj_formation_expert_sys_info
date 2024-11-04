#!/bin/bash

# Variables globales
LOG_FILE="k8s_setup.log"
SUMMARY_FILE="k8s_setup_summary.md"
AUTO_APPROVE=false
FORCE_REINSTALL=false
NODE_TYPE=""
MASTER_IP=""
MASTER_HOSTNAME="master"
WORKER_HOSTNAME="worker"

# Fonction d'aide
show_help() {
    echo "Usage: $0 [-h] [-y] [-f] [-t type]"
    echo
    echo "Script de configuration Kubernetes pour master et worker nodes"
    echo
    echo "Options:"
    echo "  -h, --help        Affiche cette aide"
    echo "  -y, --yes         Mode automatique (pas de confirmation)"
    echo "  -f, --force       Force la réinstallation"
    echo "  -t, --type        Type de nœud (master/worker)"
    echo
    echo "Exemples:"
    echo "  $0 -t master      Configure un nœud master"
    echo "  $0 -t worker      Configure un nœud worker"
    echo "  $0 -t worker -y   Configure un worker en mode automatique"
}

# Fonction pour logger les actions
log_action() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a $LOG_FILE
}

# Fonction de confirmation
confirm() {
    if [ "$AUTO_APPROVE" = true ]; then
        return 0
    fi
    local message="${1:-Continuer ?}"
    read -p "$message (o/n) : " response
    [[ "$response" =~ ^[oO]$ ]]
}

# Fonction de vérification des erreurs
check_command_success() {
    if [ $? -ne 0 ]; then
        log_action "Erreur lors de l'exécution de la dernière commande. Abandon du script."
        exit 1
    fi
}

# Fonction pour lire les logs en cas d'erreur
check_logs_on_failure() {
    local log_file=$1
    if [ -f "$log_file" ]; then
        log_action "Affichage des 20 dernières lignes du fichier $log_file :"
        tail -n 20 $log_file | tee -a $LOG_FILE
    else
        log_action "Aucun fichier de log trouvé pour $log_file."
    fi
}

# Fonction de gestion des erreurs APT
handle_apt_errors() {
    local output="$1"
    if echo "$output" | grep -q "404  Not Found"; then
        log_action "Erreur: Dépôt non trouvé lors de la mise à jour APT. Vérifiez les sources du dépôt."
        exit 1
    fi
    if echo "$output" | grep -q "E:"; then
        log_action "Erreur APT: $(echo "$output" | grep "E:")"
        exit 1
    fi
}

# Vérification des prérequis
check_prerequisites() {
    log_action "Vérification des prérequis..."

    # Ajouter le dépôt Kubernetes si nécessaire
    if ! grep -q "kubernetes" /etc/apt/sources.list /etc/apt/sources.list.d/*; then
        log_action "Ajout du dépôt Kubernetes..."
        curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | apt-key add -
        cat <<EOF | tee /etc/apt/sources.list.d/kubernetes.list
deb https://apt.kubernetes.io/ kubernetes-xenial main
EOF
        apt-get update
    fi

    # Vérifier la présence des dépendances nécessaires et leurs versions spécifiques
    local dependencies=(
        "conntrack:1:1.4.5-2"
        "ethtool:1:5.4-1"
        "crictl:required"
    )
    for dep_info in "${dependencies[@]}"; do
        local dep=$(echo $dep_info | cut -d: -f1)
        local required_version=$(echo $dep_info | cut -d: -f2)

        if ! command -v $dep &> /dev/null; then
            log_action "Dépendance manquante: $dep. Installation..."
            apt_output=$(apt-get update 2>&1)
            handle_apt_errors "$apt_output"
            apt_output=$(apt-get install -y $dep 2>&1)
            if [ $? -ne 0 ]; then
                log_action "Tentative d'installation de $dep depuis une source alternative..."
                if [ "$dep" = "crictl" ]; then
                    curl -LO https://github.com/kubernetes-sigs/cri-tools/releases/download/v1.23.0/crictl-v1.23.0-linux-amd64.tar.gz
                    tar -C /usr/local/bin -xzf crictl-v1.23.0-linux-amd64.tar.gz
                    rm -f crictl-v1.23.0-linux-amd64.tar.gz
                    check_command_success
                else
                    handle_apt_errors "$apt_output"
                fi
            else
                handle_apt_errors "$apt_output"
            fi
            check_command_success
        else
            local installed_version=$(dpkg -s $dep | grep Version | awk '{print $2}')
            if [ "$required_version" != "required" ] && [ "$installed_version" != "$required_version" ]; then
                log_action "Version différente pour $dep. Installation de la version requise..."
                apt_output=$(apt-get install -y $dep=$required_version 2>&1)
                handle_apt_errors "$apt_output"
                check_command_success
            fi
        fi
    done

    # Vérifier si le port 10250 est utilisé
    if lsof -i:10250 &> /dev/null; then
        log_action "Le port 10250 est déjà utilisé. Tentative de libération du port..."
        fuser -k 10250/tcp
        if lsof -i:10250 &> /dev/null; then
            log_action "Impossible de libérer le port 10250. Abandon du script."
            exit 1
        fi
    fi
}

# Configuration du hostname et hosts
setup_network_config() {
    log_action "Configuration réseau..."

    # Configuration hostname
    local new_hostname=""
    if [ "$NODE_TYPE" = "master" ]; then
        new_hostname=$MASTER_HOSTNAME
    else
        # Générer un hostname unique pour chaque worker
        WORKER_COUNT=$(grep -o "$WORKER_HOSTNAME-[0-9]*" /etc/hosts | wc -l)
        WORKER_COUNT=$((WORKER_COUNT + 1))
        new_hostname="$WORKER_HOSTNAME-$WORKER_COUNT"
    fi

    # Valider ou changer le hostname
    log_action "Changement du hostname à : $new_hostname"
    hostnamectl set-hostname $new_hostname
    check_command_success

    # Configuration /etc/hostname
    echo "$new_hostname" > /etc/hostname
    check_command_success

    # Configuration /etc/hosts
    echo "Configuration de /etc/hosts"
    if [ "$NODE_TYPE" = "master" ]; then
        MASTER_IP=$(hostname -I | awk '{print $1}')
        log_action "IP du master automatiquement détectée : $MASTER_IP"
    else
        if [ -z "$MASTER_IP" ]; then
            MASTER_IP=$(grep "$MASTER_HOSTNAME" /etc/hosts | awk '{print $1}')
            if [ -z "$MASTER_IP" ]; then
                read -p "Entrez l'IP du master: " MASTER_IP
            else
                log_action "IP du master récupérée depuis /etc/hosts : $MASTER_IP"
            fi
        fi
    fi
    if [ "$NODE_TYPE" = "worker" ]; then
        WORKER_IP=$(hostname -I | awk '{print $1}')
        log_action "IP du worker automatiquement détectée : $WORKER_IP"
    fi

    # Backup du fichier hosts
    cp /etc/hosts /etc/hosts.bak
    check_command_success

    cat > /etc/hosts << EOF
127.0.0.1 localhost
$MASTER_IP $MASTER_HOSTNAME
EOF

    if [ "$NODE_TYPE" = "worker" ]; then
        echo "$WORKER_IP $new_hostname" >> /etc/hosts
    fi
}

# Désactivation du swap
disable_swap() {
    log_action "Désactivation du swap..."
    swapoff -a
    check_command_success
    sed -i '/ swap / s/^/#/' /etc/fstab
    check_command_success
}

# Configuration des droits sudo
setup_sudo_rights() {
    log_action "Configuration des droits sudo..."
    local username=$(whoami)
    usermod -aG sudo $username
    check_command_success
    echo "$username ALL=(ALL:ALL) NOPASSWD: ALL" | sudo tee /etc/sudoers.d/$username
    check_command_success
}

# Configuration de containerd
setup_containerd() {
    log_action "Configuration de containerd..."

    # Vérification et création du fichier config.toml si nécessaire
    mkdir -p /etc/containerd
    containerd config default > /etc/containerd/config.toml
    check_command_success

    # Modification de la configuration
    sed -i 's/disabled_plugins/enabled_plugins/' /etc/containerd/config.toml
    check_command_success

    # Redémarrage du service
    systemctl restart containerd.service
    check_command_success
}

# Installation de Docker
install_docker() {
    log_action "Installation de Docker..."
    if ! command -v docker &> /dev/null; then
        curl -fsSL https://get.docker.com | sh
        check_command_success
        usermod -aG docker $USER
        systemctl enable docker
        systemctl start docker
        check_command_success
    fi
}

# Installation de Kubernetes via snap
install_kubernetes() {
    log_action "Installation de Kubernetes..."

    # Installation de snap si nécessaire
    if ! command -v snap &> /dev/null; then
        apt_output=$(apt-get update 2>&1)
        handle_apt_errors "$apt_output"
        apt_output=$(apt-get install -y snapd 2>&1)
        handle_apt_errors "$apt_output"
        systemctl enable --now snapd.socket
        check_command_success
    fi

    # Installation des composants K8s
    snap install kubectl --classic
    check_command_success
    snap install kubeadm --classic
    check_command_success
    snap install kubelet --classic
    check_command_success

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

    systemctl daemon-reload
    systemctl enable kubelet
    systemctl start kubelet
    check_command_success
}

# Initialisation du master
init_master() {
    log_action "Initialisation du master node..."

    kubeadm init --pod-network-cidr=10.244.0.0/16 --apiserver-advertise-address=$MASTER_IP
    if [ $? -ne 0 ]; then
        log_action "Erreur lors de l'initialisation du master. Affichage des logs :"
        check_logs_on_failure "/var/log/syslog"
        exit 1
    fi

    # Configuration de kubectl
    mkdir -p $HOME/.kube
    cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
    chown $(id -u):$(id -g) $HOME/.kube/config
    check_command_success

    # Configuration réseau
    modprobe br_netfilter
    echo "net.bridge.bridge-nf-call-iptables=1" >> /etc/sysctl.conf
    sysctl -p
    check_command_success

    # Installation de Flannel
    kubectl apply -f https://raw.githubusercontent.com/flannel-io/flannel/master/Documentation/kube-flannel.yml
    if [ $? -ne 0 ]; then
        log_action "Erreur lors de l'installation de Flannel. Affichage des logs :"
        check_logs_on_failure "/var/log/syslog"
        exit 1
    fi

    # Récupération des informations pour le join
    local token=$(kubeadm token create)
    local hash=$(openssl x509 -in /etc/kubernetes/pki/ca.crt -noout -pubkey | openssl rsa -pubin -outform DER 2>/dev/null | sha256sum | cut -d' ' -f1)

    echo "Information pour joindre le cluster:" | tee -a $SUMMARY_FILE
    echo "kubeadm join ${MASTER_IP}:6443 --token $token --discovery-token-ca-cert-hash sha256:$hash" | tee -a $SUMMARY_FILE
}

# Configuration du worker
setup_worker() {
    log_action "Configuration du worker node..."

    if [ -z "$MASTER_IP" ]; then
        MASTER_IP=$(grep "$MASTER_HOSTNAME" /etc/hosts | awk '{print $1}')
        if [ -z "$MASTER_IP" ]; then
            read -p "Entrez l'IP du master: " MASTER_IP
        else
            log_action "IP du master récupérée depuis /etc/hosts : $MASTER_IP"
        fi
    fi
    read -p "Entrez le token: " token
    read -p "Entrez le hash: " hash

    kubeadm join ${MASTER_IP}:6443 --token $token --discovery-token-ca-cert-hash sha256:$hash
    if [ $? -ne 0 ]; then
        log_action "Erreur lors de la jointure du worker. Affichage des logs :"
        check_logs_on_failure "/var/log/syslog"
        exit 1
    fi
}

# Vérification de l'état du cluster
check_cluster_status() {
    log_action "Vérification de l'état du cluster..."

    kubectl get nodes -o wide
    if [ $? -ne 0 ]; then
        log_action "Erreur lors de la vérification des nœuds. Affichage des logs :"
        check_logs_on_failure "/var/log/syslog"
        exit 1
    fi
    kubectl get pods --all-namespaces
    if [ $? -ne 0 ]; then
        log_action "Erreur lors de la vérification des pods. Affichage des logs :"
        check_logs_on_failure "/var/log/syslog"
        exit 1
    fi
}

# Script principal
main() {
    # Vérification des droits root
    if [ "$EUID" -ne 0 ]; then
        echo "Ce script doit être exécuté en tant que root"
        exit 1
    fi

    # Demande du type de nœud si non spécifié
    if [ -z "$NODE_TYPE" ]; then
        read -p "Type de nœud (master/worker): " NODE_TYPE
    fi

    # Exécution des étapes communes
    check_prerequisites
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
        setup_worker
        check_cluster_status
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
        -f|--force)
            FORCE_REINSTALL=true
            shift
            ;;
        -t|--type)
            NODE_TYPE="$2"
            shift 2
            ;;
        *)
            echo "Option invalide: $1"
            show_help
            exit 1
            ;;
    esac
done

# Lancement du script
main
