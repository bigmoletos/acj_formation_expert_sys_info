"""Configuration du logging pour l'application."""
import logging
import os
from logging.handlers import RotatingFileHandler


def configure_logging():
    """Configure le système de logging de l'application."""
    # Créer le dossier logs s'il n'existe pas
    if not os.path.exists('logs'):
        os.makedirs('logs')

    # Configuration du handler de fichier
    file_handler = RotatingFileHandler('logs/openaq.log',
                                       maxBytes=10240,
                                       backupCount=10)
    file_handler.setFormatter(
        logging.Formatter(
            '%(asctime)s %(levelname)s: %(message)s [in %(pathname)s:%(lineno)d]'
        ))
    file_handler.setLevel(logging.INFO)

    # Configuration du logger
    logger = logging.getLogger('openaq')
    logger.setLevel(logging.INFO)
    logger.addHandler(file_handler)

    logger.info('OpenAQ startup')
