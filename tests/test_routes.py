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


def test_home_page(client):
    """Test simple de la page d'accueil."""
    response = client.get('/')
    assert response.status_code == 302  # Redirection vers login


def test_login_page(client):
    """Test simple de la page de connexion."""
    response = client.get('/login')
    assert response.status_code == 200


def test_weather_page(client):
    """Test simple de la page météo."""
    response = client.get('/weather')
    assert response.status_code in [200,
                                    302]  # 200 ou redirection si auth requise
