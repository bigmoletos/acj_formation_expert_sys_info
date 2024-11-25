import pytest
from app import app, db
from tests.config_test import TestConfig


@pytest.fixture
def test_app():
    app.config.from_object(TestConfig)
    with app.app_context():
        db.create_all()
        yield app
        db.session.remove()
        db.drop_all()


@pytest.fixture
def test_client(test_app):
    return test_app.test_client()


@pytest.fixture
def test_db():
    db.create_all()
    yield db
    db.session.remove()
    db.drop_all()
