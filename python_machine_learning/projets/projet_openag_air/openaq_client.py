import os
import sys
import logging
import requests
from dotenv import load_dotenv
from typing import Protocol, Dict, Any

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


def main():
    r"""!
    \brief Fonction principale de récupération et d'affichage des données.
    \details Charge la clé API, récupère les données pour un ID de localisation donné et les affiche.
    """
    load_dotenv()
    api_key = os.getenv("api_key")

    if not api_key:
        logger.error("La clé API n'a pas été trouvée dans le fichier .env.")
        return

    fetcher = OpenAQLocationFetcher(api_key=api_key)
    location_id = 2162726

    try:
        data = fetcher.fetch_location_data(location_id)
        logger.info("Récupération des données réussie.")
        logger.debug(f"Données finales : {data}")

        print("Résultats pour la localisation :")
        print(data)

    except ValueError as e:
        logger.error(f"Échec de la récupération des données : {e}")


if __name__ == "__main__":
    main()
