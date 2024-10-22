from fastapi import FastAPI, HTTPException, Query
import json
from typing import Optional
import logging

# Configuration du logging
logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s - %(levelname)s - %(message)s')

# http://localhost:8004/marseille/meteo_quotidienne/?jour=10:12:2024
# http://localhost:8004/marseille/meteo_quotidienne/?jour=10:12:2024&heure=09:23
# http://localhost:8004/marseille/meteo_quotidienne/?date_debut=01:01:2024&date_fin=31:12:2024
#
app = FastAPI()

# fichierJson = 'meteo_marseille_10ans_1minute2.json'
fichierJson = '/app/data/meteo_marseille_10ans_1minute.json'
# fichierJson = r'DOCKER\images\python\meteo_marseille_10ans_1minute.json'

# Charger les données météo depuis le fichier JSON
try:
    logging.info(f"Chargement des données à partir du fichier {fichierJson}")
    with open(fichierJson, 'r') as f:
        meteo_data = json.load(f)
    logging.info("Données chargées avec succès.")
        # Ajoutez ce log pour voir les premières dates dans les données chargées
    logging.debug(f"Premières dates dans le fichier JSON : {[meteo['date'] for meteo in meteo_data[:5]]}")

except Exception as e:
    logging.error(f"Erreur lors du chargement des données : {e}")
    raise HTTPException(status_code=500,
                        detail="Erreur lors du chargement des données.")


# Fonction pour rechercher les données météo pour une date, une heure spécifiques ou une plage de jours
@app.get("/marseille/meteo_quotidienne/")
def get_meteo(jour: Optional[str] = Query(
    None, description="Date au format JJ:MM:AAAA"),
              heure: Optional[str] = None,
              date_debut: Optional[str] = None,
              date_fin: Optional[str] = None):
    """
    Rechercher des données météo à Marseille pour un jour et/ou une heure spécifiques,
    ou une plage de jours. Les résultats sont extraits à partir d'un fichier JSON.

    :param jour: La date spécifique au format JJ:MM:AAAA
    :param heure: (Optionnel) L'heure spécifique au format HH:MM
    :param date_debut: (Optionnel) La date de début de la plage au format JJ:MM:AAAA
    :param date_fin: (Optionnel) La date de fin de la plage au format JJ:MM:AAAA
    :return: Un dictionnaire contenant les résultats météo trouvés
    """
    logging.info(
        f"Requête reçue : jour={jour}, heure={heure}, date_debut={date_debut}, date_fin={date_fin}"
    )

    # Liste des résultats trouvés
    resultats = []

    # Convertir les formats de date
    def convertir_date(date_str):
        try:
            date_parts = date_str.split(":")
            date_format = f"{date_parts[2]}-{date_parts[1]}-{date_parts[0]}"  # Format AAAA-MM-JJ
            logging.debug(
                f"Conversion de la date {date_str} au format {date_format}")
            return date_format
        except Exception as e:
            logging.error(f"Erreur de conversion de la date : {e}")
            raise HTTPException(
                status_code=400,
                detail="Format de date invalide. Utilisez JJ:MM:AAAA")

    # Cas où une seule date est fournie
    if jour:
        logging.debug(f"Recherche des données pour le jour {jour}")
        jour_format = convertir_date(jour)
        for meteo in meteo_data:
            if meteo["date"] == jour_format:
                if heure:
                    logging.debug(
                        f"Recherche des données pour l'heure {heure}")
                    if meteo["heure"] == heure:
                        resultats.append(meteo)
                else:
                    resultats.append(meteo)

    # Cas d'une plage de dates
    elif date_debut and date_fin:
        logging.debug(
            f"Recherche des données entre {date_debut} et {date_fin}")
        date_debut_format = convertir_date(date_debut)
        date_fin_format = convertir_date(date_fin)

        for meteo in meteo_data:
            if date_debut_format <= meteo["date"] <= date_fin_format:
                resultats.append(meteo)

    # Vérification des résultats
    if not resultats:
        logging.warning(f"Aucune donnée trouvée pour les paramètres fournis.")
        raise HTTPException(
            status_code=404,
            detail="Aucune donnée trouvée pour ces paramètres.")

    logging.info(f"{len(resultats)} résultats trouvés pour la requête.")
    return {"resultats": resultats}
