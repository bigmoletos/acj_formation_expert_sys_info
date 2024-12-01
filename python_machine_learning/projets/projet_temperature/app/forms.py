##
# @file forms.py
# @brief Module de formulaires pour l'application
#
# @details Définit les différents formulaires WTForms utilisés dans l'application,
# notamment le formulaire de connexion
##

from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired, Length, EqualTo, ValidationError
from app.models import User


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


class RegistrationForm(FlaskForm):
    username = StringField(
        'Username',
        validators=[
            DataRequired(message="This field is required"),
            Length(min=4,
                   max=64,
                   message="Username must be between 4 and 64 characters")
        ])
    password = PasswordField(
        'Password',
        validators=[
            DataRequired(message="This field is required"),
            Length(min=6, message="Password must be at least 6 characters")
        ])
    password2 = PasswordField(
        'Repeat Password',
        validators=[
            DataRequired(message="This field is required"),
            EqualTo('password', message='Passwords must match')
        ])
    submit = SubmitField('Register')

    def validate_username(self, username):
        user = User.query.filter_by(username=username.data).first()
        if user is not None:
            raise ValidationError('Please use a different username.')
