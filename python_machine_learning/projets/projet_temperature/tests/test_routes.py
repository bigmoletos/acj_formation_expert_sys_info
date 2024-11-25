import pytest
from unittest.mock import patch
from app import app


def test_index_get(client):
    """Test de la page d'accueil en GET."""
    response = client.get('/')
    assert response.status_code == 302  # Redirection vers login

    response = client.get('/login')
    assert response.status_code == 200
    assert b'Connexion' in response.data


def test_index_post_invalid(client):
    """Test de connexion avec des identifiants invalides."""
    response = client.post('/login',
                           data={
                               'username': 'wronguser',
                               'password': 'wrongpass'
                           })
    assert response.status_code == 200
    assert b'Connexion' in response.data


@patch('requests.get')
def test_weather_valid_city(mock_get, auth_client):
    """Test de la route weather avec une ville valide."""
    # Mock de la réponse de l'API
    mock_response = {
        'main': {
            'temp': 20.5
        },
        'name': 'Paris',
        'weather': [{
            'description': 'ciel dégagé'
        }],
        'coord': {
            'lat': 48.8566,
            'lon': 2.3522
        }
    }
    mock_get.return_value.json.return_value = mock_response
    mock_get.return_value.status_code = 200

    response = auth_client.get('/weather?city=Paris')
    assert response.status_code == 200
    assert b'20.5' in response.data
    assert b'Paris' in response.data


@patch('requests.get')
def test_weather_invalid_city(mock_get, auth_client):
    """Test de la route weather avec une ville invalide."""
    # Mock d'une erreur de l'API
    mock_get.side_effect = Exception('City not found')

    response = auth_client.get('/weather?city=InvalidCity')
    assert response.status_code == 200  # Retourne la page avec un message d'erreur
    assert b'erreur' in response.data.lower()


def test_weather_no_city(auth_client):
    """Test de la route weather sans paramètre city."""
    response = auth_client.get('/weather')
    assert response.status_code == 200


@patch('requests.get')
def test_weather_api(mock_get, client):
    """Test de l'API météo."""
    mock_response = {
        'main': {
            'temp': 20.5
        },
        'name': 'Paris',
        'weather': [{
            'description': 'ciel dégagé'
        }],
        'coord': {
            'lat': 48.8566,
            'lon': 2.3522
        }
    }
    mock_get.return_value.json.return_value = mock_response
    mock_get.return_value.status_code = 200

    response = client.get('/api/weather/Paris')
    assert response.status_code == 200
    data = response.get_json()
    assert data['city'] == 'Paris'
    assert data['temperature'] == 20.5


def test_logout(auth_client):
    """Test de la déconnexion."""
    response = auth_client.get('/logout', follow_redirects=True)
    assert response.status_code == 200
    assert b'connexion' in response.data.lower()


def test_docs_access(client):
    """Test d'accès à la documentation."""
    response = client.get('/docs/')
    assert response.status_code == 200
