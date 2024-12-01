import os
from dotenv import load_dotenv
from pathlib import Path


# Chargement du fichier .env approprié
def load_environment():
    """Charge le fichier d'environnement approprié"""
    env = os.environ.get('FLASK_ENV', 'development')

    # Charger d'abord le fichier .env par défaut
    default_env = Path('.env')
    if default_env.exists():
        load_dotenv(default_env)

    # Si en mode test, surcharger avec .env.testing
    if env == 'testing':
        env_file = Path('.env.testing')
    else:
        env_file = Path('.env')

    if env_file.exists():
        load_dotenv(env_file, override=True)
        return env
    else:
        raise FileNotFoundError(f"Fichier {env_file} non trouvé")


# Chargement de l'environnement
try:
    CURRENT_ENV = load_environment()
except Exception as e:
    print(f"Erreur lors du chargement de l'environnement: {e}")
    CURRENT_ENV = 'development'


class Config:
    """Configuration de l'application"""

    # Environnement
    FLASK_ENV = os.getenv('FLASK_ENV', 'development')
    TESTING = FLASK_ENV == 'testing'
    DEBUG = os.getenv('DEBUG', 'True').lower() == 'true'

    # Serveur
    HOST = os.getenv('HOST', '127.0.0.1')
    PORT = int(os.getenv('PORT', 5001))

    # Base de données
    if TESTING:
        SQLALCHEMY_DATABASE_URI = 'sqlite:///:memory:'
    else:
        DB_USER = os.getenv('DB_USER')
        DB_PASSWORD = os.getenv('DB_PASSWORD')
        DB_HOST = os.getenv('DB_HOST', 'localhost')
        DB_PORT = os.getenv('DB_PORT', '3306')
        DB_NAME = os.getenv('DB_NAME')

        SQLALCHEMY_DATABASE_URI = os.getenv('DATABASE_URL') or \
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
