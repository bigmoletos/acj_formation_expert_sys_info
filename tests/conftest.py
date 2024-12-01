import pytest
from app import create_app, db
from app.models import User


@pytest.fixture
def app():
    app = create_app()
    app.config.update({
        'TESTING': True,
        'SQLALCHEMY_DATABASE_URI': 'sqlite:///:memory:',
        'WTF_CSRF_ENABLED': False,
        'OPENWEATHER_API_KEY': 'test_key',
        'SECRET_KEY': 'test_key'
    })

    # S'assurer que les routes sont enregistrées
    with app.app_context():
        db.create_all()
        # Créer un utilisateur de test si nécessaire
        if not User.query.filter_by(username='test_user').first():
            user = User(username='test_user')
            user.set_password('test_password')
            db.session.add(user)
            db.session.commit()

    return app


@pytest.fixture
def client(app):
    return app.test_client()


@pytest.fixture
def runner(app):
    return app.test_cli_runner()
