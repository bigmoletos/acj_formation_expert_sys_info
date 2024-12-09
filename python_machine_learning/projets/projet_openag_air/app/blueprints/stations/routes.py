"""Routes pour la gestion des stations."""
from flask import jsonify, current_app
from . import bp
from ...services.stations_service import StationsService
import logging

logger = logging.getLogger('openaq')


@bp.route('/list/<country>')
def list_stations(country):
    """Liste toutes les stations d'un pays."""
    try:
        service = StationsService(api_key=current_app.config['API_KEY'])
        stations = service.get_stations_by_country(country)
        return jsonify(stations)
    except Exception as e:
        logger.error(f"Erreur lors de la récupération des stations: {str(e)}")
        return jsonify({"error": str(e)}), 400


@bp.route('/list/<country>/<city>')
def list_city_stations(country, city):
    """Liste les stations d'une ville."""
    try:
        service = StationsService(api_key=current_app.config['API_KEY'])
        stations = service.get_stations_by_city(country, city)
        return jsonify(stations)
    except Exception as e:
        logger.error(
            f"Erreur lors de la récupération des stations de {city}: {str(e)}")
        return jsonify({"error": str(e)}), 400
