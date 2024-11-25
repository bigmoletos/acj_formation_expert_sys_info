import pytest
from app.models import User
from app import db


def test_user_creation(client):
    """Test de la création d'un utilisateur."""
    user = User(username='testuser')
    user.set_password('testpass')

    assert user.username == 'testuser'
    assert user.password != 'testpass'  # Le mot de passe doit être hashé
    assert user.check_password('testpass')
    assert not user.check_password('wrongpass')


def test_user_unique_username(client):
    """Test de l'unicité du nom d'utilisateur."""
    user1 = User(username='testuser')
    user1.set_password('testpass')

    with pytest.raises(Exception):
        # Tentative de création d'un utilisateur avec le même username
        user2 = User(username='testuser')
        user2.set_password('testpass')

        db.session.add(user1)
        db.session.add(user2)
        db.session.commit()


def test_password_hashing():
    """Test du hashage des mots de passe."""
    user = User(username='testuser')
    user.set_password('testpass')

    # Vérifie que le mot de passe est bien hashé
    assert user.password != 'testpass'

    # Vérifie que le hash est différent pour le même mot de passe
    user2 = User(username='testuser2')
    user2.set_password('testpass')
    assert user.password != user2.password
