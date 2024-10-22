import json
from datetime import datetime, timedelta
import random
import logging

# Configurer le logger
logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s - %(levelname)s - %(message)s',
                    handlers=[
                        logging.FileHandler("meteo_generation.log"),
                        logging.StreamHandler()
                    ])

# Début du processus
logging.info("Début de la génération des données météo.")

try:
    # Générer des données météo pour 10 ans avec un pas de 1 minute entre chaque enregistrement
    start_date = datetime(2014, 7, 1)  # Commence le 1er juillet 2014
    days = 3650  # 10 ans
    interval_minutes = 1  # Intervalle de 1 minute
    total_minutes = days * 24 * 60  # Nombre total de minutes sur 10 ans

    current_datetime = start_date

    # Enregistrer les données directement dans le fichier sans tout charger en mémoire
    file_path = r'DOCKER\images\python\meteo_marseille_10ans_1minute2.json'

    logging.info(f"Le fichier sera enregistré à : {file_path}")

    with open(file_path, "w") as f:
        f.write("[\n")  # Commence le tableau JSON
        logging.debug(
            f"Début de l'écriture des données dans le fichier {file_path}")

        for minute in range(total_minutes):
            # Générer une entrée de données météo
            meteo_entry = {
                "date": current_datetime.strftime("%Y-%m-%d"),
                "heure": current_datetime.strftime("%H:%M"),
                "temperature":
                random.randint(18,
                               35),  # Température aléatoire entre 18 et 35°C
                "humidite":
                random.randint(50, 80),  # Humidité aléatoire entre 50% et 80%
                "vent_vitesse": random.randint(
                    0, 120)  # Vitesse du vent aléatoire entre 0 et 120 km/h
            }

            # Écrire chaque entrée dans le fichier
            json.dump(meteo_entry, f)

            # Ajouter une virgule sauf pour le dernier enregistrement
            if minute < total_minutes - 1:
                f.write(",\n")

            # Passer à la minute suivante
            current_datetime += timedelta(minutes=interval_minutes)

            # Logging debug chaque 1 million de minutes traitées
            if minute % 1000000 == 0:
                logging.debug(
                    f"Progression : {minute} minutes traitées sur {total_minutes}."
                )

        f.write("\n]")  # Terminer le tableau JSON

    logging.info("La génération des données météo s'est terminée avec succès.")
    logging.info(f"Fichier enregistré à l'emplacement : {file_path}")

except Exception as e:
    logging.error(f"Une erreur est survenue : {e}")
