import pytest
from unittest.mock import patch
from app import app


@pytest.fixture
def mock_weather_response():
    return {'main': {'temp': 20.5}}


def test_weather_api_integration(client, mock_weather_response):
    """Test de l'intégration avec l'API météo"""
    with patch('requests.get') as mock_get:
        mock_get.return_value.json.return_value = mock_weather_response
        mock_get.return_value.status_code = 200

        response = client.get('/weather?city=Paris')
        assert response.status_code == 200
        assert b'20.5' in response.data
