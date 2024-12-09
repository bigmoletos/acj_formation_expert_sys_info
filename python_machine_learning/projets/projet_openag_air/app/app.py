from flask import Flask, request, render_template, jsonify
from ..openaq_client import OpenAQLocationFetcher, format_location_data
from dotenv import load_dotenv
import os
import folium

# Charger la clé API depuis le fichier .env
load_dotenv()
api_key = os.getenv("api_key")

if not api_key:
    raise ValueError(
        "La clé API OpenAQ n'est pas définie dans le fichier .env.")

# Initialiser Flask
app = Flask(__name__)

# Initialiser le fetcher OpenAQ
fetcher = OpenAQLocationFetcher(api_key=api_key)


@app.route("/", methods=["GET", "POST"])
def index():
    """Page principale avec formulaire de recherche."""
    if request.method == "POST":
        city_name = request.form.get("city_name", "").strip()
        if not city_name:
            return render_template("index.html",
                                   error="Veuillez entrer le nom d'une ville.")

        try:
            # Rechercher les données par ville
            url = f"https://api.openaq.org/v3/locations"
            params = {"city": city_name, "limit": 1}
            headers = {"X-API-Key": api_key}
            response = fetcher.requests.get(url,
                                            headers=headers,
                                            params=params)
            response.raise_for_status()
            data = response.json()

            if not data["results"]:
                return render_template(
                    "index.html",
                    error=f"Aucune donnée trouvée pour la ville {city_name}.")

            location_data = data["results"][0]
            map_html = create_map(location_data)

            return render_template("map.html",
                                   map_html=map_html,
                                   city=city_name)

        except Exception as e:
            return render_template(
                "index.html",
                error=f"Erreur lors de la récupération des données : {e}")
    return render_template("index.html")


def create_map(location_data):
    """Crée une carte avec les données de localisation et les capteurs."""
    latitude = location_data["coordinates"]["latitude"]
    longitude = location_data["coordinates"]["longitude"]
    station_name = location_data["name"]
    sensors = location_data["sensors"]

    # Créer la carte centrée sur la localisation
    pollution_map = folium.Map(location=[latitude, longitude], zoom_start=12)

    # Ajouter un marqueur pour la station
    popup_content = f"<b>Station :</b> {station_name}<br><b>Latitude :</b> {latitude}<br><b>Longitude :</b> {longitude}<br>"
    for sensor in sensors:
        popup_content += f"- {sensor['parameter']['displayName']}: {sensor['parameter']['units']}<br>"

    folium.Marker(
        [latitude, longitude],
        popup=folium.Popup(popup_content, max_width=300),
        tooltip="Station de pollution",
    ).add_to(pollution_map)

    # Convertir la carte en HTML
    return pollution_map._repr_html_()


if __name__ == "__main__":
    app.run(debug=True)
