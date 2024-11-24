##
# @file logging_config.py
# @brief Configuration du système de logging pour l'application
#
# @details Configure les différents handlers et formatters pour le logging
# Permet de logger vers la console et/ou un fichier
##

import logging
import os
from logging.handlers import RotatingFileHandler
from datetime import datetime


##
# @brief Configure le système de logging
#
# @param log_to_file Si True, crée également un fichier de log
# @param log_level Niveau de log (DEBUG, INFO, WARNING, ERROR, CRITICAL)
# @param log_dir Répertoire où stocker les fichiers de log
# @return Logger configuré
##
def setup_logging(log_to_file=False, log_level=logging.INFO, log_dir='logs'):
    try:
        # Création du logger principal
        logger = logging.getLogger('temperature_app')
        logger.setLevel(log_level)

        # Format des logs
        formatter = logging.Formatter(
            '%(asctime)s - %(name)s - %(levelname)s - %(message)s')

        # Handler pour la console
        console_handler = logging.StreamHandler()
        console_handler.setFormatter(formatter)
        logger.addHandler(console_handler)

        # Configuration du logging vers un fichier si demandé
        if log_to_file:
            try:
                # Création du répertoire de logs s'il n'existe pas
                if not os.path.exists(log_dir):
                    os.makedirs(log_dir)

                # Nom du fichier de log avec la date
                log_file = os.path.join(
                    log_dir,
                    f'temperature_app_{datetime.now().strftime("%Y%m%d")}.log')

                # Handler pour le fichier avec rotation
                file_handler = RotatingFileHandler(
                    log_file,
                    maxBytes=1024 * 1024,  # 1 Mo
                    backupCount=5)
                file_handler.setFormatter(formatter)
                logger.addHandler(file_handler)

                logger.info(f"Logging configuré avec fichier: {log_file}")
            except Exception as e:
                logger.error(
                    f"Erreur lors de la création du fichier de log: {str(e)}")
                raise

        return logger

    except Exception as e:
        print(f"Erreur fatale lors de la configuration du logging: {str(e)}")
        raise


##
# @brief Fonction utilitaire pour logger les exceptions
# @param logger Logger à utiliser
# @param e Exception à logger
# @param message Message additionnel
##
def log_exception(logger, e, message="Une erreur est survenue"):
    try:
        logger.error(f"{message}: {str(e)}", exc_info=True)
    except Exception as logging_error:
        print(f"Erreur lors du logging de l'exception: {str(logging_error)}")


##
# @brief Décorateur pour logger les appels de fonction
# @param logger Logger à utiliser
##
def log_function_call(logger):

    def decorator(func):

        def wrapper(*args, **kwargs):
            try:
                logger.debug(
                    f"Appel de {func.__name__} avec args={args}, kwargs={kwargs}"
                )
                result = func(*args, **kwargs)
                logger.debug(f"Fin de {func.__name__}, retourne: {result}")
                return result
            except Exception as e:
                log_exception(logger, e, f"Erreur dans {func.__name__}")
                raise

        return wrapper

    return decorator
