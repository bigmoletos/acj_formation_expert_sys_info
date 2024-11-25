import pytest
from unittest.mock import patch
from app import app


def test_index_get(client):
    """Test de la page d'accueil en GET."""
    response = client.get('/')
    assert response.status_code == 200
    assert b'Connexion' in response.data


def test_index_post_invalid(client):
    """Test de connexion avec des identifiants invalides."""
    response = client.post('/',
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
    mock_response = {'main': {'temp': 20.5}, 'name': 'Paris'}
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
    assert response.status_code == 302  # Redirection
