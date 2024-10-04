import paramiko


def sftp_transfer(hostname, port, username, password, local_file, remote_file):
    """
    Transfère un fichier local vers un hôte distant via SFTP.

    :param hostname: Adresse de l'hôte distant
    :param port: Port SSH (généralement 22)
    :param username: Nom d'utilisateur pour la connexion SSH
    :param password: Mot de passe pour la connexion SSH
    :param local_file: Chemin du fichier local à transférer
    :param remote_file: Chemin de destination sur l'hôte distant
    """
    transport = paramiko.Transport((hostname, port))

    try:
        # Se connecter au serveur distant
        transport.connect(username=username, password=password)
        sftp = paramiko.SFTPClient.from_transport(transport)

        # Transférer le fichier
        sftp.put(local_file, remote_file)
        print(f"Fichier {local_file} transféré vers {remote_file}")

    except Exception as e:
        print(f"Erreur lors du transfert SFTP : {str(e)}")

    finally:
        # Fermer la connexion SFTP
        transport.close()


if __name__ == "__main__":
    HOSTNAME = "votre_serveur_ssh.com"
    PORT = 22
    USERNAME = "votre_utilisateur"
    PASSWORD = "votre_mot_de_passe"
    LOCAL_FILE = "chemin/vers/le/fichier/local.txt"
    REMOTE_FILE = "/chemin/vers/le/fichier/distant.txt"

    sftp_transfer(HOSTNAME, PORT, USERNAME, PASSWORD, LOCAL_FILE, REMOTE_FILE)
