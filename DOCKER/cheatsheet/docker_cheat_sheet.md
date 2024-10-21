
# Docker Cheat Sheet

## Ajouter votre utilisateur au groupe Docker
```Dockerfile
sudo usermod -aG docker vboxuser
newgrp docker
sudo usermod -aG docker franck
newgrp docker
```

## Vérifier que le démon Docker est en cours d'exécution

```Dockerfile
sudo service docker status
```

## si démon Docker est arrété i lfaut le redemarrer

```Dockerfile
sudo service docker start
```

## pour voir les images
```Dockerfile
sudo docker ps

```
## telecharger une image

```Dockerfile
docker pull fedora
docker pull debian
docker pull bash
docker pull httpd
docker pull mariadb
docker pull mysql
docker pull postgres
docker pull mongo
docker pull grafana/grafana
docker pull gradle
docker pull selenium/video
docker pull php
docker pull openjdk
docker pull python
docker pull pypy
docker pull nginx


```

## Démarrer le conteneur HTTPD (apache)  en arriere plan

```Dockerfile
docker run -d httpd

```
## Pour rentrer dans mon image Debian il faut Lancer un contener  en lancant un terminal bash
```Dockerfile
docker run -it debian /bin/bash
```

## Lancer un contener debian en lancant un terminal bash puis avece une commande
```Dockerfile
docker run  debian ls /etc
```



1. Gestion des conteneurs
-------------------------
- docker run <image>                  : Démarrer un nouveau conteneur à partir d'une image.
- docker ps                           : Lister les conteneurs en cours d'exécution.
- docker ps -a                        : Lister tous les conteneurs (en cours et arrêtés).
- docker stop <id/nom_conteneur>      : Arrêter un conteneur en cours d'exécution.
- docker start <id/nom_conteneur>     : Démarrer un conteneur arrêté.
- docker restart <id/nom_conteneur>   : Redémarrer un conteneur.
- docker rm <id/nom_conteneur>        : Supprimer un conteneur arrêté.
- docker exec -it <id/nom_conteneur> bash : Accéder à un conteneur en mode interactif (bash).
- docker logs <id/nom_conteneur>      : Afficher les logs d'un conteneur.
- docker inspect <id/nom_conteneur>   : Obtenir des informations détaillées sur un conteneur.
- docker rename <ancien_nom> <nouveau_nom> : Renommer un conteneur.

2. Gestion des images
---------------------
- docker images                        : Lister les images Docker locales.
- docker pull <image>                  : Télécharger une image depuis un registre Docker (par ex: Docker Hub).
- docker build -t <nom_image> .        : Construire une image à partir d'un Dockerfile.
- docker rmi <image>                   : Supprimer une image locale.
- docker tag <image> <nouveau_nom>     : Taguer une image avec un autre nom.
- docker save -o <fichier.tar> <image> : Sauvegarder une image dans un fichier .tar.
- docker load -i <fichier.tar>         : Charger une image depuis un fichier .tar.

3. Volumes
----------
- docker volume ls                         : Lister tous les volumes.
- docker volume create <nom_volume>        : Créer un volume.
- docker volume rm <nom_volume>            : Supprimer un volume.
- docker run -v <nom_volume>:/path <image> : Monter un volume dans un conteneur.
- docker volume inspect <nom_volume>       : Obtenir des informations sur un volume.

4. Réseaux
----------
- docker network ls                        : Lister tous les réseaux Docker.
- docker network create <nom_reseau>       : Créer un nouveau réseau.
- docker network rm <nom_reseau>           : Supprimer un réseau.
- docker network inspect <nom_reseau>      : Obtenir des informations sur un réseau.
- docker run --network=<nom_reseau> <image>: Lancer un conteneur dans un réseau spécifique.

5. Docker Hub
-------------
- docker login                             : Se connecter à Docker Hub.
- docker logout                            : Se déconnecter de Docker Hub.
- docker push <nom_image>                  : Envoyer une image sur Docker Hub.
- docker pull <nom_image>                  : Télécharger une image depuis Docker Hub.

6. Dockerfile
-------------
- docker build -t <nom_image> <path>       : Construire une image à partir d’un Dockerfile.
- docker history <image>                   : Voir l'historique de construction d'une image Docker.
- docker build --no-cache -t <nom_image> . : Construire une image sans utiliser le cache.

7. Système
----------
- docker system df                         : Voir l'utilisation de l'espace disque Docker.
- docker system prune                      : Supprimer les conteneurs, volumes, réseaux inutilisés.
- docker system prune -a                   : Supprimer tous les objets inutilisés.

8. Informations
---------------
- docker info                              : Obtenir des informations sur l'installation Docker.
- docker version                           : Obtenir la version de Docker installée.

9. Conteneurs Interactifs
-------------------------
- docker attach <id/nom_conteneur>         : Se connecter à un conteneur en cours d’exécution.
- docker run -d <image>                    : Lancer un conteneur en arrière-plan (détaché).
- docker run -it <image>                   : Lancer un conteneur en mode interactif avec un terminal.

# Special IA

## telecharger les  images

```Dockerfile
docker pull tensorflow/tensorflow
docker pull pytorch/pytorch
docker pull ollama/ollama


```

## telecharger une image IA ML huggingface

```Dockerfile
# demo
docker run -it -p 7860:7860 --platform=linux/amd64 \
    -e HUGGING_FACE_HUB_TOKEN="YOUR_VALUE_HERE"
\
    registry.hf.space/harsh-manvar-llama-2-7b-chat-test:latest python app.py
# install

git clone https://huggingface.co/spaces/harsh-manvar/llama-2-7b-chat-test


```

### faire un requirement.txt avec:

```txt
gradio==3.37.0
protobuf==3.20.3
scipy==1.11.1
torch==2.0.1
sentencepiece==0.1.99
transformers==4.31.0
ctransformers==0.2.27
```

### dans Dockerfile:

```Dockerfile
FROM python:3.9
RUN useradd -m -u 1000 user
WORKDIR /code
COPY ./requirements.txt /code/requirements.txt
RUN pip install --upgrade pip
RUN pip install --no-cache-dir --upgrade -r /code/requirements.txt
USER user
COPY --link --chown=1000 ./ /code
```