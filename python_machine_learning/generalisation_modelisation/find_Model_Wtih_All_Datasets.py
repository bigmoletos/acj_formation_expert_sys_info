import pandas as pd
import numpy as np
from sklearn.utils.multiclass import type_of_target
from mimetypes import guess_type
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

# def detect_file_type(file_path):
#     """
#     Détecte le type de fichier en fonction de son extension ou de son contenu.
#     :param file_path: Chemin du fichier
#     :return: Type de fichier détecté
#     """
#     mime_type, _ = guess_type(file_path)
#     if mime_type:
#         if "text" in mime_type:
#             return "text"
#         elif "image" in mime_type:
#             return "image"
#         elif "audio" in mime_type:
#             return "audio"
#         elif "video" in mime_type:
#             return "video"
#         elif "json" in mime_type or "xml" in mime_type:
#             return "json/xml"
#     # Pour les fichiers non reconnus
#     ext = file_path.split(".")[-1].lower()
#     if ext in ["csv", "xlsx", "xls", "txt"]:
#         return "tabular"
#     elif ext in ["npy", "bin"]:
#         return "binary"
#     return "unknown"

# def load_file(file_path):
#     """
#     Charge le fichier en fonction de son type.
#     :param file_path: Chemin du fichier
#     :return: Objet contenant les données (DataFrame ou autre)
#     """
#     file_type = detect_file_type(file_path)
#     if file_type == "tabular":
#         if file_path.endswith(".csv"):
#             return pd.read_csv(file_path)
#         elif file_path.endswith(".xlsx") or file_path.endswith(".xls"):
#             return pd.read_excel(file_path)
#         elif file_path.endswith(".txt"):
#             return pd.read_csv(file_path, delimiter="\t")
#     elif file_type == "json/xml":
#         if file_path.endswith(".json"):
#             return pd.read_json(file_path)
#         elif file_path.endswith(".xml"):
#             return pd.read_xml(file_path)
#     elif file_type == "binary":
#         if file_path.endswith(".npy"):
#             return np.load(file_path, allow_pickle=True)
#     elif file_type in ["image", "audio", "video"]:
#         return {"type": file_type, "path": file_path}
#     raise ValueError("Format de fichier non pris en charge.")

# def analyze_dataset(dataset):
#     """
#     Analyse un dataset tabulaire ou détecte les types de données non tabulaires,
#     puis propose les modèles de Machine Learning adaptés.
#     :param dataset: Dataset (DataFrame ou dictionnaire pour d'autres types)
#     :return: Liste de modèles recommandés
#     """
#     recommendations = []

#     if isinstance(dataset, pd.DataFrame):  # Si les données sont tabulaires
#         # Étape 1 : Analyse du nombre d'échantillons
#         num_samples = dataset.shape[0]
#         if num_samples > 100_000:
#             recommendations.append("Réseaux de Neurones (Deep Learning)")
#             recommendations.append(
#                 "SGDClassifier / SGDRegressor (descente de gradient)")
#         else:
#             recommendations.append(
#                 "Modèles classiques (Random Forest, SVM, KNN, etc.)")

#         # Étape 2 : Vérifier le type de données (structurées ou non)
#         is_structured = dataset.select_dtypes(include=['number']).shape[1] > 0
#         if not is_structured:
#             recommendations.append(
#                 "Modèles spécialisés pour données non structurées (CNN, RNN pour texte/images/audio)"
#             )

#         # Étape 3 : Vérifier la normalité des données
#         numeric_columns = dataset.select_dtypes(include=['number']).columns
#         if not numeric_columns.empty:
#             normal_data = dataset[numeric_columns].apply(
#                 lambda col: abs(col.skew()) < 1).all()
#             if normal_data:
#                 recommendations.append(
#                     "Modèles linéaires (Linear Regression, Ridge, Lasso)")
#             else:
#                 recommendations.append(
#                     "Modèles non paramétriques (Decision Trees, Random Forest, Gradient Boosting)"
#                 )

#         # Étape 4 : Identifier le type de variables cibles
#         target_column = dataset.columns[
#             -1]  # Dernière colonne comme cible par défaut
#         target_type = type_of_target(dataset[target_column])

