# Guide de Lancement de l'Application Température

## 1. Environnement Virtuel
```bash
# Création
python -m venv venv

# Activation
# Windows :
venv\Scripts\activate
# Linux/Mac :
source venv/bin/activate
```

## 2. Installation des Dépendances
```bash
pip install -r requirements.txt
```

## 3. Configuration des Variables d'Environnement
Créer un fichier `.env` à la racine :
```env
FLASK_APP=app
FLASK_ENV=development
SECRET_KEY=votre_clé_secrète
DATABASE_URL=mysql+pymysql://user:password@localhost:3306/temperature_db
OPENWEATHER_API_KEY=votre_clé_api_openweathermap
```

## 4. Initialisation de la Base de Données
```python
# Dans l'interpréteur Python
python
>>> from app import db
>>> db.create_all()
>>> exit()
```

```bash
# Dans un shell Python
from app import app, db
from app.models import User

with app.app_context():
    # Vérifier si l'utilisateur existe déjà
    user = User.query.filter_by(username='admin').first()
    if not user:
        user = User(username='admin')
        user.set_password('password')
        db.session.add(user)
        db.session.commit()
        print("Utilisateur admin créé avec succès")
```


## 5. Lancement de l'Application
```bash
# Méthode 1
flask run

# Méthode 2
make run
```

## 6. Tests
```bash
# Tests complets
pytest

# Tests avec couverture
pytest --cov=app --cov-report=html
```

## 7. Accès à l'Application
- Interface web : http://localhost:5000
- API météo : http://localhost:5000/weather?city=Paris

## 8. Docker (Optionnel)
```bash
# Construction
docker build -t projet_temperature .

# Lancement
docker-compose up -d
```

## 9. Logs
- Emplacement : dossier `logs/`
- Contient les journaux d'erreurs et d'activité

## 10. URLs Disponibles
- `/` : Page d'accueil (connexion)
- `/weather?city=<nom_ville>` : Température d'une ville

## 11. Commandes Make
```bash
make help      # Liste des commandes
make install   # Installation
make test      # Tests
make docs      # Documentation
make clean     # Nettoyage
```

## 12. Résolution des Problèmes
- Vérifier les logs (`logs/`)
- Vérifier les dépendances
- Vérifier la base de données
- Vérifier la clé API OpenWeatherMap

## 13. Mode Développement
```bash
# Linux/Mac
export FLASK_DEBUG=1

# Windows
set FLASK_DEBUG=1

# Lancement debug
flask run --debug
```

## 14. Arrêt de l'Application
```bash
# Arrêt application
Ctrl+C

# Arrêt Docker
docker-compose down

# Désactivation venv
deactivate
```

## Points Importants
- ✅ Configurer la base de données
- ✅ Obtenir une clé API OpenWeatherMap
- ✅ Maintenir les dépendances à jour
- ✅ Sauvegarder régulièrement

## Dépannage Rapide
| Problème | Solution |
|----------|----------|
| Erreur de connexion BD | Vérifier DATABASE_URL dans .env |
| API météo ne répond pas | Vérifier OPENWEATHER_API_KEY |
| Erreur d'import | Vérifier l'activation du venv |
| Erreur de port | Vérifier si port 5000 libre |

## Notes
- Gardez une copie de `.env.example`
- Documentez les modifications
- Utilisez `make help` pour l'aide
- Consultez les logs régulièrement