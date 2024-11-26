import pytest
from app import app, db
import os


@pytest.fixture(scope='session', autouse=True)
def setup_test_environment():
    """Configure l'environnement de test avant tous les tests"""
    os.environ['FLASK_ENV'] = 'testing'
    os.environ['TESTING'] = 'True'
    os.environ['DATABASE_URL'] = 'sqlite:///:memory:'
    yield
    # Nettoyage après les tests
    if 'FLASK_ENV' in os.environ:
        del os.environ['FLASK_ENV']
    if 'TESTING' in os.environ:
        del os.environ['TESTING']
    if 'DATABASE_URL' in os.environ:
        del os.environ['DATABASE_URL']


@pytest.fixture
def test_app():
    """Fixture pour l'application de test"""
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
    app.config['TESTING'] = True
    with app.app_context():
        db.create_all()
        yield app
        db.session.remove()
        db.drop_all()


@pytest.fixture
def test_client(test_app):
    """Fixture pour le client de test"""
    return test_app.test_client()


@pytest.fixture
def test_db(test_app):
    """Fixture pour la base de données de test"""
    return db