#         if target_type == "binary" or target_type == "multiclass":
#             recommendations.append(
#                 "Classification (Logistic Regression, Random Forest, SVM, Gradient Boosting)"
#             )
#         elif target_type == "continuous":
#             recommendations.append(
#                 "Régression (Linear Regression, Random Forest Regressor, Gradient Boosting Regressor)"
#             )
#         elif target_type == "multilabel-indicator":
#             recommendations.append(
#                 "Classification multilabel (One-vs-Rest avec Random Forest ou SVM)"
#             )

#         # Étape 5 : Analyse du nombre de variables qualitatives et quantitatives
#         num_qualitative = dataset.select_dtypes(
#             include=['object', 'category']).shape[1]
#         num_quantitative = dataset.select_dtypes(include=['number']).shape[1]
#         if num_qualitative > 0 and num_quantitative > 0:
#             recommendations.append(
#                 "Approches mixtes : Pipelines avec encodage des variables catégorielles"
#             )
#         elif num_qualitative > 0:
#             recommendations.append(
#                 "Encodage nécessaire pour variables catégorielles (OneHotEncoder, CatBoost)"
#             )
#         elif num_quantitative > 0:
#             recommendations.append(
#                 "Modèles adaptés aux variables numériques (Random Forest, Linear Models)"
#             )
#     else:
#         # Analyse pour d'autres types de données
#         if dataset["type"] == "image":
#             recommendations.append(
#                 "Réseaux de Neurones Convolutionnels (CNN) pour la classification ou la détection d'objets"
#             )
#         elif dataset["type"] == "audio":
#             recommendations.append(
#                 "RNN / LSTM pour analyse audio ou reconnaissance vocale")
#         elif dataset["type"] == "video":
#             recommendations.append(
#                 "Modèles CNN + RNN pour l'analyse vidéo ou détection d'actions"
#             )
#         elif dataset["type"] == "text":
#             recommendations.append(
#                 "Transformers (BERT, GPT) ou TF-IDF + SVM pour le traitement de texte"
#             )

#     return recommendations

# # utilisation
# if __name__ == "__main__":
#     #  chargement de fichier CSV
#     try:
#         # file_path = ".././data/image/Djangounchained.webp"
#         file_path = "././data/csv/name_basics.csv"
#         dataset = load_file(file_path)
#         print(dataset)
#     #     recommendations = analyze_dataset(dataset)

#     #     # Afficher les recommandations
#     #     print("Recommandations de modèles pour le dataset :")
#     #     for rec in recommendations:
#     #         print(f"- {rec}")
#     except Exception as e:
#         print(f"Erreur : {e}")

import os
import pandas as pd
import numpy as np
from sklearn.utils.multiclass import type_of_target
from mimetypes import guess_type


def detect_file_type(file_path):
    """
    @brief Détecte le type de fichier en fonction de son extension ou de son contenu.

    @param file_path Chemin du fichier
    @return Type de fichier détecté ("text", "image", "audio", "video", "json/xml", "tabular", "binary", "unknown")

    @details
    - Détection automatique du type de fichier avec `mimetypes.guess_type`.
    - Prise en charge des formats suivants :
      - Tabulaires : CSV, Excel, TXT.
      - Non tabulaires : JSON, XML, images, audio, vidéos.
      - Binaires : Numpy (.npy), fichiers binaires divers.
    """
    mime_type, _ = guess_type(file_path)
    if mime_type:
        if "text" in mime_type:
            return "text"
        elif "image" in mime_type:
            return "image"
        elif "audio" in mime_type:
            return "audio"
        elif "video" in mime_type:
            return "video"
        elif "json" in mime_type or "xml" in mime_type:
            return "json/xml"
    ext = file_path.split(".")[-1].lower()
    if ext in ["csv", "xlsx", "xls", "txt"]:
        return "tabular"
    elif ext in ["npy", "bin"]:
        return "binary"
    return "unknown"


def load_file(file_path):
    """
    @brief Charge un fichier en fonction de son type.

    @param file_path Chemin du fichier
    @return Données chargées (DataFrame ou dictionnaire contenant des métadonnées pour les formats non tabulaires)

    @details
    - Les fichiers tabulaires (CSV, Excel, TXT) sont chargés avec Pandas.
    - Les fichiers binaires (Numpy .npy) sont chargés avec Numpy.
    - Les fichiers JSON/XML sont chargés avec les parsers correspondants de Pandas.
    - Pour les formats non tabulaires (images, audio, vidéos), les données sont encapsulées dans un dictionnaire.
    """
    if not os.path.exists(file_path):
        raise FileNotFoundError(
            f"Le fichier spécifié n'existe pas : {file_path}")

    file_type = detect_file_type(file_path)
    if file_type == "tabular":
        if file_path.endswith(".csv"):
            return pd.read_csv(file_path)
        elif file_path.endswith(".xlsx") or file_path.endswith(".xls"):
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
    elif file_type in ["image", "audio", "video"]:
        return {"type": file_type, "path": file_path}
    raise ValueError("Format de fichier non pris en charge.")


