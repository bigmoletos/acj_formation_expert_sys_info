import pytest
from flask import url_for


def test_home_page(client):
    """Test simple de la page d'accueil."""
    response = client.get('/')
    assert response.status_code == 302  # Redirection vers login


def test_login(client):
    """Test simple de la page de connexion."""
    # Test GET
    response = client.get('/login')
    assert response.status_code == 200

    # Test POST
    response = client.post('/login',
                           data={
                               'username': 'test',
                               'password': 'test'
                           })
    assert response.status_code == 302  # Redirection après login


def test_weather(client):
    """Test simple de la page météo."""
    response = client.get('/weather')
    assert response.status_code == 200


def test_logout(client):
    """Test simple de la déconnexion."""
    response = client.get('/logout')
    assert response.status_code == 302  # Redirection vers login
