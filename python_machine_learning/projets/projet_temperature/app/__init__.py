##
# @file __init__.py
# @brief Module d'initialisation de l'application Flask
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

# Initialisation de l'application
app = Flask(__name__)

try:
    # Déterminer l'environnement
    FLASK_ENV = os.environ.get('FLASK_ENV', 'development')
    logger.info(f"Démarrage de l'application en mode: {FLASK_ENV}")

    # Configuration de base
    app.config.update(
        SECRET_KEY=os.environ.get('SECRET_KEY', 'your_secret_key'),
        SQLALCHEMY_TRACK_MODIFICATIONS=False,
        LOG_LEVEL=os.environ.get('LOG_LEVEL', 'DEBUG'),
        LOG_FILE_PATH=os.environ.get('LOG_FILE_PATH', '/var/log/app.log'),
        OPENWEATHER_API_KEY=os.environ.get('API_KEY_OPENWEATHER'),
        TESTING=(FLASK_ENV == 'testing'))

    # Configuration de la base de données selon l'environnement
    if FLASK_ENV == 'testing' or os.environ.get('DATABASE_URL',
                                                '').startswith('sqlite'):
        # Utilisation de SQLite pour les tests ou si explicitement configuré
        app.config['SQLALCHEMY_DATABASE_URI'] = os.environ.get(
            'DATABASE_URL', 'sqlite:///:memory:')
        logger.info(
            f"Utilisation de SQLite: {app.config['SQLALCHEMY_DATABASE_URI']}")
    else:
        # Configuration MySQL pour les autres environnements
        db_params = {
            'user': os.environ.get('DB_USER', 'username'),
            'password': os.environ.get('DB_PASSWORD', 'password'),
            'host': os.environ.get('DB_HOST', 'localhost'),
            'port': os.environ.get('DB_PORT', '3306'),
            'database': os.environ.get('DB_NAME', 'temperature_db')
        }
        app.config['SQLALCHEMY_DATABASE_URI'] = (
            f"mysql+pymysql://{db_params['user']}:{db_params['password']}"
            f"@{db_params['host']}:{db_params['port']}/{db_params['database']}"
        )
        logger.info(
            f"Utilisation de MySQL sur {db_params['host']}:{db_params['port']}"
        )

    # Initialisation des extensions
    db = SQLAlchemy(app)
    login_manager = LoginManager(app)
    login_manager.login_view = 'login'
    login_manager.login_message = "Veuillez vous connecter pour accéder à cette page."

    # Import des routes après l'initialisation
    from app import routes, models

    # Création des tables si nécessaire
    if not app.config['TESTING']:  # Ne pas créer les tables en mode test
        with app.app_context():
            db.create_all()
            logger.info("Base de données initialisée avec succès")

except Exception as e:
    logger.critical(
        f"Erreur fatale lors de l'initialisation de l'application: {str(e)}")
    raise
