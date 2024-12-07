import requests
from dotenv import load_dotenv
from urllib.parse import urlencode
import os
import logging

# Configurer le logger
logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[
        logging.FileHandler("app.log"),  # Sauvegarde des logs dans un fichier
        logging.StreamHandler()  # Affichage dans la console
    ])

# Charger les variables d'environnement
load_dotenv()

# Clé API et URL
api_host = "leboncoin1.p.rapidapi.com"
api_key = os.getenv(
    "API_KEY")  # Assurez-vous que "API_KEY" est bien défini dans .env

if not api_key:
    logging.error(
        "La clé API n'a pas été trouvée. Assurez-vous qu'elle est définie dans le fichier .env."
    )
    exit()

# Paramètres de recherche
params = {"category": 2, "text": "EVOQUE", "brand": "Land Rover", "gearbox": 2}

# Construire l'URL de recherche
encoded_query = urlencode(params, safe=":")
api_url = f"https://leboncoin1.p.rapidapi.com/v2/leboncoin/search?query=https://www.leboncoin.fr/recherche?{encoded_query}"

# En-têtes de la requête
headers = {
    "x-rapidapi-host": api_host,
    "x-rapidapi-key": api_key,
    "Content-Type": "application/json",
    "User-Agent": "Mozilla/5.0"
}

# Logs des informations de configuration
logging.debug(f"URL générée : {api_url}")
logging.debug(f"En-têtes : {headers}")

# Faire la requête GET
try:
    logging.info("Envoi de la requête à l'API...")
    response = requests.get(api_url, headers=headers)
    response.raise_for_status()  # Vérifie si la requête a réussi
    logging.info("Requête API réussie.")

    # Parse les données JSON
    data = response.json()
    logging.info("Données reçues :")
    logging.debug(data)

    print("Résultats de la recherche :")
    for result in data.get("results", []):
        print(result)
        logging.debug(result)

except requests.exceptions.HTTPError as http_err:
    logging.error(f"Erreur HTTP : {http_err}")
except requests.exceptions.RequestException as req_err:
    logging.error(f"Erreur lors de l'appel API : {req_err}")
except ValueError as json_err:
    logging.error(f"Erreur lors du parsing JSON : {json_err}")
