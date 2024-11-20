import requests
import os
import pandas as pd

def telecharger_et_charger_fichier(url, dossier_destination=None):
    """
    Télécharge un fichier depuis une URL donnée, le sauvegarde dans un dossier spécifié,
    Si le dossier n'existe pas il est crée
    Par defaut enregistre le fichier dans un repertoire ../datas qui est à la racine du projet
    et charge le fichier dans un DataFrame en fonction de son format.

    :param url: URL du fichier à télécharger.
    :param dossier_destination: Dossier de destination optionnel pour le fichier.
    :return: Tuple contenant le DataFrame original, sa copie, et le nom du fichier.
    """
    # Initialiser df_original et df à None
    df_original, df = None, None
    try:
        # Déterminer le nom du fichier à partir de l'URL
        nom_fichier = url.split('/')[-1]

        # Construire le chemin absolu du dossier de destination
        if dossier_destination is None:
            # Chemin par défaut relatif au script
            chemin_script = os.path.dirname(os.path.abspath(__file__))
            chemin_complet = os.path.join(chemin_script, "..", "datas", nom_fichier)
        else:
            # Utiliser le chemin de destination fourni
            chemin_complet = os.path.join(dossier_destination, nom_fichier)

        # Créer le dossier de destination s'il n'existe pas
        os.makedirs(os.path.dirname(chemin_complet), exist_ok=True)

        # Télécharger le fichier
        response = requests.get(url)
        response.raise_for_status()

        # Écrire le contenu dans le fichier de destination
        with open(chemin_complet, 'wb') as file:
            file.write(response.content)

        # Déterminer l'extension du fichier et charger dans un DataFrame
        extension = nom_fichier.split('.')[-1].lower()
        if extension in ['csv', 'txt']:
            df_original = pd.read_csv(chemin_complet, encoding='utf-8', header=0, index_col=0)
        elif extension == 'json':
            df_original = pd.read_json(chemin_complet, encoding='utf-8', orient='records')
        elif extension == 'xlsx':
            df_original = pd.read_excel(chemin_complet, index_col=0)
        else:
            print(f"Format de fichier non pris en charge : {extension}")

        # Faire une copie du DataFrame si celui-ci a été chargé
        if df_original is not None:
            df = df_original.copy()


        return df_original, df, chemin_complet

    except requests.HTTPError as http_err:
        print(f"Erreur HTTP lors du téléchargement du fichier : {http_err}")
        return None, None, None
    except Exception as err:
        print(f"Une erreur est survenue lors du téléchargement du fichier : {err}")
        return None, None, None



# test
url = "https://raw.githubusercontent.com/jbrownlee/Datasets/master/daily-min-temperatures.csv"

df_original, df, nom_fichier = telecharger_et_charger_fichier( url, "datas/csv")