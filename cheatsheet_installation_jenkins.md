# Installation CI/CD Automatisé d'une API Flask avec Jenkins sur Gitlab

## Sommaire
1. [Prérequis](#prérequis)
2. [Installation de Jenkins](#installation-de-jenkins)
3. [Configuration de Jenkins](#configuration-de-jenkins)
4. [Configuration GitLab](#configuration-gitlab)
5. [Pipeline CI/CD](#pipeline-ci-cd)
6. [Dépannage](#dépannage)

## Prérequis
- Une machine virtuelle Linux (Ubuntu recommandé)
- Accès root ou sudo
- Git installé
- Python 3.x installé

## Installation de Jenkins
### Installation des dépendances
```bash
sudo apt update && sudo apt upgrade -y
# Installation de Java
sudo apt install fontconfig openjdk-17-jre
```

### Installation de Jenkins
```bash
# Ajout de la clé du dépôt Jenkins
sudo wget -O /usr/share/keyrings/jenkins-keyring.asc \
  https://pkg.jenkins.io/debian-stable/jenkins.io-2023.key
echo "deb [signed-by=/usr/share/keyrings/jenkins-keyring.asc]" \
  https://pkg.jenkins.io/debian-stable binary/ | sudo tee \
  /etc/apt/sources.list.d/jenkins.list > /dev/null
sudo apt-get update
sudo apt-get install jenkins
```

### Vérification et démarrage
```bash
# Vérifier l'installation
jenkins --version
sudo systemctl status jenkins

# Démarrer Jenkins
sudo systemctl start jenkins

# Vérifier l'adresse IP
ip a | grep ens

# Configuration du pare-feu
sudo ufw allow 8080/tcp
```

## Configuration de Jenkins
1. Accédez à l'interface web : `http://<votre-ip_vm>:8080`

2. Récupération du mot de passe initial :
```bash
sudo cp /var/lib/jenkins/secrets/initialAdminPassword .
sudo cat initialAdminPassword
```

3. Configuration initiale :
   - Installer les plugins suggérés
   - Créer un compte administrateur
   - Configurer l'URL Jenkins

## Configuration GitLab
### Informations du dépôt
- SSH : `git@gitlab.com:ajc543243/projet_bigdata2.git`
- HTTPS : `https://gitlab.com/ajc543243/projet_bigdata2.git`

### Configuration des webhooks
1. Dans GitLab, allez dans Settings > Webhooks
2. Ajoutez l'URL Jenkins : `http://<votre-ip_vm>:8080/gitlab-webhook/`
3. Sélectionnez les événements déclencheurs (Push events, Merge Request events)

## Pipeline CI/CD
### Structure du Pipeline
créer un fichier Jenkinsfile dans le dossier du projet par ex

Jenkinsfile.groovy
```groovy
// Exemple de Jenkinsfile
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                // Étapes de build
            }
        }
        stage('Test') {
            steps {
                // Étapes de test
            }
        }
        stage('Deploy') {
            steps {
                // Étapes de déploiement
            }
        }
    }
}
```

### Configuration requise
- Installer les plugins Python dans Jenkins
- Configurer les credentials GitLab
- Configurer l'environnement Python

## Dépannage
### Problèmes courants
- Si Jenkins ne démarre pas : `sudo systemctl status jenkins`
- Problèmes de permissions : `sudo chown -R jenkins:jenkins /var/lib/jenkins`
- Erreurs de connexion GitLab : vérifier les credentials

### Logs utiles
```bash
sudo tail -f /var/log/jenkins/jenkins.log
```

### Commandes Git utiles
```bash
# Configuration de la branche
git push -u origin <nom-branche>
git branch --set-upstream-to=origin/<branche> <branche-locale>

# Vérification de la configuration
git remote -v
git branch -vv
```

## Liens utiles
- [Documentation Jenkins](https://www.jenkins.io/doc/)
- [Documentation GitLab CI](https://docs.gitlab.com/ee/ci/)
- [Guide Flask](https://flask.palletsprojects.com/)



