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
    username = StringField('Username',
                           validators=[DataRequired(),
                                       Length(min=4, max=64)])
    password = PasswordField('Password',
                             validators=[DataRequired(),
                                         Length(min=6)])
    password2 = PasswordField('Repeat Password',
                              validators=[DataRequired(),
                                          EqualTo('password')])
    submit = SubmitField('Register')

    def validate_username(self, username):
        user = User.query.filter_by(username=username.data).first()
        if user is not None:
            raise ValidationError('Please use a different username.')
