import pytest
from flask import url_for
from app import db
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
    client.post(url_for('main.login'),
                data={
                    'username': 'test_user',
                    'password': 'test_password'
                })
    return client


def test_login_flow(client, test_user):
    """Test du flux de connexion complet"""
    # Test redirection vers login
    response = client.get('/')
    assert response.status_code == 302
    assert url_for('main.login') in response.location

    # Test page de login
    response = client.get(url_for('main.login'))
    assert response.status_code == 200
    assert b'Login' in response.data

    # Test connexion réussie
    response = client.post(url_for('main.login'),
                           data={
                               'username': 'test_user',
                               'password': 'test_password'
                           })
    assert response.status_code == 302
    assert url_for('main.weather') in response.location

    # Test connexion échouée
    response = client.post(url_for('main.login'),
                           data={
                               'username': 'wrong_user',
                               'password': 'wrong_password'
                           })
    assert response.status_code == 200
    assert b'Invalid username or password' in response.data


def test_weather_page(auth_client):
    """Test de la page météo"""
    # Test page météo sans ville
    response = auth_client.get(url_for('main.weather'))
    assert response.status_code == 200

    # Test page météo avec ville
    response = auth_client.get(url_for('main.weather', city='Paris'))
    assert response.status_code == 200
    assert b'Paris' in response.data


def test_logout(auth_client):
    """Test de déconnexion"""
    response = auth_client.get(url_for('main.logout'))
    assert response.status_code == 302
    assert url_for('main.login') in response.location
