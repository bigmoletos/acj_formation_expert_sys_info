import os
from dotenv import load_dotenv

# Charger le fichier .env
load_dotenv()


def get_env_variable(var_name, default=None):
    """Récupère la variable d'environnement ou retourne une valeur par défaut."""
    value = os.getenv(var_name)
    if value is None:
        print(
            f"Attention : {var_name} n'est pas définie. Utilisation de la valeur par défaut : {default}"
        )
    return value if value is not None else default


# Informations pour la VM debian (connexion avec mot de passe)
DEBIAN_BDD = {
    'hostname': get_env_variable('DEBIAN_HOSTNAME'),
    'ip': get_env_variable('DEBIAN_IP'),
    'port': int(get_env_variable('DEBIAN_PORT', 22)),
    'username': get_env_variable('DEBIAN_USERNAME', 'vboxuser'),
    'password': get_env_variable('DEBIAN_PASSWORD'),
    'key_file':
    get_env_variable('DEBIAN_KEY_FILE',
                     ''),  # Laisser vide si connexion avec mot de passe
    'port_internet': int(get_env_variable('DEBIAN_PORT_INTERNET', 8080)),
    'name': get_env_variable('DEBIAN_NAME', 'debian'),
}

# Informations pour la VM debian2 (connexion avec mot de passe)
DEBIAN_WEB = {
    'hostname': get_env_variable('DEBIAN2_HOSTNAME'),
    'ip': get_env_variable('DEBIAN2_IP'),
    'port': int(get_env_variable('DEBIAN2_PORT', 22)),
    'username': get_env_variable('DEBIAN2_USERNAME', 'vboxuser'),
    'password': get_env_variable('DEBIAN2_PASSWORD'),
    'key_file':
    get_env_variable('DEBIAN2_KEY_FILE',
                     ''),  # Laisser vide si connexion avec mot de passe
    'port_internet': int(get_env_variable('DEBIAN2_PORT_INTERNET', 8081)),
    'name': get_env_variable('DEBIAN2_NAME', 'debian2'),
}

# Informations pour la VM ubuntu (connexion avec mot de passe)
UBUNTU = {
    'hostname': get_env_variable('UBUNTU_HOSTNAME'),
    'ip': get_env_variable('UBUNTU_IP'),
    'port': int(get_env_variable('UBUNTU_PORT', 22)),
    'username': get_env_variable('UBUNTU_USERNAME', 'vboxuser'),
    'password': get_env_variable('UBUNTU_PASSWORD'),
    'key_file':
    get_env_variable('UBUNTU_KEY_FILE',
                     ''),  # Laisser vide si connexion avec mot de passe
    'port_internet': int(get_env_variable('UBUNTU_PORT_INTERNET', 8082)),
    'name': get_env_variable('UBUNTU_NAME', 'ubuntu'),
}

# Informations pour la VM ubuntu2 (connexion avec mot de passe)
UBUNTU2 = {
    'hostname': get_env_variable('UBUNTU2_HOSTNAME'),
    'ip': get_env_variable('UBUNTU2_IP'),
    'port': int(get_env_variable('UBUNTU2_PORT', 22)),
    'username': get_env_variable('UBUNTU2_USERNAME', 'vboxuser'),
    'password': get_env_variable('UBUNTU2_PASSWORD'),
    'key_file':
    get_env_variable('UBUNTU2_KEY_FILE',
                     ''),  # Laisser vide si connexion avec mot de passe
    'port_internet': int(get_env_variable('UBUNTU2_PORT_INTERNET', 8083)),
    'name': get_env_variable('UBUNTU2_NAME', 'ubuntu2'),
}

# Informations pour la VM kali_linux (connexion avec mot de passe)
KALI_LINUX = {
    'hostname': get_env_variable('KALI_LINUX_HOSTNAME'),
    'ip': get_env_variable('KALI_LINUX_IP'),
    'port': int(get_env_variable('KALI_LINUX_PORT', 22)),
    'username': get_env_variable('KALI_LINUX_USERNAME', 'vboxuser'),
    'password': get_env_variable('KALI_LINUX_PASSWORD'),
    'key_file':
    get_env_variable('KALI_LINUX_KEY_FILE',
                     ''),  # Laisser vide si connexion avec mot de passe
    'port_internet': int(get_env_variable('KALI_LINUX_PORT_INTERNET', 8084)),
    'name': get_env_variable('KALI_LINUX_NAME', 'kali_linux'),
}

# Informations pour la VM kali_linux (connexion avec mot de passe)
KALI_LINUX2 = {
    'hostname': get_env_variable('KALI_LINUX_HOSTNAME'),
    'ip': get_env_variable('KALI_LINUX_IP'),
    'port': int(get_env_variable('KALI_LINUX_PORT', 22)),
    'username': get_env_variable('KALI_LINUX_USERNAME', 'vboxuser'),
    'password': get_env_variable('KALI_LINUX_PASSWORD'),
    'key_file':
    get_env_variable('KALI_LINUX_KEY_FILE',
                     ''),  # Laisser vide si connexion avec mot de passe
    'port_internet': int(get_env_variable('KALI_LINUX_PORT_INTERNET', 8084)),
    'name': get_env_variable('KALI_LINUX_NAME', 'kali_linux'),
}

# Informations pour la VM debian_ajc_aws (connexion avec clé)
DEBIAN_AJC_AWS = {
    'hostname': get_env_variable('DEBIAN_AJC_AWS_HOSTNAME'),
    'ip': get_env_variable('DEBIAN_AJC_AWS_IP'),
    'port': int(get_env_variable('DEBIAN_AJC_AWS_PORT', 22)),
    'username': get_env_variable('DEBIAN_AJC_AWS_USERNAME'),
    'password': get_env_variable('DEBIAN_AJC_AWS_PASSWORD',
                                 ''),  # Laisser vide si connexion avec clé
    'key_file':
    get_env_variable('DEBIAN_AJC_AWS_KEY_FILE'
                     ),  # Chemin vers la clé pour la connexion avec clé
    'port_internet': int(get_env_variable('DEBIAN_AJC_AWS_PORT_INTERNET',
                                          8085)),
    'name': get_env_variable('DEBIAN_AJC_AWS_NAME', 'debian_ajc_aws'),
}
