"""Configuration pour les tests"""


class TestConfig:
    TESTING = True
    SQLALCHEMY_DATABASE_URI = 'sqlite:///:memory:'
    SQLALCHEMY_TRACK_MODIFICATIONS = False
    SECRET_KEY = 'test_key'
    API_KEY_OPENWEATHER = 'test_key'
    LOG_TO_FILE = False
    LOG_LEVEL = 'DEBUG'
