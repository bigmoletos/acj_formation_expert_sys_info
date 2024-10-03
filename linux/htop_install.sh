#!/bin/bash

# Vérifier si l'URL est passée en argument
if [ -z "$1" ]; then
    read -p "Veuillez saisir l'URL du code source de htop (tar.gz) : " URL
else
    URL=$1
fi

# Vérifier si l'URL est vide
if [ -z "$URL" ]; then
    echo "L'URL ne peut pas être vide. Annulation de l'installation."
    exit 1
fi

# Vérification de la version existante de htop
echo "Vérification de la version actuelle de htop..."
if command -v htop &> /dev/null; then
    CURRENT_VERSION=$(htop --version | head -n 1)
    echo "Version actuelle de htop trouvée : $CURRENT_VERSION"
    read -p "Voulez-vous désinstaller l'ancienne version et installer la nouvelle ? (o/n) : " response
    if [[ "$response" =~ ^[oO]$ ]]; then
        echo "Désinstallation de l'ancienne version de htop..."
        sudo make uninstall &> /dev/null || sudo apt remove --purge -y htop
    else
        read -p "Voulez-vous installer une version supplémentaire avec altinstall ? (o/n) : " alt_response
        if [[ ! "$alt_response" =~ ^[oO]$ ]]; then
            echo "Installation annulée."
            exit 0
        fi
    fi
else
    echo "Aucune version de htop trouvée. Procédure d'installation de la nouvelle version."
fi

# Mise à jour du système et installation des dépendances
echo "Mise à jour du système et installation des dépendances..."
sudo apt update && sudo apt upgrade -y
sudo apt install -y wget make build-essential libncursesw5-dev libncurses-dev autoconf automake pkgconf m4
sudo apt install -y libssl-dev
sudo apt install -y build-essential libffi-dev zlib1g-dev libbz2-dev libreadline-dev libsqlite3-dev wget
sudo apt-get install -y build-essential gdb lcov pkg-config libbz2-dev libffi-dev libgdbm-dev libgdbm-compat-dev liblzma-dev libncurses5-dev libreadline6-dev libsqlite3-dev libssl-dev lzma lzma-dev tk-dev uuid-dev zlib1g-dev 

# Exporter les variables d'environnement pour OpenSSL
export LD_LIBRARY_PATH=/usr/local/openssl/lib
export PATH=/usr/local/openssl/bin:$PATH

# Téléchargement du code source
echo "Téléchargement du code source depuis $URL..."
wget $URL -O htop-source.tar.gz

# Vérifier si le téléchargement a réussi
if [ ! -f htop-source.tar.gz ]; then
    echo "Échec du téléchargement. Vérifiez l'URL et réessayez."
    exit 1
fi

# Extraction du code source
echo "Extraction du code source..."
tar -xvzf htop-source.tar.gz

# Trouver le répertoire extrait
SOURCE_DIR=$(tar -tzf htop-source.tar.gz | head -1 | cut -f1 -d"/")

# Accéder au répertoire extrait
cd $SOURCE_DIR

# Générer le script configure si nécessaire
if [ ! -f ./configure ]; then
    echo "Génération du script configure..."
    autoreconf -i
fi

# Configurer, compiler et installer
echo "Configuration..."
if [[ "$alt_response" =~ ^[oO]$ ]]; then
    ./configure --prefix=/usr/local/htop-$(date +%Y%m%d%H%M%S)
else
    ./configure
fi

echo "Compilation..."
make

echo "Installation..."
if [[ "$alt_response" =~ ^[oO]$ ]]; then
    sudo make install
    echo "Installation de htop terminée ! Utilisez '/usr/local/htop-*/bin/htop' pour lancer cette version."
else
    sudo make install
fi

# Nettoyage
echo "Nettoyage des fichiers temporaires..."
cd ..
rm -rf htop-source.tar.gz $SOURCE_DIR

echo "Processus terminé !"
