"""Point d'entrée de l'application."""
import logging
from app import create_app

# Configuration du logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

app = create_app()

if __name__ == "__main__":
    try:
        app.run(host='127.0.0.1', port=80000, debug=True)
    except Exception as e:
        logger.error(f"Erreur lors du démarrage du serveur: {str(e)}")
