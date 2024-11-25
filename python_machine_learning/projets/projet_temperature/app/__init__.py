##
# @file __init__.py
# @brief Module d'initialisation de l'application Flask
#
# @details Configure l'application Flask et ses extensions :
# - SQLAlchemy pour la base de données
# - LoginManager pour la gestion de l'authentification
##

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager
from app.logging_config import setup_logging
import os
from dotenv import load_dotenv

# Chargement des variables d'environnement
load_dotenv()

# Configuration du logging
logger = setup_logging(log_to_file=os.environ.get('LOG_TO_FILE',
                                                  'False').lower() == 'true',
                       log_level=os.environ.get('LOG_LEVEL', 'INFO'),
                       log_dir=os.environ.get('LOG_DIR', 'logs'))

try:
    # Initialisation de l'application
    app = Flask(__name__)

    # Configuration
    app.config['SECRET_KEY'] = os.environ.get('SECRET_KEY', 'your_secret_key')
    app.config['SQLALCHEMY_DATABASE_URI'] = os.environ.get(
        'DATABASE_URL', 'sqlite:///app.db')  # SQLite par défaut
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
    app.config['OPENWEATHER_API_KEY'] = os.environ.get('API_KEY_OPENWEATHER')
    logger.debug(f"Clé API chargée: {app.config['OPENWEATHER_API_KEY']}")

    # Initialisation des extensions
    db = SQLAlchemy(app)
    login_manager = LoginManager(app)
    login_manager.login_view = 'login'
    login_manager.login_message = "Veuillez vous connecter pour accéder à cette page."

    # Import des routes après l'initialisation
    from app import routes, models

    # Création des tables si elles n'existent pas
    with app.app_context():
        db.create_all()
        logger.info("Base de données initialisée avec succès")

except Exception as e:
    logger.critical(
        f"Erreur fatale lors de l'initialisation de l'application: {str(e)}")
    raise
