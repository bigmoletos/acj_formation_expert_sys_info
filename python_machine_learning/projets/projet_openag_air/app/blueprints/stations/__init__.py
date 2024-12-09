"""Blueprint pour la gestion des stations."""
from flask import Blueprint

bp = Blueprint('stations', __name__, url_prefix='/stations')

from . import routes  # Import des routes après création du blueprint
