import os
from dotenv import load_dotenv

# Charger le fichier .env
load_dotenv()

# Lire les valeurs
login = os.getenv('NOM_UTILISATEUR')
password = os.getenv('MOT_DE_PASSE')

# Lire et remplacer les placeholders dans le fichier markdown
with open('modop_install.md', 'r') as file:
    content = file.read()
    content = content.replace('${NOM_UTILISATEUR}', login)
    content = content.replace('${MOT_DE_PASSE}', password)

# Écrire le nouveau contenu dans un fichier sécurisé
with open('modop_install_securise.md', 'w') as file:
    file.write(content)
