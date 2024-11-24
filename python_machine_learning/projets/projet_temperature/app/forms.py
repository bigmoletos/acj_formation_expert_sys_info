##
# @file forms.py
# @brief Module de formulaires pour l'application
#
# @details Définit les différents formulaires WTForms utilisés dans l'application,
# notamment le formulaire de connexion
##

from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired


##
# @brief Formulaire de connexion utilisateur
#
# @var username Champ pour le nom d'utilisateur
# @var password Champ pour le mot de passe
# @var submit Bouton de soumission
##
class LoginForm(FlaskForm):
    username = StringField('Username', validators=[DataRequired()])
    password = PasswordField('Password', validators=[DataRequired()])
    submit = SubmitField('Login')
