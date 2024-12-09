"""Routes de l'application."""
from flask import Blueprint, render_template, request, current_app
import folium
import logging
from .forms import CitySearchForm
from .openaq_client import OpenAQLocationFetcher

# Création du blueprint
main_bp = Blueprint('main', __name__)
logger = logging.getLogger('openaq')


@main_bp.route("/", methods=["GET", "POST"])
def index():
    """Page principale avec formulaire de recherche."""
    form = CitySearchForm()

    if form.validate_on_submit():
        city_name = form.city_name.data.strip()
        logger.info(f"Recherche pour la ville: {city_name}")

        try:
            # Initialiser le fetcher OpenAQ
            fetcher = OpenAQLocationFetcher(
                api_key=current_app.config['API_KEY'])

            # Rechercher les données par ville
            url = "https://api.openaq.org/v3/locations"
            params = {"city": city_name, "limit": 1}
            headers = {"X-API-Key": current_app.config['API_KEY']}
            response = fetcher.requests.get(url,
                                            headers=headers,
                                            params=params)
            response.raise_for_status()
            data = response.json()

            if not data["results"]:
                logger.warning(f"Aucune donnée trouvée pour {city_name}")
                return render_template(
                    "index.html",
                    form=form,
                    error=f"Aucune donnée trouvée pour la ville {city_name}.")

            location_data = data["results"][0]
            map_html = create_map(location_data)

            return render_template("map.html",
                                   map_html=map_html,
                                   city=city_name)

        except Exception as e:
            logger.error(
                f"Erreur lors de la récupération des données: {str(e)}")
            return render_template(
                "index.html",
                form=form,
                error=f"Erreur lors de la récupération des données : {e}")

    return render_template("index.html", form=form)


def create_map(location_data):
    """
    Crée une carte avec les données de localisation et les capteurs.

    Args:
        location_data (dict): Données de localisation de l'API

    Returns:
        str: HTML de la carte Folium
    """
    latitude = location_data["coordinates"]["latitude"]
    longitude = location_data["coordinates"]["longitude"]
    station_name = location_data["name"]
    sensors = location_data["sensors"]

    # Créer la carte centrée sur la localisation
    pollution_map = folium.Map(location=[latitude, longitude], zoom_start=12)

    # Ajouter un marqueur pour la station
    popup_content = f"""
        <b>Station :</b> {station_name}<br>
        <b>Latitude :</b> {latitude}<br>
        <b>Longitude :</b> {longitude}<br>
    """

    for sensor in sensors:
        popup_content += f"- {sensor['parameter']['displayName']}: {sensor['parameter']['units']}<br>"

    folium.Marker(
        [latitude, longitude],
        popup=folium.Popup(popup_content, max_width=300),
        tooltip="Station de pollution",
    ).add_to(pollution_map)

    return pollution_map._repr_html_()
