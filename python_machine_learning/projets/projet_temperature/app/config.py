import os
from dotenv import load_dotenv

load_dotenv()


class Config:
    """Configuration de l'application"""

    # Clés d'API
    SECRET_KEY = os.environ.get('SECRET_KEY', 'your_secret_key')
    API_KEY_OPENWEATHER = os.environ.get('API_KEY_OPENWEATHER')
    BRANCH = os.environ.get('BRANCH', 'dev2')

    # Configuration de la Base de Données
    DB_HOST = os.environ.get('DB_HOST', 'localhost')
    DB_PORT = os.environ.get('DB_PORT', '5432')
    DB_USER = os.environ.get('DB_USER', 'username')
    DB_PASSWORD = os.environ.get('DB_PASSWORD', 'password')
    DB_ROOT_PASSWORD = os.environ.get('DB_ROOT_PASSWORD', '1234')
    DB_NAME = os.environ.get('DB_NAME', 'temperature_db')

    # Configuration SQLAlchemy
    SQLALCHEMY_TRACK_MODIFICATIONS = False
    SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL') or \
        f"mysql+pymysql://{DB_USER}:{DB_PASSWORD}@{DB_HOST}:{DB_PORT}/{DB_NAME}"

    # Utilisateur Administrateur de la Base de Données
    DB_USER_ADMIN = os.environ.get('DB_USER_ADMIN', 'admin')
    DB_PASSWORD_ADMIN = os.environ.get('DB_PASSWORD_ADMIN', 'password')

    # Configuration de l'environnement Flask
    FLASK_APP = os.environ.get('FLASK_APP', 'app')
    FLASK_ENV = os.environ.get('FLASK_ENV', 'development')
    DEBUG = os.environ.get('DEBUG', 'True').lower() == 'true'
    ALLOWED_HOSTS = os.environ.get('ALLOWED_HOSTS',
                                   'localhost,127.0.0.1').split(',')

    # Configuration API REST
    API_BASE_URL = os.environ.get('API_BASE_URL', 'https://127.0.0.1:5000/v1')
    API_TIMEOUT = int(os.environ.get('API_TIMEOUT', '30'))

    # Configuration de Logging
    LOG_LEVEL = os.environ.get('LOG_LEVEL', 'DEBUG')
    LOG_FILE_PATH = os.environ.get('LOG_FILE_PATH', '/var/log/app.log')
    LOG_TO_FILE = os.environ.get('LOG_TO_FILE', 'False').lower() == 'true'

    # Configuration Redis
    REDIS_HOST = os.environ.get('REDIS_HOST', 'localhost')
    REDIS_PORT = int(os.environ.get('REDIS_PORT', '6379'))

    @classmethod
    def get_database_url(cls):
        """Retourne l'URL de la base de données"""
        return cls.SQLALCHEMY_DATABASE_URI

    @classmethod
    def is_development(cls):
        """Vérifie si l'application est en mode développement"""
        return cls.FLASK_ENV == 'development'

    @classmethod
    def get_log_config(cls):
        """Retourne la configuration de logging"""
        return {
            'level': cls.LOG_LEVEL,
            'file_path': cls.LOG_FILE_PATH,
            'to_file': cls.LOG_TO_FILE
        }
