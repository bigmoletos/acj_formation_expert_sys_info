
# Docker Cheat Sheet

## Ajouter votre utilisateur au groupe Docker
```Dockerfile
sudo groupadd docker && sudo usermod -aG docker franck
# ou
sudo usermod -aG docker vboxuser
newgrp docker
# autre vm
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
## pour arreter tous les conteneurs qui tournent
```Dockerfile
docker stop $(docker ps -q)

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
## Démarrer le conteneur HTTPD (apache)  en arriere plan et le rediriger vers le port

```Dockerfile
docker run -d -p 80:80 httpd
```
 Pour amazon ec2 comme leport 80 et déja utilisé pour mon wordpress on redirege sur un autre port par ex 8080
```Dockerfile
docker run -d -p 8080:80 httpd
```
pour tester dans chrome on prend l'ip de la vm (eth0 ou enp0), ci dessous l'ip de wsl windows
```Dockerfile
ip a
http://172.21.238.49/
```


## Pour rentrer dans mon image Debian il faut Lancer un contener  en lancant un terminal bash
```Dockerfile
docker run -it debian /bin/bash
```

## Lancer un contener debian en lancant un terminal bash puis avece une commande
```Dockerfile
docker run  debian ls /etc
```
# Volume
## Créer un volume apache2 pour pesister les données
```Dockerfile
docker run -d -p 8080:80 -v /root/html:/usr/local/apache2/htdocs httpd
# ou en general mon_dossier=root/html

docker run -d -p 8080:80 -v /mon_dossier/html:/usr/local/apache2/htdocs httpd
# ou
sudo docker volume create --name my_data_volume
sudo docker run  -dti -v my_data_volume
```

# Reseau
## Créer un nouveau réseau bridge
```Dockerfile
sudo docker network ls
sudo docker network create --driver bridge mon_reseau-bridge
sudo docker network ls

sudo docker network inspect
# pour supprimer le reseau
docker network rm mon_reseau-bridge

```
## suite probleme sur wordpress
```Dockerfile
# on supprime les docker compose
docker compose down
#  on supprime les volumes
docker volume ls
docker volume remove wordpress_db wordpress_wordpress
docker volume ls
#  on relance le build
docker compose up -d
```

## Nettoyer Docker
###  Pour faire de la place sur la vm
```Dockerfile
#  voir la place dispo sur la vm
df -h
#  suppression des fichiers et apt inutiles
sudo apt-get autoremove
sudo apt-get clean
#  suppresion des anciens kernel
dpkg --list | grep linux-image
sudo apt-get purge linux-image-x.x.x-xx

# suppression des fichiers temporaires
sudo rm -rf /tmp/*
#  verifier la taille des fichiers log
sudo du -h /var/log

#  nettoyage dedocker
docker system prune -a

# relance du container
docker exec -it gitlab gitlab-ctl restart

```



## lancer une image sur un reseau particulier, par ex apache2
dans le repertoire mettre un fichier Dockerfile
```Dockerfile

sudo docker run -dit --name mytest --network mon_reseau_bridge httpd


```


# Construire une image

```Dockerfile

docker build -t mon-wordpress .

```



# Commandes
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
docker pull jupyter/scipy-notebook
docker pull tensorflow/tensorflow
docker pull pytorch/pytorch
docker pull ollama/ollama
docker pull opencv/opencv
docker pull nvidia/cuda
docker pull huggingface/transformers-pytorch-cpu
docker pull mxnet/python
docker pull horovod/horovod
docker pull tiangolo/uvicorn-gunicorn-fastapi


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

# creer une cle SSh pour se connecter à GitLab

```bash
ssh-keygen -t rsa -b 4096 -C "romaru@yopmail.com" -f ~/.ssh/key_gitlab
# creation du fichier de config
sudo nano ~/.ssh/config

# GitLab.com
Host gitlab.com
  User git
  PreferredAuthentications publickey
  IdentityFile ~/.ssh/key_gitlab


#  instazll de xclip
sudo apt install xclip

xclip -sel clip ~/.ssh/key_gitlab.pub

#  test connection SSH depuis la vm
ssh -T git@gitlab.com

#  pour verifier que le .env fonctionne et que les variables sont bien passées au docker-compose

docker exec -it gitlab env

#  pour aller dans le repertoire des clés
cd ~/.ssh/

```

## pour renitialiser le password root de gitlab

```bash
docker exec -it gitlab gitlab-rake "gitlab:password:reset[root]"
```