import os
from dotenv import load_dotenv

# Charger le fichier .env
load_dotenv()


def inject_env_variables_to_md(input_md, output_md):
    """Injecter les variables d'environnement dans un fichier Markdown."""
    with open(input_md, 'r') as file:
        content = file.read()

    # Remplacer les placeholders par les valeurs des variables d'environnement
    for var in os.environ:
        placeholder = f'${{{var}}}'
        value = os.getenv(var, 'VALEUR_NON_DEFINIE')
        content = content.replace(placeholder, value)

    # Écrire le contenu modifié dans le fichier de sortie
    with open(output_md, 'w') as file:
        file.write(content)


# Remplacer les placeholders dans le fichier modop_install.md
inject_env_variables_to_md('install_wordPress_aws.md',
                           'install_wordPress_aws_securise.md')
