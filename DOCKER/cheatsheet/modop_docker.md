# Installation de Docker sur Debian

Voir le site officiel :

[https://docs.docker.com/engine/install/debian/](https://docs.docker.com/engine/install/debian/)

## Ajouter la clé GPG officielle de Docker :

```bash
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc
```

## Ajouter le dépôt Docker aux sources Apt :

```bash
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```

## Installer les paquets Docker :

```bash
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

## Vérifier l'installation :

```bash
sudo docker run hello-world
```

# Installation de Docker sur Ubuntu

## Installation via le dépôt Apt
Avant d'installer Docker Engine pour la première fois sur une nouvelle machine hôte, vous devez configurer le dépôt Docker. Ensuite, vous pourrez installer et mettre à jour Docker depuis ce dépôt.

## Ajouter la clé GPG officielle de Docker :

```bash
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc
```

## Ajouter le dépôt Docker aux sources Apt :

```bash
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

sudo apt-get update
```

## Installer les paquets Docker :

```bash
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

## Vérifier l'installation :

```bash
sudo docker run hello-world
```


## WSL il faut crée un fichier .wslconfig dans C:\Users\User
et rajouter ces lignes :

```bash

[wsl2]
memory=16GB (+ ou - à votre convenance)
kernelCommandLine = cgroup_no_v1=all

```
# Dockerfile

## Structure de base d'un Dockerfile

```Dockerfile
# Utiliser une image de base
FROM python:3.9

# Définir le répertoire de travail dans le conteneur
WORKDIR /appya un

# Copier les fichiers nécessaires
COPY . /app

# Désactiver les interactions lors des mises à jour et installations
ENV DEBIAN_FRONTEND=noninteractive

# Installer les dépendances
RUN pip install -r requirements.txt

# Exposer un port
EXPOSE 5000

# Commande à exécuter au démarrage du conteneur
CMD ["python", "app.py"]
```

## Commandes principales

- **FROM** : Spécifie l'image de base.
- **WORKDIR** : Définit le répertoire de travail.
- **COPY** : Copie des fichiers dans l'image.
- **RUN** : Exécute une commande pendant la création de l'image.
- **CMD** : Définit la commande à exécuter au démarrage du conteneur.
- **EXPOSE** : Indique le port sur lequel le conteneur écoutera.

## Exemples utiles

- Installer des paquets :
  ```Dockerfile
  RUN apt-get update && apt-get install -y <package_name>
  ```

- Ajouter des variables d'environnement :
  ```Dockerfile
  ENV VARIABLE_NAME=value
  ```

## Docker file pour faire une image ubuntu
```yaml
FROM ubuntu
# Désactiver les interactions lors des mises à jour et installations cela evite de mettre les -y
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt upgrade
# ou
RUN export DEBIAN_FRONTEND=noninteractive && apt update && apt upgrade

RUN apt install apache2
ADD index.html /var/www/html

WORKDIR /var/www/html
EXPOSE 80
CMD ["/usr/sbin/apache2ctl", "-D", "FOREGROUND"]
```
## Docker file toutes les commandes
```yaml
Commandes Dockerfile courantes :
FROM : Définit l'image de base à utiliser pour créer l'image Docker. C'est la première instruction dans un Dockerfile.

Exemple : FROM ubuntu:latest
MAINTAINER : (Déprécié au profit de LABEL) Définit le nom du créateur ou du mainteneur de l'image. Aujourd'hui, on utilise plutôt l'instruction LABEL pour cette information.

Exemple : LABEL maintainer="Nom Prénom <email@domaine.com>"
RUN : Exécute une commande lors de la création de l'image. Utilisé pour installer des paquets ou effectuer des configurations dans l'image.

Exemple : RUN apt-get update && apt-get install -y apache2
CMD : Définit la commande par défaut à exécuter lorsque le conteneur démarre. Elle est utilisée pour définir le processus principal à exécuter dans le conteneur.

Exemple : CMD ["/usr/sbin/apache2ctl", "-D", "FOREGROUND"]
EXPOSE : Indique quel port sera exposé par le conteneur pour la communication avec l'extérieur.

Exemple : EXPOSE 80
ENV : Définit une variable d'environnement à utiliser dans le conteneur.

Exemple : ENV APP_HOME /usr/src/app
ARG : Similaire à ENV, mais utilisé uniquement lors de la construction de l'image (pas pendant le runtime). Utilisé pour passer des variables lors du build.

Exemple : ARG VERSION=1.0
COPY : Copie des fichiers ou répertoires depuis l'hôte vers l'image Docker.

Exemple : COPY ./app /usr/src/app
ADD : Semblable à COPY, mais peut également décompresser des fichiers ou copier des fichiers depuis une URL.

Exemple : ADD https://example.com/file.tar.gz /usr/src/app/
LABEL : Ajoute des méta-données à l'image. Cela peut inclure des informations telles que le mainteneur ou la version de l'image.

Exemple : LABEL version="1.0" description="Une image Docker pour une application web"
ENTRYPOINT : Définit la commande principale à exécuter lors du démarrage du conteneur, mais contrairement à CMD, elle n'est pas remplacée par des arguments supplémentaires.

Exemple : ENTRYPOINT ["/docker-entrypoint.sh"]
VOLUME : Crée un volume qui est monté dans le conteneur et persiste même si le conteneur est détruit.

Exemple : VOLUME /data
```

## Docker file pour faire une image ubuntu avec toutes les commandes
```yaml
# Choisir l'image de base Ubuntu
FROM ubuntu:20.04
# Informations sur le créateur de l'image (anciennement MAINTAINER, maintenant avec LABEL)
LABEL maintainer="John Doe <johndoe@example.com>"
LABEL version="1.0"
LABEL description="Image Docker pour une application web simple avec Apache et PHP."
# Définir une variable d'environnement pour l'emplacement de l'application
ENV APP_HOME /var/www/html
# Définir une variable ARG utilisée uniquement lors du build (pas en runtime)
ARG APP_VERSION=1.0
# Mettre à jour le système et installer Apache, PHP, et des dépendances sans interaction
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt upgrade -y && apt install -y apache2 php libapache2-mod-php
# Copier un fichier index.html dans le répertoire web de l'image
COPY ./html/index.html $APP_HOME
# Utiliser ADD pour ajouter un fichier depuis une URL
ADD https://example.com/logo.tar.gz /tmp/logo.tar.gz
RUN tar -xzf /tmp/logo.tar.gz -C $APP_HOME
# Créer un volume pour les fichiers persistants
VOLUME /var/log/apache2
# Exposer le port 80 pour l'application web
EXPOSE 80
# Définir l'entrée principale du conteneur (point d'entrée)
ENTRYPOINT ["/usr/sbin/apache2ctl"]
# Définir la commande par défaut lors du démarrage du conteneur
CMD ["-D", "FOREGROUND"]

```
# Docker Compose

## Fichier docker-compose.yml de base

```yaml
version: '3.8'
services:
  web:
    image: nginx
    ports:
      - "8080:80"
  app:
    build: .
    ports:
      - "5000:5000"
    volumes:
      - .:/app
    environment:
      - FLASK_ENV=development
```
## Docker file pour faire une image ubuntu
```yaml
FROM ubuntu
# Désactiver les interactions lors des mises à jour et installations cela evite de mettre les -y
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt upgrade
RUN apt install apache2
ADD index.html /var/www/html

WORKDIR /var/www/html
EXPOSE 80
CMD ["/usr/sbin/apache2ctl", "-D", "FOREGROUND"]
```

## pour builder

```bash
# Construire et démarrer vos conteneurs
docker compose up --build
# Arrêter les conteneurs (sans les supprimer) :
docker compose stop
# Arrêter et supprimer les conteneurs (et les réseaux associés) :
docker compose down
# Vérifier les logs des conteneurs :
docker compose logs -f

```

## pour le lancer

```bash
docker run -d -p 8001:8000 my-fastapi-meteo
```

## Commandes principales

- **version** : Déclare la version de Docker Compose utilisée.
- **services** : Définit les différents services à lancer.
- **image** : Utilise une image existante pour créer un service.
- **build** : Construit une image à partir d'un Dockerfile local.
- **ports** : Mappe les ports du conteneur à ceux de l'hôte.
- **volumes** : Monte des volumes entre l'hôte et le conteneur.
- **environment** : Définit des variables d'environnement pour le service.

## Exemples utiles

- Démarrer des services :
```bash
docker compose up -d
```

- Arrêter des services :
```bash
docker compose down
```

- Construire des images :
```bash
docker compose up -d
# ou pour voir les logs en direct
docker compose up --build
```


- voir les images en cours :
```bash
docker compose ps
```

- supprimer un container :
```bash
docker rm -f gitlab
#  pour partir propre on peutr aussi faire un cumul
docker rm -f gitlab &&  docker compose down && docker compose up -d

```
# Installer git lab sur sa VM par ex 192.168.1.97

- sur l'instance créer les repertoires necessaires à gitlab :
```bash
cd ~
cd srv/
sudo mkdir gitlab
sudo mkdir data
cd gitlab/
sudo mkdir config logs

#  dans un repertoire de l'instance créer un dossier pour y déposer le docker compose

cd /mnt/c/AJC_formation/DOCKER/images
sudo mkdir gitlab
cd gitlab
sudo touch docker-compose.yml
#  dans nano saisir

version: '3.7'

services:
  gitlab:
    image: gitlab/gitlab-ce
    container_name: gitlab
    restart: always
    hostname: 'gitlab'
    environment:
      GITLAB_OMNIBUS_CONFIG: |
        # Add any other gitlab.rb configuration here, each on its own line
        external_url 'http://192.168.1.97/'
    ports:
      - '8088:80'
      - '22000:22'
    volumes:
      - '/srv/gitlab/config:/etc/gitlab'
      - '/srv/gitlab/logs:/var/log/gitlab'
      - '/srv/gitlab/data:/var/opt/gitlab'
    shm_size: '256m'

# lancer le build
docker compose up -d

# verfier le status  on doit être : "Up 13 minutes (healthy)"
#  en general cela prend environ 7 à 8 min pour que gitlab soit totalement installé
# on peut verifier avec htop qu'il n'y a plus de processus gitlb ruby à plus de 90% de cpu
docker compose ps


# aller dans le navigateur
http://192.168.1.97:8088

# ip a me donne finalement cette ip: 172.21.238.49

http://172.21.238.49:8085



```
