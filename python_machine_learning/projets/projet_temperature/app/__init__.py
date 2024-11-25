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

    # Configuration de base
    app.config.update(
        SECRET_KEY=os.environ.get('SECRET_KEY', 'your_secret_key'),
        SQLALCHEMY_TRACK_MODIFICATIONS=False,
        LOG_LEVEL=os.environ.get('LOG_LEVEL', 'DEBUG'),
        LOG_FILE_PATH=os.environ.get('LOG_FILE_PATH', '/var/log/app.log'),
        OPENWEATHER_API_KEY=os.environ.get('API_KEY_OPENWEATHER'))

    # Configuration de la base de données
    if os.environ.get('FLASK_ENV') == 'testing':
        # Utiliser SQLite pour les tests
        app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
        logger.info("Utilisation de SQLite en mémoire pour les tests")
    else:
        # Configuration normale pour MySQL
        database_url = os.environ.get('DATABASE_URL')
        if not database_url:
            database_url = f"mysql+pymysql://{os.environ.get('DB_USER')}:{os.environ.get('DB_PASSWORD')}@{os.environ.get('DB_HOST', 'localhost')}:{os.environ.get('DB_PORT', '3306')}/{os.environ.get('DB_NAME')}"
        app.config['SQLALCHEMY_DATABASE_URI'] = database_url
        logger.info(f"Utilisation de MySQL avec l'URL: {database_url}")

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
