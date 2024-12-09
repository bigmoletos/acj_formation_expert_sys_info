from sklearn.model_selection import train_test_split, GridSearchCV, RandomizedSearchCV
import seaborn as sns
import matplotlib.pyplot as plt
import pickle
import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler, LabelEncoder, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

import logging

# Configurer le logger
logger = logging.getLogger("notebook_logger")
logger.setLevel(logging.DEBUG)

console_handler = logging.StreamHandler()
formatter = logging.Formatter(
    '%(asctime)s - %(name)s - %(levelname)s - %(message)s')
console_handler.setFormatter(formatter)
logger.addHandler(console_handler)


def load_dataset(filepath):
    """
    Charger le dataset et retourner le DataFrame.
    """
    try:
        data = pd.read_csv(filepath)
        logger.info("Dataset chargé avec succès.")
        return data
    except Exception as e:
        logger.error(f"Erreur lors du chargement du dataset: {e}")
        raise


def preprocess_data(df):
    """
    Préparer les données : nettoyage et encodage.
    """
    try:
        # Suppression des colonnes inutiles
        df = df.drop(['RowNumber', 'CustomerId', 'Surname'], axis=1)

        # Encodage des variables catégoriques
        df = pd.get_dummies(df,
                            columns=['Geography', 'Gender'],
                            drop_first=True)

        # Séparation des features (X) et de la cible (y)
        X = df.drop('Exited', axis=1)
        y = df['Exited']
        logger.info("Prétraitement des données terminé.")
        return X, y
    except Exception as e:
        logger.error(f"Erreur lors du prétraitement des données: {e}")
        raise


def save_dataframe(df, output_file):
    """
    Sauvegarder un DataFrame au format pickle.

    :param df: DataFrame à sauvegarder
    :param output_file: Chemin et nom du fichier pickle
    """
    try:
        with open(output_file, 'wb') as f:
            pickle.dump(df, f)
            logger.info(f"Dataset sauvegardé avec succès dans {output_file}.")
    except Exception as e:
        logger.error(f"Erreur lors de la sauvegarde du DataFrame : {e}")
        raise


def load_dataframe(filepath):
    """
    Charger un DataFrame sauvegardé au format pickle.
    """
    with open(filepath, 'rb') as f:
        return pickle.load(f)


def train_model(X_train, y_train):
    """
    Entraîner un modèle Random Forest.
    """
    try:
        model = RandomForestClassifier(n_estimators=100, random_state=42)
        model.fit(X_train, y_train)
        logger.info("Modèle entraîné avec succès.")
        return model
    except Exception as e:
        logger.error(f"Erreur lors de l'entraînement du modèle: {e}")
        raise


def evaluate_model(model, X_test, y_test):
    """
    Évaluer le modèle sur l'ensemble de test.
    """
    try:
        y_pred = model.predict(X_test)
        acc = accuracy_score(y_test, y_pred)
        cm = confusion_matrix(y_test, y_pred)
        cr = classification_report(y_test, y_pred)

        logger.info(f"Accuracy: {acc}")
        logger.info(f"Confusion Matrix:\n{cm}")
        logger.info(f"Classification Report:\n{cr}")
        return acc, cm, cr
    except Exception as e:
        logger.error(f"Erreur lors de l'évaluation du modèle: {e}")
        raise


if __name__ == "__main__":
    # filepath = "Churn_Modelling.csv"  # Remplacez par le chemin réel du fichier
    filepath = r"C:\AJC_formation\data\csv\churn_modelling.csv"  # Remplacez par le chemin réel du fichier
    try:
        # Charger et préparer les données
        data = load_dataset(filepath)
        X, y = preprocess_data(data)
        save_dataframe(
            X, r"C:\AJC_formation\data\csv\churn_modelling_preprocessed.pkl")
        # Diviser les données
        X_train, X_test, y_train, y_test = train_test_split(X,
                                                            y,
                                                            test_size=0.2,
                                                            random_state=42)

        # Entraîner le modèle
        model = train_model(X_train, y_train)

        # Évaluer le modèle
        evaluate_model(model, X_test, y_test)
    except Exception as e:
        logger.error(f"Erreur dans le pipeline: {e}")
