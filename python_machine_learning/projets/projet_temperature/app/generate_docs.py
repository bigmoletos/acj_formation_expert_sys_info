import os
import subprocess
import logging
from flask import current_app

logger = logging.getLogger(__name__)


def generate_documentation():
    """Génère la documentation avec Doxygen"""
    try:
        # Vérifier si Doxygen est installé
        subprocess.run(['doxygen', '--version'], check=True)

        # Créer le dossier de documentation s'il n'existe pas
        docs_dir = os.path.join(current_app.root_path, 'statics', 'docs')
        os.makedirs(docs_dir, exist_ok=True)

        # Générer la documentation
        result = subprocess.run(['doxygen', 'Doxyfile'],
                                capture_output=True,
                                text=True)

        if result.returncode == 0:
            logger.info("Documentation générée avec succès")
            return True
        else:
            logger.error(f"Erreur lors de la génération: {result.stderr}")
            return False

    except FileNotFoundError:
        logger.error("Doxygen n'est pas installé")
        return False
    except Exception as e:
        logger.error(f"Erreur inattendue: {str(e)}")
        return False


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    generate_documentation()
