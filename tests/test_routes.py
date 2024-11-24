import pytest
from app import app, db
from app.models import User


@pytest.fixture
def client():
    app.config['TESTING'] = True
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'

    with app.test_client() as client:
        with app.app_context():
            db.create_all()
        yield client
        with app.app_context():
            db.drop_all()


def test_index_page(client):
    """Test de la page d'accueil"""
    response = client.get('/')
    assert response.status_code == 200
    assert b'Login' in response.data


def test_weather_page_without_city(client):
    """Test de la page météo sans ville spécifiée"""
    response = client.get('/weather')
    assert response.status_code == 302  # Redirection


def test_weather_page_with_city(client):
    """Test de la page météo avec une ville"""
    response = client.get('/weather?city=Paris')
    assert response.status_code == 200
    assert b'temperature' in response.data.lower()
