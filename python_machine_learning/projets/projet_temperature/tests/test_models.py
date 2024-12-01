import pytest
from app.models import User
from app import db


@pytest.fixture
def user(app):
    """Fixture pour créer un utilisateur de test"""
    with app.app_context():
        user = User(username='test_user')
        user.set_password('test_password')
        db.session.add(user)
        db.session.commit()
        return user


def test_user_creation(app, user):
    """Test la création d'un utilisateur"""
    with app.app_context():
        assert user.username == 'test_user'
        assert user.password_hash is not None


def test_password_hashing(app, user):
    """Test le hashage des mots de passe"""
    with app.app_context():
        assert not user.check_password('wrong_password')
        assert user.check_password('test_password')
