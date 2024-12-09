"""Routes pour la gestion du cache."""
from flask import jsonify, current_app
from . import bp
from ...services.cache_service import CacheService
import logging
import requests

logger = logging.getLogger('openaq')


@bp.route('/data/<country>')
def get_country_data(country):
    """
    Récupère toutes les données d'un pays (depuis le cache si possible).

    Args:
        country: Code pays (ex: FR)
    """
    try:
        service = CacheService(api_key=current_app.config['API_KEY'])
        data = service.load_cache(country)
        return jsonify(data)
    except Exception as e:
        logger.error(f"Erreur lors de la récupération des données: {str(e)}")
        return jsonify({"error": str(e)}), 400


@bp.route('/update/<country>')
def update_country_data(country):
    """
    Force la mise à jour du cache pour un pays.

    Args:
        country: Code pays (ex: FR)
    """
    try:
        service = CacheService(api_key=current_app.config['API_KEY'])
        data = service.update_cache(country)
        return jsonify(data)
    except Exception as e:
        logger.error(f"Erreur lors de la mise à jour du cache: {str(e)}")
        return jsonify({"error": str(e)}), 400


@bp.route('/cities/<country>')
def get_cities(country):
    """
    Récupère la liste des villes disponibles pour un pays.

    Args:
        country: Code pays (ex: FR)
    """
    try:
        service = CacheService(api_key=current_app.config['API_KEY'])
        data = service.load_cache(country)
        cities = list(data.get('cities', {}).keys())
        return jsonify({'country': country, 'cities': sorted(cities)})
    except Exception as e:
        logger.error(f"Erreur lors de la récupération des villes: {str(e)}")
        return jsonify({"error": str(e)}), 400


@bp.route('/countries')
def get_countries():
    """Récupère la liste des pays disponibles."""
    try:
        url = "https://api.openaq.org/v3/countries"
        headers = {"X-API-Key": current_app.config['API_KEY']}
        params = {"limit": 1000, "page": 1, "offset": 0}

        response = requests.get(url, headers=headers, params=params)
        response.raise_for_status()
        data = response.json()

        countries = [{
            'id': country['code'],
            'name': country['name'],
            'locations': country.get('locations', 0)
        } for country in data.get('results', [])]

        return jsonify(
            {'countries': sorted(countries, key=lambda x: x['name'])})
    except Exception as e:
        logger.error(f"Erreur lors de la récupération des pays: {str(e)}")
        return jsonify({"error": str(e)}), 400
