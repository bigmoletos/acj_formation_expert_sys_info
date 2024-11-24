from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your_secret_key'
app.config[
    'SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://user:password@db:3306/temperature_db'
db = SQLAlchemy(app)
login_manager = LoginManager(app)

from app import routes, models
