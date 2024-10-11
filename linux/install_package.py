import paramiko
import logging

# Configurer les logs
logging.basicConfig(level=logging.DEBUG)

def execute_ssh_command(hostname, port, username, password, command):
    """
    Établit une connexion SSH à un hôte distant et exécute une commande.

    :param hostname: Adresse de l'hôte distant
    :param port: Port SSH (généralement 22)
    :param username: Nom d'utilisateur pour la connexion SSH
    :param password: Mot de passe pour la connexion SSH
    :param command: Commande à exécuter sur l'hôte distant

    :return: Sortie de la commande exécutée
    :raises Exception: Si la connexion SSH ou l'exécution de la commande échoue
    """
    ssh_client = paramiko.SSHClient()
    ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

    try:
        # Se connecter au serveur distant
        logging.debug(f"Tentative de connexion à {hostname} sur le port {port} avec l'utilisateur {username}.")
        ssh_client.connect(hostname, port=port, username=username, password=password)
        logging.debug("Connexion SSH établie avec succès.")

        # Exécuter la commande
        logging.debug(f"Exécution de la commande : {command}")
        stdin, stdout, stderr = ssh_client.exec_command(command)

        # Récupérer les résultats de la commande
        output = stdout.read().decode()
        error = stderr.read().decode()

        if error:
            logging.error(f"Erreur lors de l'exécution de la commande : {error}")
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
    # Remplacer par les informations du serveur distant
    HOSTNAME = "votre_serveur_ssh.com"
    PORT = 22
    USERNAME = "votre_utilisateur"
    PASSWORD = "votre_mot_de_passe"
    COMMAND = "ls -l"

    try:
        result = execute_ssh_command(HOSTNAME, PORT, USERNAME, PASSWORD, COMMAND)
        print(result)
    except Exception as e:
        print(f"Erreur : {str(e)}")


