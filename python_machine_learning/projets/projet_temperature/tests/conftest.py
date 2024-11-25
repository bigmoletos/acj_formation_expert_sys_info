import pytest
from app import app, db
from app.models import User


@pytest.fixture
def client():
    """Fixture pour créer un client de test."""
    app.config['TESTING'] = True
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
    app.config['WTF_CSRF_ENABLED'] = False
    app.config['OPENWEATHER_API_KEY'] = 'test_api_key'

    with app.test_client() as client:
        with app.app_context():
            db.create_all()
            yield client
            db.drop_all()


@pytest.fixture
def test_user():
    """Fixture pour créer un utilisateur de test."""
    user = User(username='testuser')
    user.set_password('testpass')
    return user


@pytest.fixture
def auth_client(client, test_user):
    """Fixture pour créer un client authentifié."""
    with app.app_context():
        db.session.add(test_user)
        db.session.commit()

        # Connexion
        client.post('/login',
                    data={
                        'username': 'testuser',
                        'password': 'testpass'
                    },
                    follow_redirects=True)

        return client


@pytest.fixture
def mock_weather_api(monkeypatch):
    """Fixture pour mocker l'API météo."""

    class MockResponse:

        def __init__(self, data, status_code=200):
            self.data = data
            self.status_code = status_code

        def json(self):
            return self.data

    def mock_get(*args, **kwargs):
        return MockResponse({
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
        })

    monkeypatch.setattr('requests.get', mock_get)
