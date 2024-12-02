import os
import tempfile
import pytest
from app import create_app, db
from app.models import User


@pytest.fixture
def app():
    """Crée une instance de l'application pour les tests"""
    # Configuration de test
    db_fd, db_path = tempfile.mkstemp()
    app = create_app()
    app.config.update({
        'TESTING': True,
        'SQLALCHEMY_DATABASE_URI': f'sqlite:///{db_path}',
        'WTF_CSRF_ENABLED': False,
        'SECRET_KEY': 'test_secret_key',
        'API_KEY_OPENWEATHER': 'test_api_key',
        'LOGIN_DISABLED': False
    })

    # Création du contexte d'application
    with app.app_context():
        db.create_all()

        # Création d'un utilisateur de test
        user = User(username='test_user')
        user.set_password('test_password')
        db.session.add(user)
        db.session.commit()

    yield app

    # Nettoyage
    with app.app_context():
        db.session.remove()
        db.drop_all()
    os.close(db_fd)
    os.unlink(db_path)


@pytest.fixture
def client(app):
    """Client de test"""
    return app.test_client()


@pytest.fixture
def runner(app):
    """Runner de test pour les commandes CLI"""
    return app.test_cli_runner()


@pytest.fixture
def auth(client):
    """Helper pour l'authentification"""

    class AuthActions:

        def __init__(self, client):
            self._client = client

        def login(self, username='test_user', password='test_password'):
            return self._client.post('/login',
                                     data={
                                         'username': username,
                                         'password': password
                                     },
                                     follow_redirects=True)

        def logout(self):
            return self._client.get('/logout', follow_redirects=True)

    return AuthActions(client)
