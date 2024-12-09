import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.pipeline import Pipeline
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report, roc_curve, auc
import logging

# Configurer le logger
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


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
    Séparer les features et la cible.
    """
    try:
        # Suppression des colonnes inutiles
        df = df.drop(['RowNumber', 'CustomerId', 'Surname'], axis=1)

        # Séparation des features (X) et de la cible (y)
        X = df.drop('Exited', axis=1)
        y = df['Exited']
        logger.info("Prétraitement des données terminé.")
        return X, y
    except Exception as e:
        logger.error(f"Erreur lors du prétraitement des données: {e}")
        raise


def build_pipeline():
    """
    Construire le pipeline avec préprocesseur et classifieur.
    """
    try:
        # Définir les colonnes numériques et catégoriques
        numeric_features = [
            'CreditScore', 'Age', 'Tenure', 'Balance', 'NumOfProducts',
            'EstimatedSalary'
        ]
        categorical_features = [
            'Geography', 'Gender', 'HasCrCard', 'IsActiveMember'
        ]

        # Pipeline de prétraitement
        numeric_transformer = StandardScaler()
        categorical_transformer = OneHotEncoder(drop='first')

        preprocessor = ColumnTransformer(
            transformers=[('num', numeric_transformer, numeric_features),
                          ('cat', categorical_transformer,
                           categorical_features)])

        # Pipeline complet
        pipeline = Pipeline(
            steps=[('preprocessor', preprocessor
                    ), ('classifier',
                        RandomForestClassifier(random_state=42))])

        logger.info("Pipeline construit avec succès.")
        return pipeline
    except Exception as e:
        logger.error(f"Erreur lors de la construction du pipeline: {e}")
        raise


def perform_grid_search(pipeline, X_train, y_train):
    """
    Effectuer un GridSearchCV pour trouver les meilleurs hyperparamètres.
    """
    try:
        param_grid = {
            'classifier__n_estimators': [50, 100],
            'classifier__max_depth': [None, 5, 10],
            'classifier__min_samples_split': [2, 5],
            'classifier__min_samples_leaf': [1, 2]
        }

        grid_search = GridSearchCV(pipeline,
                                   param_grid,
                                   cv=5,
                                   n_jobs=-1,
                                   scoring='accuracy')
        grid_search.fit(X_train, y_train)
        logger.info(f"Meilleurs paramètres : {grid_search.best_params_}")
        return grid_search
    except Exception as e:
        logger.error(f"Erreur lors du GridSearchCV: {e}")
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
        logger.info(f"Classification Report:\n{cr}")

        # Afficher la matrice de confusion
        plt.figure(figsize=(6, 4))
        sns.heatmap(cm, annot=True, fmt='d', cmap='Blues')
        plt.title('Matrice de confusion')
        plt.xlabel('Prédit')
        plt.ylabel('Vrai')
        plt.show()

        # Tracer la courbe ROC
        y_proba = model.predict_proba(X_test)[:, 1]
        fpr, tpr, thresholds = roc_curve(y_test, y_proba)
        roc_auc = auc(fpr, tpr)

        plt.figure(figsize=(6, 4))
        plt.plot(fpr, tpr, label='Courbe ROC (AUC = %0.2f)' % roc_auc)
        plt.plot([0, 1], [0, 1], 'k--')
        plt.xlim([0.0, 1.0])
        plt.ylim([0.0, 1.05])
        plt.xlabel('Taux de faux positifs')
        plt.ylabel('Taux de vrais positifs')
        plt.title('Courbe ROC')
        plt.legend(loc='lower right')
        plt.show()

        return acc, cm, cr
    except Exception as e:
        logger.error(f"Erreur lors de l'évaluation du modèle: {e}")
        raise


if __name__ == "__main__":
    filepath = "Churn_Modelling.csv"  # Remplacez par le chemin réel du fichier
    try:
        # Charger et préparer les données
        data = load_dataset(filepath)
        X, y = preprocess_data(data)

        # Diviser les données
        X_train, X_test, y_train, y_test = train_test_split(X,
                                                            y,
                                                            test_size=0.2,
                                                            random_state=42)

        # Construire le pipeline
        pipeline = build_pipeline()

        # Effectuer le GridSearchCV
        model = perform_grid_search(pipeline, X_train, y_train)

        # Évaluer le modèle
        evaluate_model(model, X_test, y_test)
    except Exception as e:
        logger.error(f"Erreur dans le pipeline: {e}")
