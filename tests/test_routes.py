import pytest
from app import create_app, db
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
    assert response.status_code == 302  # Redirection vers login
    assert response.location == '/login'


def test_login_page(client):
    """Test de la page de connexion"""
    response = client.get('/login')
    assert response.status_code == 200
    assert b'Login' in response.data


def test_weather_page_without_city(client):
    """Test de la page météo sans ville spécifiée"""
    response = client.get('/weather')
    assert response.status_code == 200  # Retourne le template vide


def test_weather_page_with_city(client):
    """Test de la page météo avec une ville"""
    response = client.get('/weather?city=Paris')
    assert response.status_code in [200, 404]
    if response.status_code == 200:
        assert b'temperature' in response.data.lower()


def test_weather_api(client):
    """Test de l'API météo"""
    # Test avec une ville valide
    response = client.get('/weather?city=Paris')
    assert response.status_code in [200,
                                    404]  # 404 acceptable si ville non trouvée

    if response.status_code == 200:
        assert b'temperature' in response.data.lower()
        assert b'city' in response.data.lower()
    else:
        data = response.get_json()
        assert 'error' in data

    # Test sans ville spécifiée
    response = client.get('/weather')
    assert response.status_code == 200  # Devrait retourner le template


def test_docs_access(client):
    """Test d'accès à la documentation"""
    response = client.get('/docs')
    assert response.status_code == 200
    assert b'Documentation API' in response.data
