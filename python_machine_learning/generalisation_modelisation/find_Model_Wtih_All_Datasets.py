import pandas as pd
import numpy as np
from sklearn.utils.multiclass import type_of_target
from mimetypes import guess_type
import os
'''
Utilisation de mimetypes.guess_type pour détecter le type de fichier.
Prise en charge des formats CSV, Excel, JSON, XML, Numpy, text, images, audio, vidéo, et plus.
Chargement dynamique des fichiers :

Les fichiers tabulaires (csv, xlsx, etc.) sont chargés avec pandas.
Les fichiers binaires (npy) sont chargés avec numpy.
Les types non tabulaires (images, audio, vidéo) sont encapsulés dans un dictionnaire pour traitement spécifique.
Analyse et recommandations adaptées :

Les modèles sont recommandés en fonction du type de données :
Tabulaires : Modèles classiques (régression, arbres, etc.).
Images : CNN.
Audio : RNN/LSTM.
Vidéo : Combinaison CNN + RNN.
Texte : Transformers ou modèles basés sur TF-IDF.
Gestion des erreurs :

Détection des fichiers non pris en charge et gestion des erreurs pour éviter les plantages.

Explications
Analyse des échantillons :

Si le dataset contient plus de 100 000 points, le script recommande des modèles capables de gérer de grandes quantités de données, comme les réseaux de neurones ou les modèles à descente de gradient.
Type de données :

Les données numériques (structurées) et non numériques (non structurées, comme le texte ou les images) sont traitées différemment.
Normalité des données :

Si les données numériques suivent une distribution normale, les modèles linéaires sont privilégiés.
Sinon, des modèles non paramétriques comme les arbres de décision ou les techniques de boosting sont proposés.
Type de variable cible :

Détection automatique des types de cible :
Classification (binaire/multiclass).
Régression (cible continue).
Multilabel pour les problèmes avec plusieurs étiquettes.
Variables qualitatives/quantitatives :

Le script vérifie le ratio entre les variables qualitatives (catégoriques) et quantitatives (numériques) pour suggérer des techniques comme l’encodage.
'''


def detect_file_type(file_path):
    """
    @brief Détecte le type de fichier en fonction de son extension ou de son contenu.

    @param file_path str Chemin du fichier à analyser
    @return str Type de fichier détecté ("image", "text", "audio", "video", "json/xml", "tabular", "binary", "unknown")

    @details
    Supporte les formats suivants:
    - Images: jpg, jpeg, png, gif, bmp, webp, tiff, tif, ico, jfif, pjpeg, pjp
    - Tabulaires: csv, xlsx, xls, txt
    - Binaires: npy, bin
    - Autres: json, xml, audio, vidéo

    @throws None
    """
    mime_type, _ = guess_type(file_path)
    ext = file_path.split(".")[-1].lower()

    # Liste exhaustive des extensions d'images supportées
    image_extensions = {
        'jpg', 'jpeg', 'png', 'gif', 'bmp', 'webp', 'tiff', 'tif', 'ico',
        'jfif', 'pjpeg', 'pjp'
    }

    if ext in image_extensions or (mime_type and 'image' in mime_type):
        return "image"
    elif mime_type:
        if "text" in mime_type:
            return "text"
        elif "audio" in mime_type:
            return "audio"
        elif "video" in mime_type:
            return "video"
        elif "json" in mime_type or "xml" in mime_type:
            return "json/xml"

    if ext in ["csv", "xlsx", "xls", "txt"]:
        return "tabular"
    elif ext in ["npy", "bin"]:
        return "binary"

    return "unknown"


