import os
import json
import logging

# Configuration du logger
logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)


def check_kaggle_credentials():
    try:
        kaggle_json_path = os.path.expanduser("~/.kaggle/kaggle.json")
        logger.debug(
            f"Chemin d'accès au fichier kaggle.json : {kaggle_json_path}")

        if not os.path.exists(kaggle_json_path):
            logger.error("Le fichier kaggle.json n'existe pas.")
            return

        with open(kaggle_json_path, 'r') as file:
            credentials = json.load(file)
            logger.debug(f"Contenu du fichier kaggle.json : {credentials}")

            if 'username' not in credentials or 'key' not in credentials:
                logger.error("Le fichier kaggle.json est mal formé.")
                return

            logger.info(
                "Les informations d'identification Kaggle sont correctes.")
    except Exception as e:
        logger.exception(
            "Une erreur s'est produite lors de la vérification des informations d'identification Kaggle."
        )


check_kaggle_credentials()
