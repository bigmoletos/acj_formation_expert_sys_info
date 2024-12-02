import os
import logging
# import kaggle
from kaggle.api.kaggle_api_extended import KaggleApi

# Configuration du logger
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Définir le chemin du répertoire contenant kaggle.json
kaggle_json_path = os.path.expanduser(
    "~/.kaggle/kaggle.json")  # Utiliser le chemin par défaut
os.environ['KAGGLE_CONFIG_DIR'] = os.path.dirname(kaggle_json_path)

# print(kaggle_json_path)
print(f"\nkaggle_json_path :\n{kaggle_json_path} \n")

# Supprimer la double authentification
try:
    # Initialisation de l'API
    api = KaggleApi()
    api.model_list_cli()
    logger.info("Tentative d'authentification...")
    api.authenticate()
    logger.info("Authentification réussie !")
except Exception as e:
    logger.error(f"Erreur d'authentification : {e}")
    exit(1)

# Vérification de l'authentification
try:
    # Test simple de connexion
    api.competitions_list_cli(search="")
    logger.info("test liste des modeles ok")
except Exception as e:
    logger.error(f"Erreur de recup de la liste des modeles : {e}")
    exit(1)


# Récupérer les compétitions actives
def get_active_competitions():
    """Récupère la liste des compétitions actives."""
    try:
        logger.info("Tentative de récupération des compétitions actives...")
        competitions = api.competitions_list(search="")
        logger.info("Compétitions récupérées avec succès.")
        return competitions
    except Exception as e:
        logger.error(f"Erreur lors de la récupération des compétitions : {e}")
        raise


# Récupérer les 10 meilleurs compétiteurs d'une compétition
def get_top_competitors(competition_name):
    """Récupère les 10 meilleurs compétiteurs d'une compétition spécifique."""
    try:
        leaderboard = api.competition_view_leaderboard(competition_name)
        logger.info(f"Top 10 pour la compétition '{competition_name}':")
        for rank, user in enumerate(leaderboard['leaderboard'][:10], 1):
            logger.info(
                f"Rank {rank}: {user['teamName']} - Score: {user['score']}")
    except Exception as e:
        logger.error(f"Erreur : {e}. Vérifiez le nom de la compétition.")


def get_kaggle_models():
    """Récupère la liste des modèles disponibles sur Kaggle."""
    try:
        logger.info("Tentative de récupération des modèles...")
        models = api.model_list(
            sort_by=
            'hotness',  # Autres options: 'downloadCount', 'voteCount', etc.
            search='',
            page_size=20  # Nombre de modèles à récupérer
        )

        logger.info("Modèles récupérés avec succès")
        for model in models:
            logger.info(f"Modèle: {model.title}")
            logger.info(f"- Auteur: {model.ownerName}")
            logger.info(f"- URL: {model.url}")
            logger.info("---")

        return models

    except Exception as e:
        logger.error(f"Erreur lors de la récupération des modèles : {e}")
        raise


# recuperer les modèles
liste_modeles = get_kaggle_models()
print(f"\nliste_modeles :\n{liste_modeles} \n")

# Lister les compétitions actives
competitions = get_active_competitions()

# Exemple : récupérer les compétiteurs pour une compétition spécifique
competition_name = input(
    "\nEntrez le nom d'une compétition pour voir le leaderboard : ").strip()
get_top_competitors(competition_name)
