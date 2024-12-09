"""Service pour la gestion des stations OpenAQ."""
import requests
import logging
from typing import List, Dict, Any

logger = logging.getLogger('openaq')


class StationsService:
    """Service pour gérer les stations de mesure."""

    def __init__(self, api_key: str):
        """
        Initialise le service.

        Args:
            api_key: Clé API OpenAQ
        """
        self.api_key = api_key
        self.base_url = "https://api.openaq.org/v3"

    def get_stations_by_country(self, country: str) -> List[Dict[str, Any]]:
        """
        Récupère toutes les stations d'un pays.

        Args:
            country: Code pays (ex: FR)

        Returns:
            Liste des stations
        """
        url = f"{self.base_url}/locations"
        headers = {"X-API-Key": self.api_key}
        params = {
            "country": country,
            "limit": 1000,
            "page": 1,
            "offset": 0,
            "sort": "desc",
            "order_by": "city"
        }

        try:
            response = requests.get(url, headers=headers, params=params)
            response.raise_for_status()
            data = response.json()

            if not data.get("results"):
                return []

            # Organiser les stations par ville
            stations_by_city = {}
            for station in data["results"]:
                city = station.get("city", "Unknown")
                if city not in stations_by_city:
                    stations_by_city[city] = []
                stations_by_city[city].append({
                    "id":
                    station["id"],
                    "name":
                    station["name"],
                    "city":
                    city,
                    "coordinates":
                    station["coordinates"]
                })

            return stations_by_city

        except Exception as e:
            logger.error(
                f"Erreur lors de la récupération des stations: {str(e)}")
            raise

    def get_stations_by_city(self, country: str,
                             city: str) -> List[Dict[str, Any]]:
        """
        Récupère les stations d'une ville.

        Args:
            country: Code pays (ex: FR)
            city: Nom de la ville

        Returns:
            Liste des stations
        """
        url = f"{self.base_url}/locations"
        headers = {"X-API-Key": self.api_key}
        params = {
            "country": country,
            "city": city,
            "limit": 100,
            "page": 1,
            "offset": 0,
            "sort": "desc",
            "order_by": "name"
        }

        try:
            response = requests.get(url, headers=headers, params=params)
            response.raise_for_status()
            data = response.json()

            if not data.get("results"):
                return []

            return [{
                "id": station["id"],
                "name": station["name"],
                "coordinates": station["coordinates"]
            } for station in data["results"]]

        except Exception as e:
            logger.error(
                f"Erreur lors de la récupération des stations de {city}: {str(e)}"
            )
            raise
