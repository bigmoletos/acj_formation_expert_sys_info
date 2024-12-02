import pytest
from app import app, db
from app.models import User


@pytest.fixture(scope='module')
def test_app():
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
    app.config['TESTING'] = True

    with app.app_context():
        db.create_all()

        # Créer un utilisateur de test
        user = User(username='testuser')
        user.set_password('testpass')
        db.session.add(user)
        db.session.commit()

        yield app

        db.session.remove()
        db.drop_all()


def test_user_creation(test_app):
    """Test de création d'utilisateur en base"""
    with test_app.app_context():
        user = User.query.filter_by(username='testuser').first()
        assert user is not None
        assert user.username == 'testuser'
