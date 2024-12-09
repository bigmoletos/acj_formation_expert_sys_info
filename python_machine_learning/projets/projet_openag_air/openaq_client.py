import os
import sys
import logging
import requests
from dotenv import load_dotenv
from typing import Protocol, Dict, Any
import json

# Reconfigurer la sortie standard en UTF-8
sys.stdout.reconfigure(encoding='utf-8')

# Configuration du logger
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

file_handler = logging.FileHandler("openaq.log", encoding="utf-8")
file_handler.setLevel(logging.DEBUG)
formatter = logging.Formatter("%(asctime)s [%(levelname)s] %(message)s")
file_handler.setFormatter(formatter)

stream_handler = logging.StreamHandler()
stream_handler.setFormatter(formatter)

logger.addHandler(file_handler)
logger.addHandler(stream_handler)


class ILocationFetcher(Protocol):
    r"""!
    \brief Interface pour la récupération de données de localisation.

    \details Toute classe implémentant ce protocole doit fournir une méthode `fetch_location_data`.

    \test
    Exemple de doctest :
    >>> class MockFetcher:
    ...     def fetch_location_data(self, location_id: int) -> Dict[str, Any]:
    ...         return {"meta": {"found": 1}, "results": [{"id": location_id}]}
    >>> fetcher = MockFetcher()
    >>> result = fetcher.fetch_location_data(1234)
    >>> result["results"][0]["id"] == 1234
    True
    """

    def fetch_location_data(self, location_id: int) -> Dict[str, Any]:
        r"""!
        \brief Récupère les données pour un ID donné.
        \param location_id ID de la localisation.
        \return Les données de la localisation au format dict.
        \exception ValueError Si aucune donnée n'est disponible.
        """
        ...


class OpenAQLocationFetcher:
    r"""!
    \brief Classe concrète pour récupérer des données de localisation via l'API OpenAQ.

    \details Cette classe utilise l'API OpenAQ et nécessite une clé API définie dans un fichier .env.

    \param api_key Clé API OpenAQ
    \exception ValueError Si la clé API est manquante

    \test
    Le test d'initialisation sans clé API est effectué dans test_openaq_client.py
    """

    def __init__(self, api_key: str):
        if not api_key:
            logger.error(
                "Clé API manquante lors de l'initialisation du fetcher.")
            raise ValueError("La clé API est requise.")
        self.api_key = api_key
        self.base_url = "https://api.openaq.org/v3/locations"

    def fetch_location_data(self, location_id: int) -> Dict[str, Any]:
        r"""!
        \brief Récupère les données JSON de l'API OpenAQ pour un ID de localisation donné.

        \param location_id ID de la localisation
        \return Un dictionnaire contenant les données de la localisation
        \exception ValueError Si aucune donnée n'est trouvée ou en cas d'erreur HTTP

        \test
        Exemple (indication, à tester via mocking) :
        >>> # Ce doctest est indicatif. Pour un test effectif, voir les tests unitaires.
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

            logger.debug(f"Données reçues : {data}")
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


def format_location_data(data: Dict[str, Any]) -> str:
    r"""!
    \brief Formate les données de localisation pour l'affichage

    \details Cette fonction prend les données brutes de l'API et les formate
    dans un format lisible et structuré, incluant les informations de la station
    et les détails des capteurs.

    \param data Dictionnaire contenant les données brutes de l'API
    \return str Chaîne formatée contenant les données structurées
    \exception KeyError Si la structure des données est invalide

    \test
    >>> data = {
    ...     "results": [{
    ...         "id": 1,
    ...         "name": "Test Station",
    ...         "locality": "Test City",
    ...         "coordinates": {"latitude": 0.0, "longitude": 0.0},
    ...         "sensors": [{"id": 1, "parameter": {"displayName": "CO mass", "units": "µg/m³"}}]
    ...     }]
    ... }
    >>> result = format_location_data(data)
    >>> "Test Station" in result
    True
    """
    logger.debug("Début du formatage des données de localisation")

    try:
        if not data.get('results') or not data['results'][0]:
            logger.warning("Données de localisation vides ou invalides")
            return "Aucune donnée disponible"

        location = data['results'][0]
        logger.debug(
            f"Traitement des données pour la station: {location.get('name', 'Inconnue')}"
        )

        # Formatage des données des capteurs
        sensors_data = []
        for sensor in location['sensors']:
            try:
                sensor_info = {
                    "nom": sensor['parameter']['displayName'].split()[0],
                    "unité": sensor['parameter']['units'],
                    "id_capteur": sensor['id']
                }
                sensors_data.append(sensor_info)
                logger.debug(f"Capteur traité: {sensor_info['nom']}")
            except KeyError as e:
                logger.warning(
                    f"Structure de données invalide pour le capteur: {e}")
                continue

        formatted_output = f"""
Station de mesure:
----------------
ID          : {location['id']}
Nom         : {location['name']}
Localité    : {location['locality']}

Coordonnées:
-----------
Latitude    : {location['coordinates']['latitude']}
Longitude   : {location['coordinates']['longitude']}

Capteurs:
--------
{json.dumps(sensors_data, indent=4, ensure_ascii=False)}
"""
        logger.info("Formatage des données réussi")
        return formatted_output

    except KeyError as e:
        error_msg = f"Erreur lors du formatage des données: {e}"
        logger.error(error_msg)
        raise KeyError(error_msg)
    except Exception as e:
        error_msg = f"Erreur inattendue lors du formatage: {e}"
        logger.error(error_msg)
        raise


def main():
    r"""!
    \brief Fonction principale de récupération et d'affichage des données.

    \details Cette fonction:
        - Charge la clé API depuis le fichier .env
        - Initialise le client OpenAQ
        - Récupère et affiche les données formatées pour une station spécifique

    \note La fonction utilise l'ID de station 2162726 (MARSEILLE 5 AVENUES)
    """
    logger.info("Démarrage du programme principal")
    load_dotenv()
    api_key = os.getenv("api_key")

    if not api_key:
        logger.error("La clé API n'a pas été trouvée dans le fichier .env.")
        return

    try:
        logger.debug("Initialisation du fetcher OpenAQ")
        fetcher = OpenAQLocationFetcher(api_key=api_key)
        location_id = 2162726
        logger.info(
            f"Récupération des données pour la station ID: {location_id}")

        data = fetcher.fetch_location_data(location_id)
        logger.info("Récupération des données réussie")

        formatted_data = format_location_data(data)
        logger.debug("Données formatées avec succès")
        print(formatted_data)

    except ValueError as e:
        logger.error(f"Échec de la récupération des données : {e}")
    except Exception as e:
        logger.error(f"Erreur inattendue : {e}")


if __name__ == "__main__":
    main()
