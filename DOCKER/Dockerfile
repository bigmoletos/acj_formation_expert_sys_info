# Utiliser une image de base officielle d'Apache
FROM httpd:2.4

# Copier les fichiers HTML dans le répertoire par défaut de l'Apache
# COPY root/html/ /usr/local/apache2/htdocs/
COPY /home/vboxuser/Templates/html /usr/local/apache2/htdocs/

# Installer les dépendances nécessaires pour PHP (si vous utilisez PHP avec Apache)
RUN apt-get update && apt-get install -y \
    php libapache2-mod-php php-mysql \
    && docker-php-ext-install mysqli

# Configurer les variables d'environnement pour la connexion à MariaDB
ENV DB_HOST=192.168.1.189
ENV DB_USER=root
ENV DB_PASSWORD=votre_mot_de_passe_bdd
ENV DB_NAME=votre_nom_de_base

# Exposer le port 80 pour accéder à Apache
EXPOSE 80

# Démarrer Apache
CMD ["httpd-foreground"]
