# Utiliser une image de base officielle d'Apache
FROM php:7.4-apache

# Copier les fichiers HTML dans le répertoire par défaut de l'Apache
# COPY root/html/ /usr/local/apache2/htdocs/
COPY ./html/index.html /usr/local/apache2/htdocs/

# Installer les dépendances nécessaires pour PHP (si vous utilisez PHP avec Apache)
RUN apt-get update && apt-get install -y
# RUN apt-get update && apt-get install -y \
#     php libapache2-mod-php php-mysql \
#     && docker-php-ext-install mysqli
RUN docker-php-ext-install mysqli
# Configurer les variables d'environnement pour la connexion à MariaDB
ENV DB_HOST=192.168.1.189
ENV DB_USER=vboxuser
ENV DB_PASSWORD=1234
ENV DB_NAME=wordpress

# Exposer le port 80 pour accéder à Apache
EXPOSE 80

# # Démarrer Apache
# CMD ["httpd-foreground"]
# Démarrer Apache (déjà inclus avec PHP)
CMD ["apache2-foreground"]

