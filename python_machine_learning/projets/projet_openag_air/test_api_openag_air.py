import requests
from dotenv import load_dotenv
import os
import logging

# Configurer le logger
logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[
        logging.FileHandler(
            "openaq.log"),  # Sauvegarde des logs dans un fichier
        logging.StreamHandler()  # Affichage dans la console
    ])

# Charger les variables d'environnement
load_dotenv()

# Récupérer la clé API
api_key = os.getenv("api_key")

if not api_key:
    logging.error(
        "La clé API n'a pas été trouvée. Assurez-vous qu'elle est définie dans le fichier .env."
    )
    exit()

# URL de l'API pour le test
location_id = 2162726  #12/43.30532/5.39463
# ID de la localisation pour l'exemple
api_url = f"https://api.openaq.org/v3/locations/{location_id}"

# En-têtes de la requête
headers = {"X-API-Key": api_key}

# Requête GET
try:
    logging.info(
        f"Envoi de la requête à l'API OpenAQ pour l'ID de localisation {location_id}..."
    )
    response = requests.get(api_url, headers=headers)
    response.raise_for_status()  # Vérifie si la requête a réussi
    logging.info("Requête API réussie.")

    # Parse et afficher les données JSON
    data = response.json()
    logging.info("Données reçues :")
    logging.debug(data)

    print("Résultats pour la localisation :")
    print(data)
except requests.exceptions.HTTPError as http_err:
    logging.error(f"Erreur HTTP : {http_err}")
except requests.exceptions.RequestException as req_err:
    logging.error(f"Erreur lors de l'appel API : {req_err}")
except ValueError as json_err:
    logging.error(f"Erreur lors du parsing JSON : {json_err}")
