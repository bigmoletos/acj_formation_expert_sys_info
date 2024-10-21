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
  docker-compose up
  ```

- Arrêter des services :
  ```bash
  docker-compose down
  ```

- Construire des images :
  ```bash
  docker-compose build
  ```
