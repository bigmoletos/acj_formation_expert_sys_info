##
# @file models.py
# @brief Module de modèles de données pour l'application
#
# @details Définit les modèles SQLAlchemy pour la persistance des données,
# notamment le modèle User pour la gestion des utilisateurs
##

from app import db, login_manager
from werkzeug.security import generate_password_hash, check_password_hash
from flask_login import UserMixin
from datetime import datetime


@login_manager.user_loader
def load_user(id):
    return User.query.get(int(id))


##
# @brief Modèle représentant un utilisateur dans l'application
#
# @details Stocke les informations d'authentification des utilisateurs
#
# @var id Identifiant unique de l'utilisateur
# @var username Nom d'utilisateur unique
# @var password Mot de passe hashé de l'utilisateur
##
class User(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(64), unique=True, nullable=False)
    password_hash = db.Column(db.String(128))
    searches = db.relationship('CitySearch', backref='user', lazy='dynamic')

    ##
    # @brief Hash et définit le mot de passe de l'utilisateur
    # @param password Mot de passe en clair à hasher
    ##
    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    ##
    # @brief Vérifie si le mot de passe fourni correspond au hash stocké
    # @param password Mot de passe à vérifier
    # @return True si le mot de passe correspond, False sinon
    ##
    def check_password(self, password):
        return check_password_hash(self.password_hash, password)


class CitySearch(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    city_name = db.Column(db.String(100), nullable=False)
    temperature = db.Column(db.Float)
    search_date = db.Column(db.DateTime, default=datetime.utcnow)
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'), nullable=False)
