import os
import replicate
import requests
import logging
import time
from collections.abc import Generator  # Utilisé pour vérifier les générateurs
from dotenv import load_dotenv

load_dotenv()  # Charge les variables depuis .env

# Configuration du logger
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Définir la variable d'environnement
# os.environ["REPLICATE_API_TOKEN"] = "REMOVED_SECRET"


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
            raise TypeError(
                "Le générateur n'a produit aucun résultat exploitable.")
        else:
            logger.error("Format inattendu de 'prediction': %s",
                         type(prediction))
            raise TypeError(
                "Le résultat de la prédiction n'est ni un dictionnaire, ni un fichier binaire, ni FileOutput, ni un générateur valide."
            )
    except AttributeError as e:
        logger.error("Erreur d'attribut: %s", e)
        raise
    except Exception as e:
        logger.error("Erreur inattendue: %s", e)
        raise


def sauvegarder_image(output, chemin_fichier):
    """Sauvegarde l'image à partir du résultat brut ou d'une URL."""
    try:
        if isinstance(output, replicate.helpers.FileOutput):
            logger.info("Sauvegarde directe depuis FileOutput.")
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


def generer_image_avec_prompt():
    """Génère une image à partir d'un prompt texte."""
    output = replicate.run(
        "nvidia/sana:88312dcb9eaa543d7f8721e092053e8bb901a45a5d3c63c84e0a5aa7c247df33",
        input={
            "width": 1024,
            "height": 1024,
            "prompt":
            "a realistic cat in a forest fo epicéa with toys and birds sign that says \" Franki !\"",
            "guidance_scale": 5,
            "negative_prompt": "",
            "pag_guidance_scale": 2,
            "num_inference_steps": 18
        })
    output = attendre_completion(output)
    sauvegarder_image(output,
                      r"python_machine_learning\tests\replicate\output1.png")


def generer_image_avec_image_locale():
    """Génère une image à partir d'une image locale et d'un prompt texte."""
    with open(r"python_machine_learning\tests\replicate\china.jpg",
              "rb") as image:
        output = replicate.run(
            "stability-ai/sdxl:39ed52f2a78e934b3ba6e2a89f5b1c712de7dfea535525255b1aa35c5565e08b",
            input={
                "width": 1024,
                "height": 1024,
                "prompt":
                "That's my favorite monument. Imagine a lake with some trees and a mountain in the background, add some animals?",
                "image": image,
                "guidance_scale": 7.5,
                "negative_prompt": "",
                "num_inference_steps": 25
            })
        output = attendre_completion(output)
        sauvegarder_image(
            output, r"python_machine_learning\tests\replicate\output2.png")


def generer_image_avec_image_en_ligne():
    """Génère une image à partir d'une image en ligne et d'un prompt texte."""
    image_url = "https://rando-peche.fr/wp-content/uploads/2023/08/peche-a-la-mouche-debutant-1280x853.jpg"
    output = replicate.run(
        "stability-ai/sdxl:39ed52f2a78e934b3ba6e2a89f5b1c712de7dfea535525255b1aa35c5565e08b",
        input={
            "image": image_url,
            "prompt":
            "Here's what's in my hobbies. Can you imagine a new river of mountains with trees like spruce?",
            "width": 1024,
            "height": 1024,
            "guidance_scale": 7.5,
            "negative_prompt": "",
            "num_inference_steps": 25
        })
    output = attendre_completion(output)
    sauvegarder_image(output,
                      r"python_machine_learning\tests\replicate\output3.png")


if __name__ == "__main__":
    generer_image_avec_prompt()
    generer_image_avec_image_locale()
    generer_image_avec_image_en_ligne()
