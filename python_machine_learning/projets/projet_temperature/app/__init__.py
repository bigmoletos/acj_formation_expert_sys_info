from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager
from app.logging_config import setup_logging
import os
from dotenv import load_dotenv
from flask_migrate import Migrate
import click
from flask.cli import with_appcontext
from pathlib import Path

# Chargement des variables d'environnement
load_dotenv()

# Configuration du logging
logger = setup_logging(log_to_file=os.environ.get('LOG_TO_FILE',
                                                  'False').lower() == 'true',
                       log_level=os.environ.get('LOG_LEVEL', 'INFO'),
                       log_dir=os.environ.get('LOG_DIR', 'logs'))

# Initialisation des extensions
db = SQLAlchemy()
migrate = Migrate()
login_manager = LoginManager()


@login_manager.user_loader
def load_user(user_id):
    from app.models import User
    return User.query.get(int(user_id))


def create_app(config_name=None):
    app = Flask(
        __name__,
        static_folder=
        'templates/docs/html',  # Permettre l'accès aux fichiers statiques de la doc
        static_url_path='/docs/static')

    # S'assurer que le dossier instance existe
    instance_path = Path(app.instance_path)
    instance_path.mkdir(parents=True, exist_ok=True)

    # Configuration de base
    app.config['SECRET_KEY'] = os.environ.get('SECRET_KEY', 'your_secret_key')

    # Configuration de la base de données
    if os.environ.get('FLASK_ENV') == 'testing':
        app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
    else:
        db_path = instance_path / 'app.db'
        app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{db_path}'

    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
    app.config['OPENWEATHER_API_KEY'] = os.environ.get('API_KEY_OPENWEATHER')

    # Initialisation des extensions avec l'application
    db.init_app(app)
    migrate.init_app(app, db)
    login_manager.init_app(app)
    login_manager.login_view = 'main.login'
    login_manager.login_message = "Please log in to access this page"

    # Ajout de la commande generate-docs
    @app.cli.command('generate-docs')
    def generate_docs_command():
        """Génère la documentation avec Doxygen."""
        from app.generate_docs import generate_documentation
        if generate_documentation():
            click.echo('Documentation générée avec succès.')
        else:
            click.echo('Erreur lors de la génération de la documentation.')

    with app.app_context():
        # Import et enregistrement des routes
        from app.routes import bp
        app.register_blueprint(bp)

        # Vérifier si les tables existent déjà
        from sqlalchemy import inspect
        inspector = inspect(db.engine)
        if not inspector.has_table("user"):
            db.create_all()
            logger.info("Tables créées avec succès")

    return app


# Création de l'application
app = create_app()
