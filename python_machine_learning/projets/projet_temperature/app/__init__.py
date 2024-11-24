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
        'DATABASE_URL', 'mysql+pymysql://user:password@db:3306/temperature_db')
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

    # Initialisation des extensions
    try:
        db = SQLAlchemy(app)
        logger.info("Base de données initialisée avec succès")
    except Exception as e:
        logger.critical(
            f"Erreur lors de l'initialisation de la base de données: {str(e)}")
        raise

    try:
        login_manager = LoginManager(app)
        login_manager.login_view = 'index'
        logger.info("Login manager initialisé avec succès")
    except Exception as e:
        logger.critical(
            f"Erreur lors de l'initialisation du login manager: {str(e)}")
        raise

    # Import des routes après l'initialisation
    from app import routes, models
    logger.info("Application Flask initialisée avec succès")

except Exception as e:
    logger.critical(
        f"Erreur fatale lors de l'initialisation de l'application: {str(e)}")
    raise
