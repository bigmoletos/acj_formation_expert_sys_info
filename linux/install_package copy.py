import paramiko
import configparser
import logging

# Configurer les logs
logging.basicConfig(level=logging.DEBUG)


def load_config(config_file):
    """
    Charger la configuration à partir d'un fichier ini.

    :param config_file: Chemin du fichier de configuration
    :return: Dictionnaire contenant les informations de configuration
    """
    config = configparser.ConfigParser()
    config.read(config_file)
    return {
        'hostname': config['ssh']['hostname'],
        'port': int(config['ssh']['port']),
        'username': config['ssh']['username'],
        'key_file': config['ssh']['key_file']
    }


def execute_ssh_command(config_file, command):
    """
    Établit une connexion SSH à un hôte distant et exécute une commande.

    :param config_file: Chemin du fichier de configuration
    :param command: Commande à exécuter sur l'hôte distant

    :return: Sortie de la commande exécutée
    :raises Exception: Si la connexion SSH ou l'exécution de la commande échoue
    """
    config = load_config(config_file)
    ssh_client = paramiko.SSHClient()
    ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

    try:
        # Charger la clé privée
        logging.debug(f"Chargement de la clé SSH depuis {config['key_file']}.")
        private_key = paramiko.RSAKey(filename=config['key_file'])

        # Se connecter au serveur distant
        logging.debug(
            f"Tentative de connexion à {config['hostname']} sur le port {config['port']} avec l'utilisateur {config['username']}."
        )
        ssh_client.connect(hostname=config['hostname'],
                           port=config['port'],
                           username=config['username'],
                           pkey=private_key)
        logging.debug("Connexion SSH établie avec succès.")

        # Exécuter la commande
        logging.debug(f"Exécution de la commande : {command}")
        stdin, stdout, stderr = ssh_client.exec_command(command)

        # Récupérer les résultats de la commande
        output = stdout.read().decode()
        error = stderr.read().decode()

        if error:
            logging.error(
                f"Erreur lors de l'exécution de la commande : {error}")
            raise Exception(f"Erreur SSH : {error}")

        logging.debug(f"Sortie de la commande : {output}")
        return output

    except Exception as e:
        logging.error(f"Une erreur s'est produite : {str(e)}")
        raise

    finally:
        # Fermer la connexion SSH
        logging.debug("Fermeture de la connexion SSH.")
        ssh_client.close()


if __name__ == "__main__":
    CONFIG_FILE = 'config.ini'
    COMMAND = "ls -l"

    try:
        result = execute_ssh_command(CONFIG_FILE, COMMAND)
        print(result)
    except Exception as e:
        print(f"Erreur : {str(e)}")
