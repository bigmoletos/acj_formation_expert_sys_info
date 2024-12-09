"""Module d'initialisation de l'application Flask."""
from flask import Flask
from dotenv import load_dotenv
import os
import logging
from .logging_config import configure_logging

# Charger les variables d'environnement
load_dotenv()


def create_app():
    """
    Crée et configure l'instance de l'application Flask.

    Returns:
        Flask: L'application Flask configurée
    """
    app = Flask(__name__)

    # Configuration
    app.config['SECRET_KEY'] = os.getenv('SECRET_KEY', 'dev_key')
    app.config['API_KEY'] = os.getenv('api_key')

    if not app.config['API_KEY']:
        raise ValueError(
            "La clé API OpenAQ n'est pas définie dans le fichier .env.")

    # Configuration du logging
    configure_logging()

    # Enregistrement des blueprints
    from .blueprints.pollution import bp as pollution_bp
    from .blueprints.stations import bp as stations_bp
    from .blueprints.cache import bp as cache_bp
    app.register_blueprint(pollution_bp)
    app.register_blueprint(stations_bp)
    app.register_blueprint(cache_bp)

    return app
