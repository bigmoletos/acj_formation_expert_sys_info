"""Blueprint pour la gestion des données de pollution."""
from flask import Blueprint

bp = Blueprint('pollution', __name__)

from . import routes  # Import des routes après création du blueprint
