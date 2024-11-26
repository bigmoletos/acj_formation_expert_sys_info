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
    # Configuration de base
    app.config.update(SECRET_KEY=Config.SECRET_KEY,
                      SQLALCHEMY_TRACK_MODIFICATIONS=False,
                      LOG_LEVEL=Config.LOG_LEVEL,
                      LOG_FILE_PATH=Config.LOG_FILE_PATH,
                      OPENWEATHER_API_KEY=Config.API_KEY_OPENWEATHER,
                      TESTING=Config.TESTING)

    # Configuration de la base de données
    if FLASK_ENV == 'testing' or Config.TESTING:
        # Force SQLite pour les tests
        app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
        logger.info("Mode test : Utilisation de SQLite en mémoire")
    else:
        # Configuration normale pour l'environnement de développement/production
        app.config['SQLALCHEMY_DATABASE_URI'] = Config.get_database_url()
        logger.info(
            f"Mode normal : Utilisation de la base de données configurée : {Config.get_database_url()}"
        )
    # Définition du port et de l'hôte
    port = app.config.get('PORT', 5001)
    host = app.config.get('HOST', '127.0.0.1')

    # Initialisation des extensions
    db = SQLAlchemy(app)
    login_manager = LoginManager(app)
    login_manager.login_view = 'login'
    login_manager.login_message = "Veuillez vous connecter pour accéder à cette page."

    # Import des routes après l'initialisation
    from app import routes, models

    # Création des tables si nécessaire
    with app.app_context():
        db.create_all()
        logger.info("Base de données initialisée avec succès")

    if __name__ == '__main__':
        try:
            app.run(host=host, port=port, debug=app.config['DEBUG'])
        except OSError as e:
            logger.error(f"Erreur lors du démarrage du serveur: {str(e)}")
            # Essayer un autre port
            try:
                app.run(host=host, port=port + 1, debug=app.config['DEBUG'])
            except Exception as e:
                logger.critical(f"Impossible de démarrer le serveur: {str(e)}")
                raise

except Exception as e:
    logger.critical(
        f"Erreur fatale lors de l'initialisation de l'application: {str(e)}")
    raise
