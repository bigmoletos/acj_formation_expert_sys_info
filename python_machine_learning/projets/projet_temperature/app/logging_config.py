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
from pathlib import Path

# Définition des niveaux de log valides
VALID_LOG_LEVELS = {
    'DEBUG': logging.DEBUG,
    'INFO': logging.INFO,
    'WARNING': logging.WARNING,
    'ERROR': logging.ERROR,
    'CRITICAL': logging.CRITICAL
}


def get_valid_log_level(level_str):
    """
    Convertit une chaîne de niveau de log en niveau logging valide

    Args:
        level_str (str): Niveau de log en string ('DEBUG', 'INFO', etc.)

    Returns:
        int: Niveau de log logging correspondant
    """
    # Convertir en majuscules et nettoyer la chaîne
    level_str = str(level_str).upper().strip()

    # Retourner le niveau correspondant ou DEBUG par défaut
    return VALID_LOG_LEVELS.get(level_str, logging.DEBUG)


def setup_logging(log_to_file=False, log_level='INFO', log_dir='logs'):
    """Configure le système de logging"""
    try:
        # Création du logger
        logger = logging.getLogger('app')

        # Conversion et validation du niveau de log
        validated_level = get_valid_log_level(log_level)
        logger.setLevel(validated_level)

        # Format du log
        formatter = logging.Formatter(
            '%(asctime)s - %(name)s - %(levelname)s - %(message)s')

        # Handler pour la console
        console_handler = logging.StreamHandler()
        console_handler.setFormatter(formatter)
        logger.addHandler(console_handler)

        # Configuration du logging dans un fichier si demandé
        if log_to_file:
            try:
                # Utilisation de Path pour gérer les chemins de manière cross-platform
                log_path = Path(log_dir)
                if not log_path.is_absolute():
                    # Si le chemin n'est pas absolu, créer dans le dossier du projet
                    log_path = Path.cwd() / log_dir

                # Création du répertoire de logs
                log_path.mkdir(parents=True, exist_ok=True)

                # Configuration du handler de fichier
                file_handler = RotatingFileHandler(
                    log_path / 'app.log',
                    maxBytes=1024 * 1024,  # 1 MB
                    backupCount=5)
                file_handler.setFormatter(formatter)
                logger.addHandler(file_handler)
                logger.info(f"Logging configuré dans le dossier: {log_path}")
            except Exception as e:
                logger.warning(
                    f"Impossible de configurer le logging fichier: {str(e)}")
                logger.warning("Continuité avec logging console uniquement")

        return logger

    except Exception as e:
        # Fallback logger en cas d'erreur
        fallback_logger = logging.getLogger('fallback')
        fallback_logger.setLevel(logging.DEBUG)
        console_handler = logging.StreamHandler()
        fallback_logger.addHandler(console_handler)
        fallback_logger.error(
            f"Erreur lors de la configuration du logging: {str(e)}")
        return fallback_logger


# Logger par défaut
def get_logger():
    """
    Retourne le logger configuré avec les paramètres par défaut

    Returns:
        logging.Logger: Logger configuré
    """
    log_to_file = os.environ.get('LOG_TO_FILE', 'False').lower() == 'true'
    log_level = os.environ.get('LOG_LEVEL', 'INFO')

    return setup_logging(log_to_file=log_to_file, log_level=log_level)

logger = get_logger()


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
