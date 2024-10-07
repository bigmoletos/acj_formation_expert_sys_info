import os
import logging
from dotenv import load_dotenv

# Créer une instance de logger nommée 'vm_injector'
logger = logging.getLogger('vm_injector')
logger.setLevel(logging.DEBUG)

# Configurer le gestionnaire de fichiers pour enregistrer les logs dans 'vm_injection.log'
file_handler = logging.FileHandler('vm_injection.log')
file_handler.setLevel(logging.DEBUG)

# Configurer le gestionnaire de flux pour afficher les logs dans la console
stream_handler = logging.StreamHandler()
stream_handler.setLevel(logging.DEBUG)

# Définir le format des logs
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
file_handler.setFormatter(formatter)
stream_handler.setFormatter(formatter)

# Ajouter les gestionnaires au logger
logger.addHandler(file_handler)
logger.addHandler(stream_handler)

# Charger le fichier .env
load_dotenv()

def inject_env_variables_for_vms(input_md, output_md, vm1, vm2):
    """Injecter les variables d'environnement pour deux VMs dans un fichier Markdown."""
    logger.info(f"Début de l'injection des variables pour les VMs: {vm1} et {vm2}")
    try:
        with open(input_md, 'r') as file:
            content = file.read()
        logger.debug(f"Contenu du fichier {input_md} chargé avec succès.")
    except FileNotFoundError:
        logger.error(f"Le fichier {input_md} n'a pas été trouvé.")
        return
    except Exception as e:
        logger.error(f"Erreur lors de la lecture du fichier {input_md}: {e}")
        return

    # Liste des suffixes de variables à injecter
    vm_vars = ['name', 'root', 'password', 'user']

    # Remplacer les placeholders pour les deux VMs
    for vm in [vm1, vm2]:
        for var in vm_vars:
            # Construire le nom de la variable d'environnement (ex : DEBIAN_BDD_name)
            env_var_name = f'{vm}_BDD_{var}'
            placeholder = f'${{{var}}}'  # Placeholder dans le .md, ex : ${name}

            # Récupérer la valeur de la variable d'environnement
            value = os.getenv(env_var_name, 'VALEUR_NON_DEFINIE')

            # Log si une variable n'est pas définie
            if value == 'VALEUR_NON_DEFINIE':
                logger.warning(f"La variable d'environnement {env_var_name} n'est pas définie.")

            # Log de débogage pour chaque remplacement de placeholder
            logger.debug(f"Remplacement du placeholder {placeholder} par {value}.")
            content = content.replace(placeholder, value)

    # Écrire le contenu modifié dans le fichier de sortie
    try:
        with open(output_md, 'w') as file:
            file.write(content)
        logger.info(f"Les variables ont été injectées avec succès dans le fichier {output_md}.")
    except Exception as e:
        logger.error(f"Erreur lors de l'écriture dans le fichier {output_md}: {e}")

# Exemple d'utilisation pour sélectionner deux VMs
vm_bdd = 'DEBIAN'  # Le préfixe pour les variables d'environnement, ex : DEBIAN_BDD_
vm_web = 'DEBIAN_WEB'

nom_fichier_md = 'linux\\install_wordPress_aws.md'

# Obtenir le nom du fichier sans l'extension et ajouter '_securiser.md'
nom_fichier_sans_ext = os.path.splitext(nom_fichier_md)[0]
nom_fichier_securise = nom_fichier_sans_ext + '_securised.md'

# Remplacer les placeholders dans le fichier modop_install.md
inject_env_variables_for_vms(nom_fichier_md, nom_fichier_securise, vm_bdd, vm_web)


# # Liste des variables à injecter pour chaque VM
# vm_vars = [
#     'BDD_HOSTNAME', 'BDD_IP', 'BDD_PORT', 'BDD_USERNAME', 'BDD_PASSWORD',
#     'BDD_KEY_FILE', 'BDD_PORT_INTERNET', 'BDD_NAME'
# ]