import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import logging
from sklearn.experimental import enable_iterative_imputer  # Nécessaire pour IterativeImputer
from sklearn.impute import SimpleImputer, KNNImputer, IterativeImputer

# Configuration du logger
logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)


def generate_dataset():
    """
    Génère un dataset fictif avec des valeurs de température toutes les 5 minutes sur une période de 30 jours.

    :return: DataFrame avec des valeurs manquantes aléatoires.
    """
    try:
        logger.info("Génération du dataset avec des valeurs manquantes.")
        dates = pd.date_range(start="2024-01-01",
                              end="2024-01-30 23:55",
                              freq="5T")  # Toutes les 5 minutes
        temperatures = np.random.uniform(10, 30, size=len(dates))

        # Introduire des valeurs manquantes (de 1 min à 1 jour)
        missing_indices = np.random.choice(len(temperatures),
                                           size=1000,
                                           replace=False)
        temperatures[missing_indices] = np.nan

        data = pd.DataFrame({"Date": dates, "Temperature": temperatures})
        data.set_index("Date", inplace=True)

        logger.info("Dataset généré avec succès.")
        return data
    except Exception as e:
        logger.error(f"Erreur lors de la génération du dataset : {e}")
        raise


def pandas_interpolation(data):
    """
    Effectue différentes interpolations avec pandas.

    :param data: DataFrame contenant des données avec des valeurs manquantes.
    :return: Dictionnaire contenant les résultats des interpolations.
    """
    try:
        logger.info("Début des interpolations avec pandas.")
        methods = ["linear", "quadratic", "cubic", "nearest"]
        results = {}
        for method in methods:
            try:
                results[method] = data["Temperature"].interpolate(
                    method=method)
                logger.debug(f"Interpolation {method} réussie.")
            except Exception as e:
                logger.error(f"Erreur avec la méthode Pandas {method} : {e}")
        return results
    except Exception as e:
        logger.error(f"Erreur lors des interpolations avec pandas : {e}")
        raise


def sklearn_interpolation(data):
    """
    Effectue des interpolations avec Scikit-learn.

    :param data: DataFrame contenant des données avec des valeurs manquantes.
    :return: Dictionnaire contenant les résultats des interpolations.
    """
    try:
        logger.info("Début des interpolations avec Scikit-learn.")
        results = {}

        # SimpleImputer (moyenne)
        simple_imputer = SimpleImputer(strategy="mean")
        results["Simple Mean"] = simple_imputer.fit_transform(data)

        # KNNImputer
        knn_imputer = KNNImputer(n_neighbors=3)
        results["KNN"] = knn_imputer.fit_transform(data)

        # IterativeImputer
        iterative_imputer = IterativeImputer(random_state=42)
        results["Iterative"] = iterative_imputer.fit_transform(data)

        logger.info("Interpolations avec Scikit-learn terminées.")
        return results
    except Exception as e:
        logger.error(f"Erreur lors des interpolations avec Scikit-learn : {e}")
        raise


def visualize_results(data, pandas_results):
    """
    Visualise les interpolations sur différentes échelles de temps.

    :param data: DataFrame original avec des données manquantes.
    :param pandas_results: Résultats des interpolations avec pandas.
    """
    try:
        logger.info("Début de la visualisation des résultats.")
        fig, axes = plt.subplots(4, 1, figsize=(15, 20))

        # Zoom sur 1 heure
        one_hour = data.loc["2024-01-01 00:00":"2024-01-01 01:00"]
        axes[0].plot(one_hour.index,
                     one_hour["Temperature"],
                     label="Données originales",
                     marker="o",
                     linestyle="--",
                     color="black")
        for method, result in pandas_results.items():
            axes[0].plot(one_hour.index,
                         result.loc["2024-01-01 00:00":"2024-01-01 01:00"],
                         label=f"Pandas: {method}")
        axes[0].set_title("Zoom sur 1 heure")
        axes[0].legend()
        axes[0].grid()

        # Zoom sur 10 minutes
        ten_minutes = data.loc["2024-01-01 00:00":"2024-01-01 00:10"]
        axes[1].plot(ten_minutes.index,
                     ten_minutes["Temperature"],
                     label="Données originales",
                     marker="o",
                     linestyle="--",
                     color="black")
        for method, result in pandas_results.items():
            axes[1].plot(ten_minutes.index,
                         result.loc["2024-01-01 00:00":"2024-01-01 00:10"],
                         label=f"Pandas: {method}")
        axes[1].set_title("Zoom sur 10 minutes")
        axes[1].legend()
        axes[1].grid()

        # Zoom sur 1 jour
        one_day = data.loc["2024-01-01"]
        axes[2].plot(one_day.index,
                     one_day["Temperature"],
                     label="Données originales",
                     marker="o",
                     linestyle="--",
                     color="black")
        for method, result in pandas_results.items():
            axes[2].plot(one_day.index,
                         result.loc["2024-01-01"],
                         label=f"Pandas: {method}")
        axes[2].set_title("Zoom sur 1 jour")
        axes[2].legend()
        axes[2].grid()

        # Données sur 30 jours
        axes[3].plot(data.index,
                     data["Temperature"],
                     label="Données originales",
                     marker="o",
                     linestyle="--",
                     color="black")
        for method, result in pandas_results.items():
            axes[3].plot(data.index, result, label=f"Pandas: {method}")
        axes[3].set_title("Zoom sur 30 jours")
        axes[3].legend()
        axes[3].grid()

        plt.tight_layout()
        plt.show()
        logger.info("Visualisation terminée avec succès.")
    except Exception as e:
        logger.error(f"Erreur lors de la visualisation : {e}")
        raise


if __name__ == "__main__":
    # Génération du dataset
    dataset = generate_dataset()

    # Interpolation avec Pandas
    pandas_results = pandas_interpolation(dataset)

    # Interpolation avec Scikit-learn
    sklearn_results = sklearn_interpolation(dataset)

    # Visualisation
    visualize_results(dataset, pandas_results)
