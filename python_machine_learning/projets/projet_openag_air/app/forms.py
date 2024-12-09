"""Formulaires de l'application."""
from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField
from wtforms.validators import DataRequired


class CitySearchForm(FlaskForm):
    """Formulaire de recherche par ville."""
    city_name = StringField('Nom de la ville', validators=[DataRequired()])
    submit = SubmitField('Rechercher')
