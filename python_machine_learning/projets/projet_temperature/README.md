# Projet Temperature

## Description
Application web Flask permettant de consulter la température actuelle de n'importe quelle ville dans le monde en utilisant l'API OpenWeatherMap.

## Structure du Projet

```bash
projet_temperature/
├── app/
│ ├── init.py # Initialisation de l'application Flask
│ ├── routes.py # Définition des routes de l'application
│ ├── models.py # Modèles de données SQLAlchemy
│ ├── forms.py # Formulaires WTForms
│ ├── logging_config.py # Configuration du système de logging
│ ├── templates/ # Templates HTML
│ │ ├── index.html # Page d'accueil/connexion
│ │ └── weather.html # Page d'affichage météo
│ └── static/ # Fichiers statiques (CSS, JS)
├── docs/ # Documentation générée par Doxygen
├── logs/ # Fichiers de logs
├── tests/ # Tests unitaires
├── .env # Variables d'environnement
├── .gitignore # Fichiers à ignorer par Git
├── Dockerfile # Configuration Docker
├── docker-compose.yml # Configuration Docker Compose
├── requirements.txt # Dépendances Python
├── Makefile # Commandes make
├── Doxyfile # Configuration Doxygen
└── ci-cd.yml # Configuration CI/CD GitHub Actions
```

## Fonctionnalités

### Routes (`routes.py`)
- **/** : Page d'accueil avec formulaire de connexion
  - Méthodes : GET, POST
  - Gère l'authentification des utilisateurs
- **/weather** : Affichage de la température
  - Méthode : GET
  - Paramètre : city (nom de la ville)
  - Utilise l'API OpenWeatherMap

### Modèles (`models.py`)
- **User** : Modèle utilisateur
  - `id` : Identifiant unique
  - `username` : Nom d'utilisateur
  - `password` : Mot de passe hashé
  - Méthodes :
    - `set_password()` : Hash le mot de passe
    - `check_password()` : Vérifie le mot de passe

### Formulaires (`forms.py`)
- **LoginForm** : Formulaire de connexion
  - Champs :
    - username : Nom d'utilisateur
    - password : Mot de passe
    - submit : Bouton de soumission

### Logging (`logging_config.py`)
- Configuration complète du système de logging
- Fonctionnalités :
  - Logs console et fichier
  - Rotation des fichiers de log
  - Différents niveaux de log (DEBUG, INFO, WARNING, ERROR, CRITICAL)
  - Décorateur pour tracer les appels de fonction
  - Gestion des exceptions

## Configuration

### Variables d'Environnement (.env)


SECRET_KEY=your_secret_key
LOG_TO_FILE=true
LOG_LEVEL=DEBUG
LOG_DIR=logs
DATABASE_URL=mysql+pymysql://user:password@db:3306/temperature_db


### Base de Données
- MySQL 5.7
- Configuration dans docker-compose.yml
- Variables :
  - MYSQL_DATABASE: temperature_db
  - MYSQL_USER: user
  - MYSQL_PASSWORD: password

## Déploiement

### Docker

```bash
Construction de l'image
docker build -t projet_temperature .
Lancement avec docker-compose
docker-compose up -d
```

### Make

```bash
# Installation des dépendances
make install
# Lancement des tests
make test
# Génération de la documentation
make docs
# Lancement de l'application
make run
```

## CI/CD
- Intégration continue avec GitHub Actions
- Étapes :
  1. Tests unitaires
  2. Construction de l'image Docker
  3. Déploiement automatique

## Documentation
- Générée avec Doxygen
- Format : HTML
- Inclut :
  - Documentation du code
  - Diagrammes UML
  - Graphes d'appels
  - Interface de recherche

## Sécurité
- Mots de passe hashés
- Protection CSRF dans les formulaires
- Variables sensibles en environnement
- Gestion des erreurs et logging

## Dépendances Principales
- Flask : Framework web
- SQLAlchemy : ORM
- WTForms : Gestion des formulaires
- Requests : Appels API
- PyMySQL : Connecteur MySQL

## Tests
- Tests unitaires avec pytest
- Couverture de code
- Tests d'intégration avec la base de données

## Développement

### Installation en Local

```bash
# Cloner le repository
git clone [URL_DU_REPO]
# Créer un environnement virtuel
python -m venv venv
source venv/bin/activate # Linux/Mac
venv\Scripts\activate # Windows
# Installer les dépendances
pip install -r requirements.txt
# Configurer les variables d'environnement
cp .env.example .env
# Éditer .env avec vos valeurs
# Lancer l'application
flask run
```


### Contribution
1. Fork le projet
2. Créer une branche (`git checkout -b feature/AmazingFeature`)
3. Commit les changements (`git commit -m 'Add some AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrir une Pull Request

## Licence
[Insérer la licence ici]

## Contact
[Vos informations de contact]
