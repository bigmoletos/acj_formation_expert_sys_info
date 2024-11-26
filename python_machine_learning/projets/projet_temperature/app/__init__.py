##
# @file __init__.py
# @brief Module d'initialisation de l'application Flask
##

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager
from app.logging_config import setup_logging
from app.config import Config
import os

# Configuration du logging
logger = setup_logging(log_to_file=Config.LOG_TO_FILE,
                       log_level=Config.LOG_LEVEL,
                       log_dir=os.path.dirname(Config.LOG_FILE_PATH))

try:
    # Initialisation de l'application
    app = Flask(__name__)

    # Déterminer l'environnement
    FLASK_ENV = os.environ.get('FLASK_ENV', 'development')
    logger.info(f"Démarrage de l'application en mode: {FLASK_ENV}")

    # Chargement de la configuration
    app.config.from_object(Config)

    # Validation de la configuration
    Config.validate_config()

    # Configuration de base
    app.config.update(SECRET_KEY=Config.SECRET_KEY,
                      SQLALCHEMY_TRACK_MODIFICATIONS=False,
                      LOG_LEVEL=Config.LOG_LEVEL,
                      LOG_FILE_PATH=Config.LOG_FILE_PATH,
                      OPENWEATHER_API_KEY=Config.API_KEY_OPENWEATHER,
                      TESTING=Config.TESTING)

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
            'user': Config.DB_USER,
            'password': Config.DB_PASSWORD,
            'host': Config.DB_HOST,
            'port': Config.DB_PORT,
            'database': Config.DB_NAME
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
