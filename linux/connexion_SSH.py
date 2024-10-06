import paramiko
import os
import logging
from config import DEBIAN, UBUNTU, KALI_LINUX, DEBIAN2, UBUNTU2, KALI_LINUX2, DEBIAN_AJC_AWS  # Importer les informations de la VM debian2

# Configurer les logs
logging.basicConfig(level=logging.DEBUG)


def execute_ssh_command(vm_config, command):
    """
    Établit une connexion SSH à une machine virtuelle et exécute une commande.

    :param vm_config: Dictionnaire contenant les informations de la machine virtuelle
    :param command: Commande à exécuter sur la machine virtuelle

    :return: Sortie de la commande exécutée
    :raises Exception: Si la connexion SSH ou l'exécution de la commande échoue
    """
    ssh_client = paramiko.SSHClient()
    ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

    try:
        # # Charger la clé privée
        # logging.debug(
        #     f"Chargement de la clé SSH depuis {vm_config['key_file']}.")
        # # private_key = paramiko.RSAKey(filename=vm_config['key_file'])

        # # Se connecter au serveur distant
        # logging.debug(
        #     f"Tentative de connexion à {vm_config['ip']} sur le port {vm_config['port']} avec l'utilisateur {vm_config['username']}."
        # )
        # ssh_client.connect(
        #     hostname=vm_config['ip'],
        #     port=vm_config['port'],
        #     username=vm_config['username'],
        #     password=vm_config[
        #         'password'],  # Utiliser le mot de passe si nécessaire
        #     # pkey=private_key
        # )
        # logging.debug("Connexion SSH établie avec succès.")
        # Vérifier s'il faut utiliser une clé ou un mot de passe
        if vm_config.get('key_file') and os.path.exists(vm_config['key_file']):
            logging.debug(
                f"Connexion avec clé SSH. Chargement de la clé depuis : {vm_config['key_file']}"
            )
            private_key = paramiko.RSAKey(filename=vm_config['key_file'])
            ssh_client.connect(hostname=vm_config['ip'],
                               port=vm_config['port'],
                               username=vm_config['username'],
                               pkey=private_key)
        else:
            # Utiliser le mot de passe
            logging.debug(f"Connexion avec mot de passe à {vm_config['ip']}.")
            ssh_client.connect(hostname=vm_config['ip'],
                               port=vm_config['port'],
                               username=vm_config['username'],
                               password=vm_config['password'])

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
    COMMAND = "ls -l"  # La commande que vous voulez exécuter

    # try:
    #     result = execute_ssh_command(
    #         # DEBIAN_AJC_AWS,
    #         DEBIAN,
    #         # DEBIAN2,
    #         # UBUNTU,
    #         # UBUNTU2,
    #         # KALI_LINUX,
    #         # KALI_LINUX2,
    #         COMMAND)  # Utiliser les infos de la VM debian2
    #     print(result)
    # except Exception as e:
    #     print(f"Erreur : {str(e)}")

    #     COMMAND = "ls -l"  # La commande que vous voulez exécuter

    # Exemple de connexion à une VM Debian sans clé (avec mot de passe)
    try:
        result = execute_ssh_command(
            # DEBIAN_AJC_AWS,
            DEBIAN,
            # DEBIAN2,
            # UBUNTU,
            # UBUNTU2,
            # KALI_LINUX,
            # KALI_LINUX2,
            COMMAND
              )  # Utiliser la configuration de la VM Debian
        print("Résultat de la connexion sans clé :")
        print(result)
    except Exception as e:
        print(f"Erreur : {str(e)}")

    # Exemple de connexion à une VM AWS avec clé
    # try:
    #     result = execute_ssh_command(
    #         DEBIAN_AJC_AWS, COMMAND)  # Utiliser la configuration de la VM AWS
    #     print("Résultat de la connexion avec clé :")
    #     print(result)
    # except Exception as e:
    #     print(f"Erreur : {str(e)}")
