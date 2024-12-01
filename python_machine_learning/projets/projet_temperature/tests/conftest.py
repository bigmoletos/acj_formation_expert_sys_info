import pytest
from app import create_app, db


@pytest.fixture
def app():
    app = create_app()
    app.config.update({
        'TESTING': True,
        'WTF_CSRF_ENABLED': False,
        'SQLALCHEMY_DATABASE_URI': 'sqlite:///:memory:'
    })

    with app.app_context():
        db.create_all()

    return app


@pytest.fixture
def client(app):
    return app.test_client()
