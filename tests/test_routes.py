import pytest
from flask import url_for
from app import create_app, db
from app.models import User


@pytest.fixture
def test_user(app):
    """Fixture pour créer un utilisateur de test."""
    with app.app_context():
        user = User(username='test_user')
        user.set_password('test_password')
        db.session.add(user)
        db.session.commit()
        return user


@pytest.fixture
def auth_client(client, test_user):
    """Fixture pour créer un client authentifié."""
    with client.session_transaction() as session:
        client.post('/login',
                    data={
                        'username': 'test_user',
                        'password': 'test_password'
                    })
    return client


def test_index_page(client):
    """Test de la page d'accueil"""
    response = client.get('/')
    assert response.status_code == 302  # Redirection vers login
    assert '/login' in response.location


def test_login_page(client):
    """Test de la page de connexion"""
    response = client.get('/login')
    assert response.status_code == 200
    assert b'Login' in response.data


def test_login_post_valid(client):
    """Test de connexion valide"""
    response = client.post('/login',
                           data={
                               'username': 'test_user',
                               'password': 'test_password'
                           })
    assert response.status_code == 302
    assert '/weather' in response.location


def test_login_post_invalid(client):
    """Test de connexion invalide"""
    response = client.post('/login',
                           data={
                               'username': 'wrong_user',
                               'password': 'wrong_password'
                           })
    assert response.status_code == 200
    assert b'Invalid username or password' in response.data


def test_weather_page_without_city(auth_client):
    """Test de la page météo sans ville spécifiée"""
    response = auth_client.get('/weather')
    assert response.status_code == 200


def test_weather_page_with_city(auth_client):
    """Test de la page météo avec une ville"""
    response = auth_client.get('/weather?city=Paris')
    assert response.status_code == 200
    assert b'temperature' in response.data.lower()


def test_weather_api(auth_client):
    """Test de l'API météo"""
    # Test avec une ville valide
    response = auth_client.get('/weather?city=Paris')
    assert response.status_code == 200
    assert b'temperature' in response.data.lower()
    assert b'city' in response.data.lower()

    # Test sans ville spécifiée
    response = auth_client.get('/weather')
    assert response.status_code == 200


def test_docs_access(client):
    """Test d'accès à la documentation"""
    # Test avec et sans slash final
    for path in ['/docs', '/docs/']:
        response = client.get(path)
        assert response.status_code == 200
        assert b'Documentation API' in response.data


def test_logout(auth_client):
    """Test de déconnexion"""
    response = auth_client.get('/logout')
    assert response.status_code == 302
    assert '/login' in response.location
