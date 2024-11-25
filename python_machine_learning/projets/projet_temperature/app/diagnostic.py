import os
from dotenv import load_dotenv

load_dotenv()


class Config:
    """Configuration de l'application"""

    # Sécurité
    SECRET_KEY = os.environ.get('SECRET_KEY', 'your_secret_key')

    # Base de données
    SQLALCHEMY_TRACK_MODIFICATIONS = False
    SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL') or \
        f"mysql+pymysql://{os.environ.get('DB_USER')}:{os.environ.get('DB_PASSWORD')}@" \
        f"{os.environ.get('DB_HOST', 'localhost')}:{os.environ.get('DB_PORT', '3306')}/" \
        f"{os.environ.get('DB_NAME')}"

    # Logging
    LOG_LEVEL = os.environ.get('LOG_LEVEL', 'DEBUG')
    LOG_FILE_PATH = os.environ.get('LOG_FILE_PATH', '/var/log/app.log')
    LOG_TO_FILE = os.environ.get('LOG_TO_FILE', 'False').lower() == 'true'

    # API
    OPENWEATHER_API_KEY = os.environ.get('API_KEY_OPENWEATHER')


def verify_configuration():
    """Vérifie la configuration de l'application"""
    required_vars = [
        'SECRET_KEY', 'DB_USER', 'DB_PASSWORD', 'DB_NAME',
        'API_KEY_OPENWEATHER'
    ]

    missing_vars = []
    for var in required_vars:
        if not os.environ.get(var):
            missing_vars.append(var)

    if missing_vars:
        logger.error(
            f"Variables d'environnement manquantes : {', '.join(missing_vars)}"
        )
        return False

    logger.info("Configuration validée avec succès")
    return True
