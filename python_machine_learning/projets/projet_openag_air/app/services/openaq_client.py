"""Service client pour l'API OpenAQ."""
import requests
import logging
from typing import Dict, Any
from ..models import Location, Sensor

# Configuration du logger
logger = logging.getLogger('openaq')


class OpenAQLocationFetcher:
    """Client pour l'API OpenAQ."""

    def __init__(self, api_key: str):
        """
        Initialise le client OpenAQ.

        Args:
            api_key: Clé API OpenAQ
        """
        self.api_key = api_key
        self.base_url = "https://api.openaq.org/v3/locations"
        self.requests = requests

    def fetch_location_data(self, location_id: int) -> Dict[str, Any]:
        """
        Récupère les données pour une localisation.

        Args:
            location_id: ID de la localisation

        Returns:
            Dict contenant les données de la localisation

        Raises:
            ValueError: Si aucune donnée n'est trouvée
        """
        headers = {"X-API-Key": self.api_key}
        response = self.requests.get(f"{self.base_url}/{location_id}",
                                     headers=headers)
        response.raise_for_status()

        data = response.json()
        if not data["results"]:
            raise ValueError(f"Aucune donnée trouvée pour l'ID {location_id}")

        return data["results"][0]

    def search_by_city(self,
                       city_name: str,
                       country: str = "FR") -> Dict[str, Any]:
        """
        Recherche les données de pollution pour une ville.

        Args:
            city_name: Nom de la ville à rechercher
            country: Code pays ISO (FR par défaut pour la France)

        Returns:
            Dict contenant les données de la ville

        Raises:
            ValueError: Si aucune donnée n'est trouvée
        """
        # Utiliser la méthode search_locations qui gère déjà les IDs par ville
        try:
            results = self.search_locations(city_name=city_name)
            return results[0] if results else None

        except Exception as e:
            logger.error(f"Erreur lors de la recherche de la ville: {str(e)}")
            raise ValueError(
                f"Erreur lors de la recherche de la ville: {str(e)}")

    def search_locations(self,
                         city_name: str = None,
                         country: str = "FR") -> Dict[str, Any]:
        """
        Recherche les stations de mesure.

        Args:
            city_name: Nom de la ville (optionnel)
            country: Code pays ISO (FR par défaut)

        Returns:
            Dict contenant les stations trouvées

        Raises:
            ValueError: Si aucune donnée n'est trouvée
        """
        headers = {"X-API-Key": self.api_key}

        try:
            # Rechercher d'abord les stations disponibles pour le pays/ville
            url = "https://api.openaq.org/v3/locations"
            params = {
                "country": country,
                "limit": 100,
                "page": 1,
                "offset": 0,
                "sort": "desc",
                "radius": 1000,
                "order_by": "lastUpdated",
                "dumpRaw": False
            }

            if city_name:
                params["city"] = city_name

            response = self.requests.get(url, headers=headers, params=params)
            response.raise_for_status()

            data = response.json()
            if not data.get("results"):
                raise ValueError(
                    f"Aucune station trouvée pour {city_name or country}")

            stations = data["results"]

            # Enrichir chaque station avec ses mesures récentes
            results = []
            for station in stations:
                try:
                    # Récupérer les dernières mesures
                    measurements_url = f"{url}/{station['id']}/measurements"
                    measurement_params = {
                        "limit": 100,
                        "page": 1,
                        "offset": 0,
                        "sort": "desc",
                        "radius": 1000,
                        "order_by": "lastUpdated",
                        "dumpRaw": False
                    }

                    measurements_response = self.requests.get(
                        measurements_url,
                        headers=headers,
                        params=measurement_params)
                    measurements_response.raise_for_status()
                    measurements_data = measurements_response.json()

                    # Organiser les mesures par paramètre
                    latest_measurements = {}
                    for measurement in measurements_data.get("results", []):
                        parameter = measurement["parameter"]
                        if parameter not in latest_measurements:
                            latest_measurements[parameter] = {
                                "value": measurement["value"],
                                "unit": measurement["unit"],
                                "lastUpdated": measurement["date"]["local"]
                            }

                    # Ajouter les mesures à la station
                    station["measurements"] = [{
                        "parameter": param,
                        **measurement_data
                    } for param, measurement_data in
                                               latest_measurements.items()]
                    results.append(station)

                except Exception as e:
                    logger.warning(
                        f"Erreur lors de la récupération des mesures pour la station {station['id']}: {str(e)}"
                    )
                    continue

            # Trier les résultats par date de dernière mise à jour
            results.sort(key=lambda x: x.get("lastUpdated", ""), reverse=True)

            return results

        except Exception as e:
            logger.error(f"Erreur lors de la recherche des stations: {str(e)}")
            raise ValueError(
                f"Erreur lors de la recherche des stations: {str(e)}")

    def get_latest_measurements(self, location_id: str) -> list:
        """
        Récupère les dernières mesures pour une station.

        Args:
            location_id: ID de la station

        Returns:
            Liste des dernières mesures
        """
        headers = {"X-API-Key": self.api_key}
        url = f"{self.base_url}/{location_id}/measurements"

        try:
            response = self.requests.get(url, headers=headers)
            response.raise_for_status()

            data = response.json()
            if not data.get("results"):
                return []

            return data["results"]
        except Exception as e:
            logger.warning(
                f"Erreur lors de la récupération des mesures: {str(e)}")
            return []

    def get_location_by_id(self, location_id: int) -> Dict[str, Any]:
        """
        Récupère les données d'une station par son ID.

        Args:
            location_id: ID de la station OpenAQ

        Returns:
            Dict contenant les données de la station

        Raises:
            ValueError: Si la station n'est pas trouvée
        """
        headers = {"X-API-Key": self.api_key}
        url = f"{self.base_url}/{location_id}"

        response = self.requests.get(url, headers=headers)
        response.raise_for_status()

        data = response.json()
        if not data["results"]:
            raise ValueError(f"Station {location_id} non trouvée")

        return data["results"][0]
