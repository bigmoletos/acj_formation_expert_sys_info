"""Blueprint pour la gestion du cache des données."""
from flask import Blueprint

bp = Blueprint('cache', __name__, url_prefix='/cache')

from . import routes  # Import des routes après création du blueprint
