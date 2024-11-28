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
    Support pour fichiers:
    - Excel (.xlsx, .xls) via pandas
    - CSV avec différents délimiteurs
    - Texte avec détection d'encodage
    - Images (PIL/OpenCV)
    - JSON/XML via pandas

    @throws FileNotFoundError Si le fichier n'existe pas
    @throws ImportError Si une bibliothèque requise n'est pas installée
    @throws ValueError Si le format n'est pas supporté
    """
    import logging
    import chardet

    if not os.path.exists(file_path):
        raise FileNotFoundError(
            f"Le fichier spécifié n'existe pas : {file_path}")

    file_type = detect_file_type(file_path)
    try:
        # Gestion des fichiers texte
        if file_type == "text" or file_path.endswith('.txt'):
            try:
                # Détection de l'encodage
                with open(file_path, 'rb') as f:
                    raw_data = f.read()
                    result = chardet.detect(raw_data)
                    encoding = result['encoding']

                # Essayer d'abord comme CSV
                delimiters = [',', ';', '\t', '|']
                for delimiter in delimiters:
                    try:
                        df = pd.read_csv(file_path,
                                         delimiter=delimiter,
                                         encoding=encoding)
                        if len(df.columns) > 1:  # Si c'est un CSV valide
                            logging.info(
                                f"Fichier chargé comme CSV avec délimiteur: {delimiter}"
                            )
                            return df
                    except Exception:
                        continue

                # Si ce n'est pas un CSV, lire comme texte simple
                with open(file_path, 'r', encoding=encoding) as f:
                    content = f.read()
                    return {
                        "type": "text",
                        "path": file_path,
                        "data": content,
                        "format": "txt",
                        "encoding": encoding
                    }

            except Exception as e:
                logging.error(
                    f"Erreur lors de la lecture du fichier texte: {str(e)}")
                raise

        # Gestion des fichiers CSV (pour les .csv explicites)
        elif file_path.endswith('.csv'):
            try:
                # Détection de l'encodage
                with open(file_path, 'rb') as f:
                    raw_data = f.read()
                    result = chardet.detect(raw_data)
                    encoding = result['encoding']

                # Essayer différents délimiteurs
                delimiters = [',', ';', '\t', '|']
                for delimiter in delimiters:
                    try:
                        df = pd.read_csv(file_path,
                                         delimiter=delimiter,
                                         encoding=encoding)
                        if len(df.columns
                               ) > 1:  # Vérification basique de la structure
                            logging.info(
                                f"CSV chargé avec succès (délimiteur: {delimiter}, encodage: {encoding})"
                            )
                            return df
                    except Exception:
                        continue

                # Si aucun délimiteur n'a fonctionné, essayer avec le délimiteur par défaut
                return pd.read_csv(file_path, encoding=encoding)

            except Exception as e:
                logging.error(f"Erreur lors de la lecture du CSV: {str(e)}")
                raise

        # Gestion des fichiers Excel
        elif file_path.endswith(('.xlsx', '.xls')):
            try:
                return pd.read_excel(file_path)
            except Exception as e:
                logging.error(
                    f"Erreur lors de la lecture du fichier Excel: {str(e)}")
                raise

        # Gestion des fichiers JSON/XML
        elif file_type == "json/xml":
            if file_path.endswith('.json'):
                try:
                    # Lecture du JSON avec orientation 'records' pour gérer les structures irrégulières
                    with open(file_path, 'r', encoding='utf-8') as f:
                        import json
                        data = json.load(f)

                    # Si c'est une liste de dictionnaires
                    if isinstance(data, list):
                        return pd.json_normalize(data)
                    # Si c'est un dictionnaire
                    elif isinstance(data, dict):
                        # Si le dictionnaire contient des listes de même longueur
                        try:
                            return pd.DataFrame(data)
                        except ValueError:
                            # Si la conversion directe échoue, normaliser la structure
                            return pd.json_normalize(data)
                    else:
                        raise ValueError("Format JSON non supporté")

                except Exception as e:
                    logging.error(
                        f"Erreur lors de la lecture du JSON: {str(e)}")
                    raise
            elif file_path.endswith('.xml'):
                return pd.read_xml(file_path)

        # Gestion des images
        elif file_type == "image":
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

        else:
            raise ValueError(
                f"Format de fichier non pris en charge: {file_type}")

    except Exception as e:
        logging.error(
            f"Erreur lors du chargement du fichier {file_path}: {str(e)}")
        raise


def analyze_dataset(dataset):
    """
    @brief Analyse un dataset et propose les meilleurs modèles de ML adaptés.
    """
    summary = {}
    recommendations = []

    # Pour les données textuelles
    if isinstance(dataset, dict) and dataset.get("type") == "text":
        content = dataset["data"]
        nb_points = len(content)  # Nombre de caractères
        summary = {
            "type": "Texte",
            "chemin": dataset["path"],
            "format": dataset.get("format", "txt"),
            "encodage": dataset.get("encoding", "inconnu"),
            "taille": f"{len(content)} caractères",
            "nombre_lignes": content.count('\n') + 1,
            "nombre_points": nb_points,
            "aperçu": content[:200] + "..." if len(content) > 200 else content
        }

        recommendations.extend([
            "Modèles recommandés pour le texte:",
            "- Naive Bayes: Efficace pour la classification de texte, rapide et performant avec peu de données",
            "- TF-IDF + SVM: Excellent pour les textes courts et moyens, capture bien les mots importants",
            "- BERT: Pour une compréhension profonde du contexte, idéal pour les tâches complexes",
            "- RNN/LSTM: Pour l'analyse séquentielle et la prédiction de texte",
            "- Word2Vec: Pour créer des représentations vectorielles de mots similaires"
        ])

    # Pour les données tabulaires (DataFrame)
    elif isinstance(dataset, pd.DataFrame):
        nb_samples = len(dataset)
        nb_features = len(dataset.columns)
        nb_points = nb_samples * nb_features
        numeric_cols = dataset.select_dtypes(include=['number']).columns
        categorical_cols = dataset.select_dtypes(exclude=['number']).columns

        summary = {
            "type": "Données tabulaires",
            "dimensions":
            f"{dataset.shape[0]} lignes × {dataset.shape[1]} colonnes",
            "nombre_points": f"{nb_points:,} points (lignes × colonnes)",
            "taille_memoire":
            f"{dataset.memory_usage().sum() / 1024**2:.2f} MB",
            "types_colonnes": dict(dataset.dtypes.value_counts()),
            "valeurs_manquantes": dataset.isnull().sum().sum(),
            "colonnes": list(dataset.columns),
            "ratio_cat_num": f"{len(categorical_cols)}:{len(numeric_cols)}"
        }

        # Ajout de statistiques basiques pour les colonnes numériques
        if not dataset.select_dtypes(include=['number']).empty:
            summary["statistiques"] = dataset.describe().to_dict()

        # Recommandations basées sur la taille et le type de données
        if nb_samples > 100000:
            recommendations.extend([
                "Modèles recommandés pour grands volumes de données (>100k échantillons):",
                "- SGD (Descente de gradient stochastique): Optimal pour grands datasets, apprentissage incrémental",
                "- Réseaux de neurones: Excellents pour capturer des patterns complexes dans de grands volumes",
                "- SGDRegressor/Classifier: Rapides et efficaces en mémoire pour l'apprentissage en ligne"
            ])
        else:
            if len(categorical_cols) > len(numeric_cols):
                recommendations.extend([
                    "Modèles recommandés pour données majoritairement catégorielles:",
                    "- Random Forest: Gère bien les variables catégorielles, pas de normalisation requise",
                    "- XGBoost: Excellent pour les données mixtes, gestion automatique des catégories",
                    "- CatBoost: Spécialement conçu pour les variables catégorielles, moins de prétraitement nécessaire",
                    "- LightGBM: Rapide et efficace avec les catégories, bon pour l'optimisation"
                ])
            else:
                recommendations.extend([
                    "Modèles recommandés pour données numériques (<100k échantillons):",
                    "- Linear/Logistic Regression: Pour relations linéaires, données normalement distribuées",
                    "- Ridge/Lasso: Quand il y a beaucoup de features ou de la multicolinéarité",
                    "- SVM: Excellent pour données non-linéaires avec kernel trick",
                    "- KNN: Pour données avec structure de voisinage claire, petits datasets"
                ])

    # Pour les images
    elif isinstance(dataset, dict) and dataset.get("type") == "image":
        img_data = dataset["data"]
        if hasattr(img_data, 'size'):  # PIL Image
            width, height = img_data.size
            channels = len(img_data.getbands())
            nb_points = width * height * channels
        elif hasattr(img_data, 'shape'):  # Numpy array
            if len(img_data.shape) == 3:
                height, width, channels = img_data.shape
            else:
                height, width = img_data.shape
                channels = 1
            nb_points = width * height * channels

        summary = {
            "type": "Image",
            "chemin": dataset["path"],
            "format": dataset["path"].split(".")[-1].upper(),
            "dimensions": f"{width}×{height} pixels",
            "canaux": channels,
            "nombre_points": f"{nb_points:,} points (pixels × canaux)",
            "mode": img_data.mode if hasattr(img_data, 'mode') else 'N/A'
        }

        recommendations.extend([
            "Modèles recommandés pour images:",
            "- CNN: Architecture de base pour tout traitement d'image, extraction automatique de features",
            "- ResNet: Pour images complexes, évite le problème de vanishing gradient",
            "- VGG: Architecture simple et efficace pour la classification",
            "- EfficientNet: Optimal pour ressources limitées, excellent ratio performance/coût",
            "- YOLO: Spécifique à la détection d'objets en temps réel"
        ])

    # Pour les données JSON
    elif isinstance(dataset, dict) and dataset.get("type") == "json":
        if isinstance(dataset, pd.DataFrame):
            nb_points = len(dataset) * len(dataset.columns)
        else:
            nb_points = len(dataset)

        summary = {
            "type":
            "JSON structuré",
            "nombre_enregistrements":
            len(dataset),
            "nombre_points":
            f"{nb_points:,} points",
            "structure":
            "DataFrame"
            if isinstance(dataset, pd.DataFrame) else "Structure variable"
        }

        if nb_points > 100000:
            recommendations.extend([
                "Modèles recommandés pour données JSON structurées (>100k points):",
                "- Gradient Boosting: Excellent pour grandes structures tabulaires",
                "- Réseaux de neurones: Pour capturer des relations complexes",
                "- SGD: Pour apprentissage efficace sur grands volumes"
            ])
        else:
            recommendations.extend([
                "Modèles recommandés pour données JSON structurées (<100k points):",
                "- RandomForest: Robuste et polyvalent pour structures variables",
                "- SVM: Pour données non-linéaires, bon avec features engineering",
                "- KNN: Pour données avec similarité structurelle"
            ])

    # Ajout de la catégorie de taille
    if 'nombre_points' in summary:
        summary[
            "categorie_taille"] = "Grand dataset (>100k points)" if nb_points > 100000 else "Dataset standard (<100k points)"

    return summary, recommendations


# Utilisation
if __name__ == "__main__":
    import logging
    logging.basicConfig(level=logging.INFO)

    # Liste des fichiers à tester
    test_files = [
        "././data/image/Djangounchained.webp",  # Image WebP
        "././data/csv/pokemon.csv",  # CSV
        "././data/txt/teest1.txt",  # Texte
        "././data/xlsx/titanic.xlsx",  # Excel
        "././data/json/velo_ville_nantes.json",  # JSON
        # "././data/sql/"                      # SQL (à implémenter)
    ]

    # Création d'une liste pour stocker les résultats
    results = []

    for file_path in test_files:
        try:
            print(f"\n{'='*50}")
            print(f"Test du fichier : {file_path}")
            print(f"{'='*50}")

            dataset = load_file(file_path)
            summary, recommendations = analyze_dataset(dataset)

            # Affichage des résultats
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

            # Ajout des résultats à la liste
            results.append({
                "fichier":
                file_path,
                "resume":
                summary,
                "recommendations":
                recommendations,
                "date_analyse":
                pd.Timestamp.now().strftime("%Y-%m-%d %H:%M:%S")
            })

        except Exception as e:
            logging.error(f"Erreur avec {file_path} : {e}")
            # Ajout de l'erreur dans les résultats
            results.append({
                "fichier":
                file_path,
                "erreur":
                str(e),
                "date_analyse":
                pd.Timestamp.now().strftime("%Y-%m-%d %H:%M:%S")
            })
            continue

    # Création du DataFrame
    df_results = pd.DataFrame(results)

    # Sauvegarde en JSON avec formatage lisible
    output_file = "././data/json/resultat_analyse_dataset.json"
    df_results.to_json(output_file,
                       orient='records',
                       force_ascii=False,
                       indent=4)

    logging.info(f"Résultats sauvegardés dans {output_file}")
