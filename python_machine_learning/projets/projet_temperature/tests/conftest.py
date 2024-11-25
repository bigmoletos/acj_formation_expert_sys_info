import pytest
from app import app, db
from app.models import User


@pytest.fixture
def client():
    """Fixture pour créer un client de test."""
    app.config['TESTING'] = True
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
    app.config['WTF_CSRF_ENABLED'] = False

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

        client.post('/login',
                    data={
                        'username': 'testuser',
                        'password': 'testpass'
                    },
                    follow_redirects=True)

        return client
