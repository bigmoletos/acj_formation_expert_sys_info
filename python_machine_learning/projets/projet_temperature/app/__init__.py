from flask import Flask
from app.config import Config
from app.extensions import db, login_manager


def create_app(config_class=Config):
    app = Flask(__name__, instance_relative_config=True)
    app.config.from_object(config_class)

    # Initialize extensions
    db.init_app(app)
    login_manager.init_app(app)

    # Register blueprints
    from app.routes import main
    app.register_blueprint(main)

    # Create tables
    with app.app_context():
        db.create_all()

    return app
