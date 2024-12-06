import os
import replicate
import requests
import httpx
import logging
import time
from collections.abc import Generator
from dotenv import load_dotenv

# Charger les variables d'environnement depuis .env
load_dotenv()

# Configuration du logger
logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)

# Répertoire des images
BASE_DIR = os.path.join("data", "images")
os.makedirs(BASE_DIR, exist_ok=True)

# Liste des modèles à tester
MODELS = {
    "nvidia_sana":
    "nvidia/sana:88312dcb9eaa543d7f8721e092053e8bb901a45a5d3c63c84e0a5aa7c247df33",
    "stability_sdxl":
    "stability-ai/sdxl:39ed52f2a78e934b3ba6e2a89f5b1c712de7dfea535525255b1aa35c5565e08b",
    "openjourney":
    "prompthero/openjourney-v4",  # À vérifier si toujours disponible
    "dreamlike_diffusion":
    "dreamlike-art/dreamlike-photoreal-2.0"  # Alternative fiable
}

# Prompts réalistes avec éclairages naturels
PROMPTS = {
    "forest_cat":
    "A realistic cat in a spruce forest during golden hour, soft shadows, natural lighting, toys and birds around, cinematic composition.",
    "monument_lake":
    "A majestic monument surrounded by a calm lake, trees glowing in warm sunlight, mountain backdrop, realistic animals grazing nearby.",
    "river_mountains":
    "A serene river flowing through mountains, spruce trees glowing under soft morning light, birds flying above, highly detailed."
}

# Vérifier que le token d'API est disponible
if not os.getenv("REPLICATE_API_TOKEN"):
    logger.error("Token API non défini ou invalide. Vérifiez le fichier .env.")
    raise EnvironmentError("Token API manquant ou invalide.")


def verifier_model(model_key):
    """Vérifie si le modèle est valide et accessible via l'API Replicate."""
    try:
        model = MODELS[model_key]
        model_name = model.split(":")[
            0]  # Extrait le nom du modèle sans la version
        url = f"https://api.replicate.com/v1/models/{model_name}"
        headers = {
            "Authorization": f"Token {os.getenv('REPLICATE_API_TOKEN')}"
        }
        logger.info("Vérification du modèle via URL : %s", url)
        response = httpx.get(url, headers=headers)

        if response.status_code == 200:
            logger.info("Modèle validé : %s", model)
        else:
            logger.error("Le modèle '%s' est inaccessible. Code HTTP : %s",
                         model_key, response.status_code)
            raise ValueError(
                f"Le modèle '{model_key}' est invalide ou inaccessible.")
    except Exception as e:
        logger.error(
            "Erreur lors de la validation du modèle '%s'. Détails : %s",
            model_key, e)
        raise


def attendre_completion(prediction):
    """Attend la complétion d'une prédiction et retourne le résultat final."""
    try:
        if isinstance(prediction, dict) and 'status' in prediction:
            while prediction['status'] not in ["succeeded", "failed"]:
                time.sleep(1)
                prediction.reload()
            return prediction
        elif isinstance(prediction, bytes):
            logger.info(
                "La prédiction est un fichier binaire (image ou autre).")
            return prediction
        elif isinstance(prediction, replicate.helpers.FileOutput):
            logger.info("La prédiction est de type FileOutput.")
            return prediction.read()
        elif isinstance(prediction, (list, Generator)):
            logger.info("La prédiction est un générateur ou une liste.")
            for result in prediction:
                logger.debug("Résultat du générateur : %s", result)
                if isinstance(result, dict) and 'status' in result:
                    while result['status'] not in ["succeeded", "failed"]:
                        time.sleep(1)
                        result.reload()
                    return result
                elif isinstance(result, bytes):
                    logger.info("Résultat binaire obtenu via le générateur.")
                    return result
                elif isinstance(result, replicate.helpers.FileOutput):
                    logger.info("FileOutput obtenu via le générateur.")
                    return result
                else:
                    logger.warning("Format inattendu dans le générateur : %s",
                                   type(result))
            logger.error(
                "Le générateur n'a produit aucun résultat exploitable.")
            raise ValueError(
                "Aucun résultat valide produit par le générateur.")
        else:
            logger.error("Format inattendu de 'prediction': %s",
                         type(prediction))
            raise TypeError(
                "Le résultat de la prédiction n'est ni un dictionnaire, ni un fichier binaire, ni FileOutput, ni un générateur valide."
            )
    except Exception as e:
        logger.error("Erreur inattendue: %s", e)
        raise


def sauvegarder_image(output, chemin_fichier):
    """Sauvegarde l'image à partir du résultat brut ou d'une URL."""
    try:
        if isinstance(output, replicate.helpers.FileOutput):
            with open(chemin_fichier, 'wb') as f:
                f.write(output.read())
            logger.info("Image sauvegardée sous %s", chemin_fichier)
        elif isinstance(output, bytes):
            with open(chemin_fichier, 'wb') as f:
                f.write(output)
            logger.info("Image sauvegardée sous %s", chemin_fichier)
        elif isinstance(output, dict):
            output_url = output.get('output', {}).get('url')
            if output_url and output_url.startswith("http"):
                response = requests.get(output_url)
                response.raise_for_status()
                with open(chemin_fichier, 'wb') as f:
                    f.write(response.content)
                logger.info("Image téléchargée et sauvegardée sous %s",
                            chemin_fichier)
            else:
                logger.error(
                    "Erreur : L'URL retournée n'est pas valide ou est vide.")
        else:
            logger.error("Format inattendu de 'output': %s", type(output))
            raise TypeError("Le format de l'output est inconnu.")
    except Exception as e:
        logger.error("Erreur lors de la sauvegarde de l'image: %s", e)
        raise


def generer_image(model_key, prompt_key, image_name, image_input=None):
    """Génère une image à partir d'un prompt et d'un modèle spécifié."""
    verifier_model(model_key)
    model = MODELS[model_key]
    prompt = PROMPTS[prompt_key]
    inputs = {
        "width": 1024,
        "height": 1024,
        "prompt": prompt,
        "guidance_scale": 7.5,
        "num_inference_steps": 25
    }
    if image_input:
        inputs["image"] = image_input

    output_path = os.path.join(BASE_DIR, image_name)
    logger.debug("Payload envoyé : %s", inputs)
    try:
        output = replicate.run(model, input=inputs)
        output = attendre_completion(output)
        sauvegarder_image(output, output_path)
    except httpx.HTTPStatusError as e:
        if e.response.status_code == 404:
            logger.error(
                "Erreur 404 : Modèle ou ressource introuvable pour '%s'.",
                model_key)
        raise
    except Exception as e:
        logger.error("Erreur lors de la génération de l'image : %s", e)
        raise


if __name__ == "__main__":
    try:
        generer_image("nvidia_sana", "forest_cat",
                      "output_nvidia_forest_cat.png")
        generer_image("stability_sdxl", "monument_lake",
                      "output_stability_monument_lake.png")
        generer_image("openjourney", "river_mountains",
                      "output_openjourney_river_mountains.png")
        generer_image("dreamlike_diffusion", "forest_cat",
                      "output_dreamlike_forest_cat.png")
    except Exception as e:
        logger.error("Une erreur est survenue : %s", e)