def analyze_dataset(dataset):
    """
    @brief Analyse un dataset et propose les meilleurs modèles de Machine Learning adaptés.

    @param dataset Dataset à analyser (DataFrame ou métadonnées pour d'autres types)

    @return Liste de recommandations de modèles de Machine Learning

    @details
    - Analyse des échantillons, types de données, normalité, cible et variables qualitatives/quantitatives.
    """
    recommendations = []

    if isinstance(dataset, pd.DataFrame):  # Si les données sont tabulaires
        num_samples = dataset.shape[0]
        if num_samples > 100_000:
            recommendations.append("Réseaux de Neurones (Deep Learning)")
            recommendations.append(
                "SGDClassifier / SGDRegressor (descente de gradient)")
        else:
            recommendations.append(
                "Modèles classiques (Random Forest, SVM, KNN, etc.)")

        is_structured = dataset.select_dtypes(include=['number']).shape[1] > 0
        if not is_structured:
            recommendations.append(
                "Modèles spécialisés pour données non structurées (CNN, RNN pour texte/images/audio)"
            )

        numeric_columns = dataset.select_dtypes(include=['number']).columns
        if not numeric_columns.empty:
            normal_data = dataset[numeric_columns].apply(
                lambda col: abs(col.skew()) < 1).all()
            if normal_data:
                recommendations.append(
                    "Modèles linéaires (Linear Regression, Ridge, Lasso)")
            else:
                recommendations.append(
                    "Modèles non paramétriques (Decision Trees, Random Forest, Gradient Boosting)"
                )

        target_column = dataset.columns[-1]
        target_type = type_of_target(dataset[target_column])

        if target_type == "binary" or target_type == "multiclass":
            recommendations.append(
                "Classification (Logistic Regression, Random Forest, SVM, Gradient Boosting)"
            )
        elif target_type == "continuous":
            recommendations.append(
                "Régression (Linear Regression, Random Forest Regressor, Gradient Boosting Regressor)"
            )
        elif target_type == "multilabel-indicator":
            recommendations.append(
                "Classification multilabel (One-vs-Rest avec Random Forest ou SVM)"
            )

        num_qualitative = dataset.select_dtypes(
            include=['object', 'category']).shape[1]
        num_quantitative = dataset.select_dtypes(include=['number']).shape[1]
        if num_qualitative > 0 and num_quantitative > 0:
            recommendations.append(
                "Approches mixtes : Pipelines avec encodage des variables catégorielles"
            )
        elif num_qualitative > 0:
            recommendations.append(
                "Encodage nécessaire pour variables catégorielles (OneHotEncoder, CatBoost)"
            )
        elif num_quantitative > 0:
            recommendations.append(
                "Modèles adaptés aux variables numériques (Random Forest, Linear Models)"
            )
    else:
        if dataset["type"] == "image":
            recommendations.append(
                "Réseaux de Neurones Convolutionnels (CNN) pour la classification ou la détection d'objets"
            )
        elif dataset["type"] == "audio":
            recommendations.append(
                "RNN / LSTM pour analyse audio ou reconnaissance vocale")
        elif dataset["type"] == "video":
            recommendations.append(
                "Modèles CNN + RNN pour l'analyse vidéo ou détection d'actions"
            )
        elif dataset["type"] == "text":
            recommendations.append(
                "Transformers (BERT, GPT) ou TF-IDF + SVM pour le traitement de texte"
            )

    return recommendations


# Utilisation
if __name__ == "__main__":
    # Chargement de fichier CSV ou autre
    try:
        # file_path = "././data/image/Djangounchained.webp"  # Exemple image
        file_path = "././data/csv/name_basics.csv"  # Exemple CSV
        dataset = load_file(file_path)
        recommendations = analyze_dataset(dataset)

        # Afficher les recommandations
        print("Recommandations de modèles pour le dataset :")
        for rec in recommendations:
            print(f"- {rec}")
    except Exception as e:
        print(f"Erreur : {e}")
