##
# @file models.py
# @brief Module de modèles de données pour l'application
#
# @details Définit les modèles SQLAlchemy pour la persistance des données,
# notamment le modèle User pour la gestion des utilisateurs
##

from app import db
from werkzeug.security import generate_password_hash, check_password_hash


##
# @brief Modèle représentant un utilisateur dans l'application
#
# @details Stocke les informations d'authentification des utilisateurs
#
# @var id Identifiant unique de l'utilisateur
# @var username Nom d'utilisateur unique
# @var password Mot de passe hashé de l'utilisateur
##
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(150), nullable=False, unique=True)
    password = db.Column(db.String(150), nullable=False)

    ##
    # @brief Hash et définit le mot de passe de l'utilisateur
    # @param password Mot de passe en clair à hasher
    ##
    def set_password(self, password):
        self.password = generate_password_hash(password)

    ##
    # @brief Vérifie si le mot de passe fourni correspond au hash stocké
    # @param password Mot de passe à vérifier
    # @return True si le mot de passe correspond, False sinon
    ##
    def check_password(self, password):
        return check_password_hash(self.password, password)