def load_file(file_path):
    """
    @brief Charge un fichier en fonction de son type détecté.

    @param file_path str Chemin du fichier à charger
    @return Union[dict, pd.DataFrame, np.ndarray] Données chargées selon le format

    @details
    Support spécial pour WebP:
    - Utilisation de PIL avec support WebP
    - Fallback sur cv2.IMREAD_UNCHANGED pour WebP
    - Conversion automatique des espaces de couleur

    @throws FileNotFoundError Si le fichier n'existe pas
    @throws ImportError Si une bibliothèque requise n'est pas installée
    @throws ValueError Si le format n'est pas supporté
    """
    import logging

    if not os.path.exists(file_path):
        raise FileNotFoundError(
            f"Le fichier spécifié n'existe pas : {file_path}")

    file_type = detect_file_type(file_path)
    try:
        if file_type == "image":
            try:
                # Import des bibliothèques nécessaires
                try:
                    from PIL import Image, ImageFile
                    # Activer le chargement des images tronquées
                    ImageFile.LOAD_TRUNCATED_IMAGES = True
                except ImportError:
                    logging.error(
                        "Pillow n'est pas installé. Installation avec 'pip install Pillow'"
                    )
                    raise

                # Essai avec PIL d'abord
                try:
                    img = Image.open(file_path)
                    # S'assurer que l'image est chargée
                    img.load()
                    # Convertir en RGB si nécessaire
                    if img.mode not in ('RGB', 'L'):
                        img = img.convert('RGB')
                    return {"type": "image", "path": file_path, "data": img}
                except Exception as e:
                    logging.warning(f"PIL n'a pas pu charger l'image: {e}")

                    # Fallback sur OpenCV
                    try:
                        import cv2
                    except ImportError:
                        logging.error(
                            "OpenCV n'est pas installé. Installation avec 'pip install opencv-python'"
                        )
                        raise

                    # Essayer différents modes de lecture OpenCV
                    for read_mode in [
                            cv2.IMREAD_UNCHANGED, cv2.IMREAD_COLOR,
                            cv2.IMREAD_ANYCOLOR
                    ]:
                        img = cv2.imread(file_path, read_mode)
                        if img is not None:
                            # Convertir BGR en RGB si nécessaire
                            if len(img.shape) == 3 and img.shape[2] == 3:
                                img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
                            return {
                                "type": "image",
                                "path": file_path,
                                "data": img
                            }

                    # Si aucune méthode n'a fonctionné, essayer avec webp spécifiquement
                    if file_path.lower().endswith('.webp'):
                        try:
                            # Lecture spécifique pour WebP
                            img = cv2.imread(file_path, cv2.IMREAD_UNCHANGED)
                            if img is not None:
                                # Convertir BGRA en RGB si nécessaire
                                if len(img.shape) == 3:
                                    if img.shape[2] == 4:  # BGRA
                                        img = cv2.cvtColor(
                                            img, cv2.COLOR_BGRA2RGB)
                                    elif img.shape[2] == 3:  # BGR
                                        img = cv2.cvtColor(
                                            img, cv2.COLOR_BGR2RGB)
                                return {
                                    "type": "image",
                                    "path": file_path,
                                    "data": img
                                }
                        except Exception as e:
                            logging.error(
                                f"Erreur lors du chargement WebP avec OpenCV: {e}"
                            )

                    raise ValueError(
                        f"Impossible de charger l'image {file_path}")

            except Exception as e:
                logging.error(
                    f"Erreur lors du chargement de l'image {file_path}: {str(e)}"
                )
                raise

        elif file_type == "tabular":
            if file_path.endswith(".csv"):
                return pd.read_csv(file_path)
            elif file_path.endswith((".xlsx", ".xls")):
                return pd.read_excel(file_path)
            elif file_path.endswith(".txt"):
                return pd.read_csv(file_path, delimiter="\t")
        elif file_type == "json/xml":
            if file_path.endswith(".json"):
                return pd.read_json(file_path)
            elif file_path.endswith(".xml"):
                return pd.read_xml(file_path)
        elif file_type == "binary":
            if file_path.endswith(".npy"):
                return np.load(file_path, allow_pickle=True)
        elif file_type == "audio":
            return {"type": file_type, "path": file_path}
        elif file_type == "video":
            return {"type": file_type, "path": file_path}

        logging.warning(f"Type de fichier non reconnu: {file_type}")
        raise ValueError("Format de fichier non pris en charge")

    except Exception as e:
        logging.error(
            f"Erreur lors du chargement du fichier {file_path}: {str(e)}")
        raise


