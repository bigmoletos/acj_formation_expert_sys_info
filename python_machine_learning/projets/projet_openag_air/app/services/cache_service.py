"""Service pour la gestion du cache des données OpenAQ."""
import json
import os
import requests
import logging
from datetime import datetime, timedelta
from typing import Dict, Any

logger = logging.getLogger('openaq')


class CacheService:
    """Service pour gérer le cache des données."""

    def __init__(self, api_key: str):
        """
        Initialise le service de cache.

        Args:
            api_key: Clé API OpenAQ
        """
        if not api_key:
            logger.error("Clé API manquante lors de l'initialisation.")
            raise ValueError("La clé API est requise.")

        self.api_key = api_key
        self.base_url = "https://api.openaq.org/v3/locations"
        self.cache_dir = "cache"
        self.ensure_cache_dir()

    def ensure_cache_dir(self):
        """Crée le dossier de cache s'il n'existe pas."""
        if not os.path.exists(self.cache_dir):
            os.makedirs(self.cache_dir)

    def get_cache_path(self, country: str) -> str:
        """
        Retourne le chemin du fichier de cache pour un pays.

        Args:
            country: Code pays (ex: FR)
        """
        return os.path.join(self.cache_dir, f"{country.lower()}_data.json")

    def load_cache(self, country: str) -> Dict[str, Any]:
        """
        Charge les données du cache.

        Args:
            country: Code pays (ex: FR)

        Returns:
            Dict contenant les données du cache
        """
        cache_path = self.get_cache_path(country)
        if os.path.exists(cache_path):
            try:
                with open(cache_path, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                    if data.get('timestamp'):
                        cache_time = datetime.fromisoformat(data['timestamp'])
                        if (datetime.now() - cache_time).days < 1:
                            return data
            except Exception as e:
                logger.error(f"Erreur lors de la lecture du cache: {str(e)}")

        return self.update_cache(country)

    def update_cache(self, country: str) -> Dict[str, Any]:
        """
        Met à jour le cache avec les données de l'API.

        Args:
            country: Code pays (ex: FR)

        Returns:
            Dict contenant les nouvelles données
        """
        try:
            # Liste des stations avec leurs informations complètes
            STATIONS = {
                "FR": [{
                    "id": 2162724,
                    "name": "MARSEILLE ST LOUIS",
                    "city": "Marseille",
                    "country": "France",
                    "type": "Station de fond urbain",
                    "address": "15 rue Saint-Louis, 13015 Marseille",
                    "parameters": ["NO mass", "NO2 mass", "PM10", "PM2.5"]
                }, {
                    "id": 2162725,
                    "name": "MARSEILLE RABATAU",
                    "city": "Marseille",
                    "country": "France",
                    "type": "Station trafic",
                    "address": "64 avenue du Prado, 13008 Marseille",
                    "parameters": ["NO mass", "NO2 mass", "PM10", "PM2.5"]
                }, {
                    "id": 2162726,
                    "name": "MARSEILLE 5 AVENUES",
                    "city": "Marseille",
                    "country": "France",
                    "type": "Station de fond urbain",
                    "address": "358 avenue du Maréchal Foch, 13004 Marseille",
                    "parameters": ["NO mass", "NO2 mass", "PM10", "PM2.5"]
                }]
            }

            stations_data = []
            for station in STATIONS.get(country, []):
                try:
                    data = self._fetch_location_data(station["id"])
                    if data and data.get("results"):
                        station_info = data["results"][0]
                        # Utiliser les informations locales et ajouter les données de l'API
                        formatted_data = {
                            "id": station_info["id"],
                            "name": station["name"],  # Nom local
                            "city": station["city"],  # Ville locale
                            "country": station["country"],  # Pays local
                            "type": station["type"],  # Type local
                            "address": station["address"],  # Adresse locale
                            "coordinates": station_info["coordinates"],
                            "parameters": station["parameters"],
                            "measurements":
                            station_info.get("measurements", [])
                        }
                        stations_data.append(formatted_data)
                except Exception as e:
                    logger.error(
                        f"Erreur pour la station {station['name']}: {str(e)}")
                    continue

            # Organiser par ville
            cities = {}
            for station in stations_data:
                city = station["city"]
                if city not in cities:
                    cities[city] = []
                cities[city].append(station)

            cache_data = {
                'timestamp': datetime.now().isoformat(),
                'country': country,
                'stations': stations_data,
                'cities': cities
            }

            # Sauvegarder dans le cache
            cache_path = self.get_cache_path(country)
            with open(cache_path, 'w', encoding='utf-8') as f:
                json.dump(cache_data, f, ensure_ascii=False, indent=2)

            return cache_data

        except Exception as e:
            logger.error(f"Erreur lors de la mise à jour du cache: {str(e)}")
            raise

    def _fetch_location_data(self, location_id: int) -> Dict[str, Any]:
        """
        Récupère les données d'une station spécifique.

        Args:
            location_id: ID de la station

        Returns:
            Dict contenant les données de la station
        """
        url = f"{self.base_url}/{location_id}"
        headers = {"X-API-Key": self.api_key}

        try:
            logger.debug(f"Requête GET à {url}")
            response = requests.get(url, headers=headers)
            response.raise_for_status()

            data = response.json()
            if not data:
                logger.error("Aucune donnée reçue de l'API.")
                raise ValueError("Données introuvables pour cet ID.")

            # Formater les données comme dans l'ancien client
            if data.get("results"):
                station = data["results"][0]
                formatted_data = {
                    "results": [{
                        "id": station["id"],
                        "name": station["name"],
                        "coordinates": station["coordinates"],
                        "sensors":
                        []  # Utiliser sensors au lieu de measurements
                    }]
                }

                # Créer les sensors par défaut
                default_sensors = [{
                    "id": 1,
                    "parameter": {
                        "displayName": "NO mass",
                        "units": "µg/m³"
                    },
                    "lastValue": None,
                    "lastUpdatedUTC": None
                }, {
                    "id": 2,
                    "parameter": {
                        "displayName": "NO2 mass",
                        "units": "µg/m³"
                    },
                    "lastValue": None,
                    "lastUpdatedUTC": None
                }, {
                    "id": 3,
                    "parameter": {
                        "displayName": "PM10",
                        "units": "µg/m³"
                    },
                    "lastValue": None,
                    "lastUpdatedUTC": None
                }, {
                    "id": 4,
                    "parameter": {
                        "displayName": "PM2.5",
                        "units": "µg/m³"
                    },
                    "lastValue": None,
                    "lastUpdatedUTC": None
                }]

                # Mettre à jour avec les valeurs réelles si disponibles
                for sensor in station.get("sensors", []):
                    param = sensor["parameter"]["displayName"]
                    for default_sensor in default_sensors:
                        if default_sensor["parameter"]["displayName"] == param:
                            default_sensor.update({
                                "lastValue":
                                sensor.get("lastValue"),
                                "lastUpdatedUTC":
                                sensor.get("lastUpdatedUTC")
                            })

                formatted_data["results"][0]["sensors"] = default_sensors
                return formatted_data

            return data

        except requests.exceptions.HTTPError as http_err:
            logger.error(f"Erreur HTTP : {http_err}")
            raise ValueError(
                f"Erreur HTTP lors de la récupération des données : {http_err}"
            )
        except requests.exceptions.RequestException as req_err:
            logger.error(f"Erreur de requête : {req_err}")
            raise ValueError(
                f"Erreur réseau lors de la récupération des données : {req_err}"
            )
        except ValueError as val_err:
            logger.error(f"Erreur de valeur : {val_err}")
            raise
