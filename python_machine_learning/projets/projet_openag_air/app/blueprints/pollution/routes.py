"""Routes pour le blueprint pollution."""
from flask import render_template, current_app, request
import folium
import logging
from . import bp
from ...forms import CitySearchForm
from ...services.cache_service import CacheService

logger = logging.getLogger('openaq')


@bp.route("/", methods=["GET"])
def index():
    """Page principale avec formulaire de recherche."""
    form = CitySearchForm()
    city_name = request.args.get('city_name', '').strip()

    if city_name:
        logger.info(f"Recherche pour la ville: {city_name}")
        try:
            # Utiliser le service de cache
            service = CacheService(api_key=current_app.config['API_KEY'])
            data = service.load_cache('FR')  # On commence avec la France

            # Rechercher la ville dans les données en cache
            city_data = data.get('cities', {}).get(city_name.title())
            if not city_data:
                logger.warning(f"Aucune donnée trouvée pour {city_name}")
                return render_template(
                    "pollution/index.html",
                    form=form,
                    error=f"Aucune donnée trouvée pour la ville {city_name}")

            # Afficher la liste des stations pour cette ville
            return render_template("pollution/locations.html",
                                   locations=city_data,
                                   city=city_name)

        except Exception as e:
            logger.error(f"Erreur lors de la recherche: {str(e)}")
            return render_template("pollution/index.html",
                                   form=form,
                                   error=str(e))

    return render_template("pollution/index.html", form=form)


@bp.route("/station/<int:station_id>")
def show_station(station_id):
    """Affiche les détails d'une station spécifique."""
    try:
        service = CacheService(api_key=current_app.config['API_KEY'])
        data = service.load_cache('FR')

        # Rechercher la station dans les données en cache
        station = None
        for s in data.get('stations', []):
            if s['id'] == station_id:
                station = s
                break

        if not station:
            raise ValueError(f"Station {station_id} non trouvée")

        # Créer la carte
        map_html = create_map(station)

        return render_template("pollution/map.html",
                               map_html=map_html,
                               city=station['city'])

    except Exception as e:
        logger.error(f"Erreur lors de l'affichage de la station: {str(e)}")
        return render_template("pollution/index.html",
                               form=CitySearchForm(),
                               error=str(e))


def create_map(station_data):
    """
    Crée une carte avec les données de localisation et les capteurs.

    Args:
        station_data (dict): Données de la station

    Returns:
        str: HTML de la carte Folium
    """
    latitude = station_data["coordinates"]["latitude"]
    longitude = station_data["coordinates"]["longitude"]
    station_name = station_data["name"]

    # Créer la carte centrée sur la localisation
    pollution_map = folium.Map(location=[latitude, longitude], zoom_start=12)

    # Ajouter un marqueur pour la station
    popup_content = f"""
        <b>Station :</b> {station_name}<br>
        <b>Latitude :</b> {latitude}<br>
        <b>Longitude :</b> {longitude}<br>
        <b>Mesures :</b><br>
    """

    for sensor in station_data.get('sensors', []):
        popup_content += f"- {sensor['parameter']}: {sensor['value']} {sensor['unit']}<br>"

    folium.Marker(
        [latitude, longitude],
        popup=folium.Popup(popup_content, max_width=300),
        tooltip="Station de pollution",
    ).add_to(pollution_map)

    return pollution_map._repr_html_()
