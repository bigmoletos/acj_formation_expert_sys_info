import pytest
from unittest.mock import patch
from app.models import User
from app import db


def test_index_redirect(client):
    """Test que la page d'accueil redirige vers login"""
    response = client.get('/')
    assert response.status_code == 302
    assert '/login' in response.headers['Location']


def test_login_page(client):
    """Test que la page de login s'affiche correctement"""
    response = client.get('/login')
    assert response.status_code == 200
    assert b'Login' in response.data


def test_valid_login(client, auth):
    """Test qu'un login valide fonctionne"""
    response = auth.login()
    assert response.status_code == 200
    assert b'<h1>' in response.data
    assert b'search-form' in response.data


def test_invalid_login(client):
    """Test qu'un login invalide échoue"""
    response = client.post('/login',
                           data={
                               'username': 'wrong',
                               'password': 'wrong'
                           },
                           follow_redirects=True)
    assert response.status_code == 200
    assert b'Invalid username or password' in response.data


@pytest.mark.parametrize(('username', 'password', 'message'), (
    ('', '', b'This field is required'),
    ('test', '', b'This field is required'),
    ('test', 'short', b'Password must be at least 6 characters'),
))
def test_register_validate_input(client, username, password, message):
    """Test la validation des entrées lors de l'inscription"""
    response = client.post('/register',
                           data={
                               'username': username,
                               'password': password,
                               'password2': password
                           })
    assert message in response.data


@patch('app.routes.requests.get')
def test_weather_authenticated(mock_get, client, auth):
    """Test la route weather pour un utilisateur authentifié"""
    # Configuration du mock
    mock_get.return_value.status_code = 200
    mock_get.return_value.json.return_value = {
        'main': {
            'temp': 20
        },
        'weather': [{
            'description': 'clear sky'
        }],
        'name': 'Paris',
        'coord': {
            'lat': 48.8566,
            'lon': 2.3522
        }
    }

    # Login
    auth.login()

    # Test de la requête weather
    response = client.get('/weather?city=Paris')
    assert response.status_code == 200
    assert b'20' in response.data
    assert b'Paris' in response.data


def test_weather_unauthenticated(client):
    """Test que la route weather nécessite une authentification"""
    # Essayer d'accéder à la page météo sans être connecté
    response = client.get('/weather', follow_redirects=True)
    assert b'Please log in to access this page' in response.data

    # Vérifier qu'on est bien sur la page de login
    assert b'<h1>Login</h1>' in response.data


def test_logout(client, auth):
    """Test que le logout fonctionne"""
    auth.login()
    response = auth.logout()
    assert response.status_code == 200
    assert b'Login' in response.data

    response = client.get('/weather', follow_redirects=True)
    assert b'Please log in to access this page' in response.data


@pytest.fixture
def test_user(app):
    """Fixture pour créer un utilisateur de test"""
    with app.app_context():
        user = User(username='test_user2')
        user.set_password('test_password2')
        db.session.add(user)
        db.session.commit()
        return user


def test_user_model(app, test_user):
    """Test les méthodes du modèle User"""
    with app.app_context():
        # Récupérer une nouvelle instance de l'utilisateur depuis la base
        user = User.query.get(test_user.id)
        assert user.check_password('test_password2')
        assert not user.check_password('wrong_password')
