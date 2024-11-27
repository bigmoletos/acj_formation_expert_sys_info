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

# ##
# # @file __init__.py
# # @brief Module d'initialisation de l'application Flask
# ##

# from flask import Flask
# from flask_sqlalchemy import SQLAlchemy
# from flask_login import LoginManager
# from app.logging_config import setup_logging
# from app.config import Config
# import os
# import socket
# import sys

# # Configuration du logging
# logger = setup_logging(log_to_file=Config.LOG_TO_FILE,
#                        log_level=Config.LOG_LEVEL,
#                        log_dir=os.path.dirname(Config.LOG_FILE_PATH))

# try:
#     # Initialisation de l'application
#     app = Flask(__name__)

#     # Déterminer l'environnement
#     FLASK_ENV = os.environ.get('FLASK_ENV', 'development')
#     logger.info(f"Démarrage de l'application en mode: {FLASK_ENV}")

#     # Chargement de la configuration
#     app.config.from_object(Config)

#     # Configuration de base
#     app.config.update(SECRET_KEY=Config.SECRET_KEY,
#                       SQLALCHEMY_TRACK_MODIFICATIONS=False,
#                       LOG_LEVEL=Config.LOG_LEVEL,
#                       LOG_FILE_PATH=Config.LOG_FILE_PATH,
#                       OPENWEATHER_API_KEY=Config.API_KEY_OPENWEATHER,
#                       TESTING=Config.TESTING)

#     # Configuration de la base de données
#     if FLASK_ENV == 'testing' or Config.TESTING:
#         app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
#         logger.info("Mode test : Utilisation de SQLite en mémoire")
#     else:
#         app.config['SQLALCHEMY_DATABASE_URI'] = Config.get_database_url()
#         logger.info(
#             f"Mode normal : Utilisation de la base de données configurée : {Config.get_database_url()}"
#         )

#     # Initialisation des extensions
#     db = SQLAlchemy(app)
#     login_manager = LoginManager(app)
#     login_manager.login_view = 'login'
#     login_manager.login_message = "Veuillez vous connecter pour accéder à cette page."

#     # Import des routes après l'initialisation
#     from app import routes, models

#     # Création des tables si nécessaire
#     with app.app_context():
#         db.create_all()
#         logger.info("Base de données initialisée avec succès")

#     def run_app():
#         """Fonction pour démarrer l'application avec gestion des erreurs"""
#         try:
#             # Essayer d'abord le port par défaut
#             port = int(os.environ.get('PORT', 5001))
#             app.run(host='localhost',
#                     port=port,
#                     debug=app.config.get('DEBUG', False))
#         except socket.error as e:
#             logger.warning(f"Impossible d'utiliser le port {port}: {e}")
#             try:
#                 # Essayer un port alternatif
#                 alt_port = 8080
#                 logger.info(f"Tentative avec le port alternatif {alt_port}")
#                 app.run(host='localhost',
#                         port=alt_port,
#                         debug=app.config.get('DEBUG', False))
#             except socket.error as e2:
#                 logger.error(
#                     f"Impossible d'utiliser le port alternatif {alt_port}: {e2}"
#                 )
#                 try:
#                     # Dernier essai avec un port élevé
#                     high_port = 49152  # Port dynamique/privé
#                     logger.info(f"Dernière tentative avec le port {high_port}")
#                     app.run(host='localhost',
#                             port=high_port,
#                             debug=app.config.get('DEBUG', False))
#                 except Exception as e3:
#                     logger.critical(f"Impossible de démarrer le serveur: {e3}")
#                     sys.exit(1)

#     if __name__ == '__main__':
#         run_app()

# except Exception as e:
#     logger.critical(
#         f"Erreur fatale lors de l'initialisation de l'application: {str(e)}")
#     raise
