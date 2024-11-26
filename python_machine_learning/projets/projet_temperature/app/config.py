import os
from dotenv import load_dotenv
from pathlib import Path


# Chargement du fichier .env approprié
def load_environment():
    """Charge le fichier d'environnement approprié"""
    env_testing = Path('.env.testing')
    env_default = Path('.env')

    if os.environ.get('FLASK_ENV') == 'testing' and env_testing.exists():
        load_dotenv(env_testing)
        return 'testing'
    else:
        load_dotenv(env_default)
        return 'default'


# Chargement de l'environnement
CURRENT_ENV = load_environment()


class Config:
    """Configuration de l'application"""

    # Environnement
    FLASK_ENV = os.environ.get('FLASK_ENV', 'development')
    TESTING = FLASK_ENV == 'testing'
    FLASK_APP = os.environ.get('FLASK_APP', 'app')
    DEBUG = os.environ.get('DEBUG', 'True').lower() == 'true'
    BRANCH = os.environ.get('BRANCH', 'dev2')

    # Base de données
    if TESTING:
        SQLALCHEMY_DATABASE_URI = 'sqlite:///:memory:'
    else:
        # Configuration MySQL
        DB_HOST = os.environ.get('DB_HOST', 'localhost')
        DB_PORT = os.environ.get('DB_PORT', '5432')
        DB_USER = os.environ.get('DB_USER', 'username')
        DB_PASSWORD = os.environ.get('DB_PASSWORD', 'password')
        DB_ROOT_PASSWORD = os.environ.get('DB_ROOT_PASSWORD', '1234')
        DB_NAME = os.environ.get('DB_NAME', 'temperature_db')

        # Utilisateur Admin DB
        DB_USER_ADMIN = os.environ.get('DB_USER_ADMIN', 'admin')
        DB_PASSWORD_ADMIN = os.environ.get('DB_PASSWORD_ADMIN', 'password')

        # Utiliser DATABASE_URL s'il est défini, sinon construire l'URL MySQL
        SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL') or \
            f"mysql+pymysql://{DB_USER}:{DB_PASSWORD}@{DB_HOST}:{DB_PORT}/{DB_NAME}"

    # Configuration SQLAlchemy
    SQLALCHEMY_TRACK_MODIFICATIONS = False

    # Clés d'API et sécurité
    SECRET_KEY = os.environ.get('SECRET_KEY', 'your_secret_key')
    API_KEY_OPENWEATHER = os.environ.get('API_KEY_OPENWEATHER')
    GITHUB_TOKEN = os.environ.get('GITHUB_TOKEN')  # Pour GitHub Actions

    # Configuration API REST
    API_BASE_URL = os.environ.get('API_BASE_URL', 'https://127.0.0.1:5000/v1')
    API_TIMEOUT = int(os.environ.get('API_TIMEOUT', '30'))
    ALLOWED_HOSTS = os.environ.get('ALLOWED_HOSTS',
                                   'localhost,127.0.0.1').split(',')

    # Logging
    LOG_LEVEL = os.environ.get('LOG_LEVEL', 'DEBUG')
    LOG_FILE_PATH = os.environ.get('LOG_FILE_PATH', '/var/log/app.log')
    LOG_TO_FILE = os.environ.get('LOG_TO_FILE', 'False').lower() == 'true'

    # Redis Configuration
    REDIS_HOST = os.environ.get('REDIS_HOST', 'localhost')
    REDIS_PORT = int(os.environ.get('REDIS_PORT', '6379'))

    @classmethod
    def get_database_url(cls):
        """Retourne l'URL de la base de données"""
        return cls.SQLALCHEMY_DATABASE_URI

    @classmethod
    def is_testing(cls):
        """Vérifie si l'application est en mode test"""
        return cls.TESTING

    @classmethod
    def get_log_config(cls):
        """Retourne la configuration de logging"""
        return {
            'level': cls.LOG_LEVEL,
            'file_path': cls.LOG_FILE_PATH,
            'to_file': cls.LOG_TO_FILE and not cls.TESTING
        }

    @classmethod
    def validate_config(cls):
        """Valide la configuration actuelle"""
        required_vars = []

        # Variables requises selon l'environnement
        if not cls.TESTING:
            required_vars.extend(
                ['DB_USER', 'DB_PASSWORD', 'DB_NAME', 'DB_HOST', 'DB_PORT'])

        # Variables toujours requises
        required_vars.extend(
            ['SECRET_KEY', 'API_KEY_OPENWEATHER', 'FLASK_APP', 'FLASK_ENV'])

        missing_vars = [
            var for var in required_vars if not os.environ.get(var)
        ]

        if missing_vars:
            raise ValueError(
                f"Variables d'environnement manquantes : {', '.join(missing_vars)}"
            )

        return True
