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

# Initialisation des extensions
db = SQLAlchemy()
login_manager = LoginManager()


@login_manager.user_loader
def load_user(user_id):
    from app.models import User
    return User.query.get(int(user_id))


def create_app(config_name=None):
    app = Flask(__name__)

    # Configuration de base
    app.config['SECRET_KEY'] = os.environ.get('SECRET_KEY', 'your_secret_key')

    # Configuration de la base de données
    if os.environ.get('FLASK_ENV') == 'testing':
        app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
    else:
        app.config['SQLALCHEMY_DATABASE_URI'] = os.environ.get('DATABASE_URL')

    if not app.config['SQLALCHEMY_DATABASE_URI']:
        raise ValueError("DATABASE_URL n'est pas configuré")

    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
    app.config['OPENWEATHER_API_KEY'] = os.environ.get('API_KEY_OPENWEATHER')

    # Initialisation des extensions avec l'application
    db.init_app(app)
    login_manager.init_app(app)
    login_manager.login_view = 'main.login'
    login_manager.login_message = "Veuillez vous connecter pour accéder à cette page."

    with app.app_context():
        # Import et enregistrement des routes
        from app.routes import bp
        app.register_blueprint(bp)

        # Création des tables
        db.create_all()
        logger.info("Base de données initialisée avec succès")

    return app


# Création de l'application
app = create_app()
