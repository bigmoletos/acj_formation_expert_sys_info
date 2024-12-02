from app import create_app, db
from app.models import User
import logging

logger = logging.getLogger(__name__)

app = create_app()


def init_db():
    """Initialise la base de données avec les données de test"""
    try:
        with app.app_context():
            # Vérifier si l'utilisateur de test existe déjà
            if not User.query.filter_by(username='test').first():
                user = User(username='test')
                user.set_password('test123')
                db.session.add(user)
                db.session.commit()
                logger.info("Utilisateur de test créé avec succès")
            else:
                logger.info("L'utilisateur de test existe déjà")

            print("Base de données initialisée avec succès!")

    except Exception as e:
        logger.error(
            f"Erreur lors de l'initialisation de la base de données: {str(e)}")
        raise


if __name__ == '__main__':
    init_db()
