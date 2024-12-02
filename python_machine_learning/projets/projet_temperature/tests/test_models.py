import pytest
from app.models import User
from app import db


@pytest.fixture
def app_context(app):
    """Fixture pour fournir un contexte d'application"""
    with app.app_context():
        db.create_all()
        yield
        db.session.remove()
        db.drop_all()


@pytest.fixture
def test_user(app, app_context):
    """Fixture pour créer un utilisateur de test"""
    user = User(
        username='test_user_unique')  # Nom unique pour éviter les conflits
    user.set_password('test_password')
    db.session.add(user)
    db.session.commit()
    return user


def test_user_creation(app, app_context):
    """Test la création d'un utilisateur"""
    user = User(username='test_user_creation')  # Nom unique
    user.set_password('test_password')
    db.session.add(user)
    db.session.commit()

    assert user.username == 'test_user_creation'
    assert user.password_hash is not None


def test_password_hashing(app, app_context):
    """Test le hashage des mots de passe"""
    user = User(username='test_user_password')  # Nom unique
    user.set_password('test_password')
    db.session.add(user)
    db.session.commit()

    assert not user.check_password('wrong_password')
    assert user.check_password('test_password')
