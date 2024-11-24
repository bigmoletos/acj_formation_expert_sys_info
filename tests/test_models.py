import pytest
from app.models import User
from app import db, app


@pytest.fixture
def test_user():
    user = User(username='testuser')
    user.set_password('testpass')
    return user


def test_password_hashing(test_user):
    """Test du hashage des mots de passe"""
    assert test_user.check_password('testpass')
    assert not test_user.check_password('wrongpass')
