# Gitlab

# Git clone en SSh

```bash
git clone git@192.168.1.97:ajc/ajc1.git
cd ajc1
git switch --create main
touch README.md
git add README.md
git commit -m "add README"
git push --set-upstream origin main
#Pousser un dossier existant
cd existing_folder
git init --initial-branch=main
git remote add origin git@192.168.1.97:ajc/ajc1.git
git add .
git commit -m "Initial commit"
git push --set-upstream origin main
#Pousser un dépôt Git existant
cd existing_repo
git remote rename origin old-origin
git remote add origin git@192.168.1.97:ajc/ajc1.git
git push --set-upstream origin --all
git push --set-upstream origin --tags
```

# Gti clone en HTTP

```bash
# Créer un nouveau dépôt
git clone http://192.168.1.97/ajc/ajc1.git
cd ajc1
git switch --create main
touch README.md
git add README.md
git commit -m "add README"
git push --set-upstream origin main
# Pousser un dossier existant
cd existing_folder
git init --initial-branch=main
git remote add origin http://192.168.1.97/ajc/ajc1.git
git add .
git commit -m "Initial commit"
git push --set-upstream origin main
# Pousser un dépôt Git existant
cd existing_repo
git remote rename origin old-origin
git remote add origin http://192.168.1.97/ajc/ajc1.git
git push --set-upstream origin --all
git push --set-upstream origin --tags

```

## installation du runner gitlab sur ma vm 197.168.1.97
```bash
# Download the binary for your system
sudo curl -L --output /usr/local/bin/gitlab-runner https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-linux-amd64

# Give it permission to execute
sudo chmod +x /usr/local/bin/gitlab-runner

# Create a GitLab Runner user
sudo useradd --comment 'GitLab Runner' --create-home gitlab-runner --shell /bin/bash

# Install and run as a service
sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner
sudo gitlab-runner start
sudo gitlab-runner status

# pour arreter le runner p
sudo systemctl stop gitlab-runner
# Commande pour enregistrer le runner


sudo gitlab-runner register --url http://192.168.1.97:8088/ --registration-token GR13489419ofmmqJ8CCJxkyDETrQN
sudo gitlab-runner register --url http://192.168.1.97:8088/ --registration-token GR1348941fZNDQ2HteUQ12zz81NCV

# http://192.168.1.97:8088/
# token GR13489419ofmmqJ8CCJxkyDETrQN
# 2 éme token GR1348941fZNDQ2HteUQ12zz81NCV
# vboxuser
# vbox, CI
# docker
# ruby:2.7
#

```


### Creation du fichier config ssh

```bash

sudo nano ~/.ssh/config

# GitLab.com .ssh/config
# Configuration pour la première clé SSH
Host gitlab-server-1
    HostName 192.168.1.97
    User git
    Port 22000
    IdentityFile ~/.ssh/key_gitlab
    IdentitiesOnly yes

# Configuration pour la deuxième clé SSH
Host gitlab-server-2
    HostName 192.168.1.97
    User git
    Port 22000
    IdentityFile ~/.ssh/gitlab
    IdentitiesOnly yes


chmod 700 ~/.ssh
# Si le propriétaire du dossier .ssh ou du fichier config a changé accidentellement, assure-toi que vboxuser est bien le propriétaire
sudo chown -R vboxuser:vboxuser ~/.ssh
#  test des connexions
ssh -F ~/.ssh/config -T git@gitlab-server-2
ssh -F ~/.ssh/config -T git@gitlab-server-1

# Welcome to GitLab, @root!


```


### stop relance le runner , fait le commit et le push
```bash
sudo systemctl stop  gitlab-runner && sudo systemctl start  gitlab-runner && gitlab-runner status && git commit -a -m "modif fichier " && gps

```


### Probleme de connexion SSh à la VM pour utiliser Git dans gitlab

```bash
docker exec -it gitlab
cat /etc/ssh/sshd_config | grep -i "pubkeyauthentication"
exit
# decommente la ligne  PubkeyAuthentication yes
docker exec -it gitlab sed -i 's/#PubkeyAuthentication yes/PubkeyAuthentication yes/' /etc/ssh/sshd_config
# redemarrage du servce SSH de docker
docker exec -it gitlab service ssh restart

# Utiliser les Alias SSH dans Git
git remote set-url origin git@gitlab-server-1:ajc/ajc_cpp.git
#  utilisation de git
git push -u origin main

```

### Teste Local du fichier gitlab-ci.yml sans passer par le runner
Teste la commande de compilation localement pour t'assurer qu'elle fonctionne. Si tu as accès à un environnement similaire au runner (par exemple, avec Docker), exécute cette commande pour tester localement :

```bash
docker run --rm -v $(pwd):/workspace -w /workspace gcc g++ main.cpp -o myprogrammes/prog.exe
```


### suppression du runner

```bash

sudo gitlab-runner uninstall

```