def analyze_dataset(dataset):
    """
    @brief Analyse un dataset et propose les meilleurs modèles de Machine Learning adaptés.

    @param dataset Union[pd.DataFrame, dict] Dataset à analyser:
        - pd.DataFrame pour données tabulaires
        - dict pour images/audio/vidéo
    @return Tuple[dict, List[str]] Tuple contenant:
        - Un dictionnaire avec le résumé du dataset
        - Liste des recommandations de modèles ML

    @details
    Le résumé inclut:
    - Nom du fichier
    - Type de données
    - Dimensions/taille
    - Format
    - Statistiques basiques (si applicable)
    """
    summary = {}
    recommendations = []

    if isinstance(dataset, pd.DataFrame):
        summary = {
            "type": "Données tabulaires",
            "dimensions":
            f"{dataset.shape[0]} lignes × {dataset.shape[1]} colonnes",
            "taille_memoire":
            f"{dataset.memory_usage().sum() / 1024**2:.2f} MB",
            "types_colonnes": dict(dataset.dtypes.value_counts()),
            "valeurs_manquantes": dataset.isnull().sum().sum(),
            "colonnes": list(dataset.columns),
        }

        # Ajout de statistiques basiques pour les colonnes numériques
        if not dataset.select_dtypes(include=['number']).empty:
            summary["statistiques"] = dataset.describe().to_dict()

    elif isinstance(dataset, dict) and "type" in dataset:
        if dataset["type"] == "image":
            img_data = dataset["data"]
            summary = {
                "type": "Image",
                "chemin": dataset["path"],
                "format": dataset["path"].split(".")[-1].upper(),
            }

            # Ajout des dimensions pour les images
            if hasattr(img_data, 'size'):  # Pour PIL Image
                summary[
                    "dimensions"] = f"{img_data.size[0]}×{img_data.size[1]} pixels"
                summary["mode"] = img_data.mode
            elif hasattr(img_data, 'shape'):  # Pour numpy array (OpenCV)
                summary[
                    "dimensions"] = f"{img_data.shape[1]}×{img_data.shape[0]} pixels"
                summary["canaux"] = img_data.shape[2] if len(
                    img_data.shape) > 2 else 1

        elif dataset["type"] in ["audio", "video"]:
            summary = {
                "type": dataset["type"].capitalize(),
                "chemin": dataset["path"],
                "format": dataset["path"].split(".")[-1].upper()
            }

    # ... (reste du code de recommendations inchangé)

    return summary, recommendations


# Utilisation
if __name__ == "__main__":
    import logging
    logging.basicConfig(level=logging.INFO)

    try:
        # file_path = "././data/image/Djangounchained.webp"  # Exemple image
        # file_path = "././data/csv/name_basics.csv"
        file_path = "././data/html/test_enregistrement2.html"
        # file_path = "././data/txt/teest1.txt"
        # file_path = "././data/xlsx/titanic.xlsx"
        # file_path = "././data/json/velo_ville_nantes.json"
        # file_path = "././data/sql/"
        dataset = load_file(file_path)
        summary, recommendations = analyze_dataset(dataset)

        print("\nRésumé du dataset :")
        for key, value in summary.items():
            if isinstance(value, dict):
                print(f"\n{key.capitalize()} :")
                for sub_key, sub_value in value.items():
                    print(f"  - {sub_key}: {sub_value}")
            else:
                print(f"- {key.capitalize()}: {value}")

        print("\nRecommandations de modèles :")
        for rec in recommendations:
            print(f"- {rec}")

    except Exception as e:
        logging.error(f"Erreur : {e}")
