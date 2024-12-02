import os
from pathlib import Path

# Chemin de base du projet
basedir = Path(__file__).parent.parent
instance_path = basedir / 'instance'

# Créer le dossier instance s'il n'existe pas
instance_path.mkdir(parents=True, exist_ok=True)


class Config:
    """Configuration de l'application"""

    # Sécurité
    SECRET_KEY = os.environ.get('SECRET_KEY', 'dev')

    # Base de données
    SQLALCHEMY_DATABASE_URI = f'sqlite:///{instance_path / "app.db"}'
    SQLALCHEMY_TRACK_MODIFICATIONS = False

    # API OpenWeather
    API_KEY_OPENWEATHER = os.environ.get('API_KEY_OPENWEATHER')

    # Autres configurations
    DEBUG = True
    TESTING = False
