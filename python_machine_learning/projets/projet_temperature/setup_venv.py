import os
import subprocess
import sys
import logging

# Configuration du logging
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s - %(levelname)s - %(message)s')

# Nom de l'environnement virtuel
VENV_NAME = "venv"


def log(message):
    logging.info(message)


def success(message):
    logging.info(f"\033[0;32m{message}\033[0m")  # Texte en vert


def error(message):
    logging.error(f"\033[0;31m{message}\033[0m")  # Texte en rouge
    sys.exit(1)


def check_python():
    log("Vérification de l'installation Python...")
    try:
        subprocess.run(["python", "--version"], check=True)
        success("Python est installé")
    except subprocess.CalledProcessError:
        error("Python n'est pas installé. Veuillez l'installer d'abord.")


def create_venv():
    log("Création de l'environnement virtuel...")
    if os.path.exists(VENV_NAME):
        log("L'environnement virtuel existe déjà")
    else:
        try:
            subprocess.run(["python", "-m", "venv", VENV_NAME], check=True)
            success("Environnement virtuel créé avec succès")
        except subprocess.CalledProcessError:
            error("Erreur lors de la création de l'environnement virtuel")


def activate_venv():
    log("Activation de l'environnement virtuel...")
    log(f"VENV_NAME: {VENV_NAME}  nom de l'os {os.name}")
    log(f"script activate: {os.path.join(".",
        VENV_NAME, "Scripts", "activate")}")
    activate_script = os.path.join(".",
        VENV_NAME, "Scripts", "activate") if os.name == 'nt' else os.path.join(
            VENV_NAME, "bin", "activate")
    log(f"activate_script: {activate_script}")
    try:
        # subprocess.run(["bash", "-c", f"source {activate_script}"], check=True)
        # subprocess.run(f" {activate_script}")
        if os.name == 'nt':
            log(f"{activate_script} (Windows)")  # Pas de 'source' sur Windows
        else:
            log(f"source{activate_script} (Linux/Mac)")  # 'source' pour Linux/Mac avec './'

        success("Environnement virtuel activé")
    except subprocess.CalledProcessError:
        error("Erreur lors de l'activation de l'environnement virtuel")


def install_requirements():
    log("Installation des dépendances...")
    try:
        subprocess.run(["python", "-m", "pip", "install", "--upgrade", "pip"],
                       check=True)
        subprocess.run(["pip", "install", "-r", "requirements.txt"],
                       check=True)
        success("Dépendances installées avec succès")
    except subprocess.CalledProcessError:
        error("Erreur lors de l'installation des dépendances")


def run_tests():
    log("Lancement des tests...")
    try:
        subprocess.run(["python", "-m", "pytest", "tests/", "-v"], check=True)
        success("Tests terminés avec succès")
    except subprocess.CalledProcessError:
        error("Erreur lors de l'exécution des tests")


def main():
    log("Démarrage de la configuration de l'environnement...")
    check_python()
    create_venv()
    activate_venv()
    install_requirements()
    run_tests()
    success("Configuration terminée avec succès!")
    log("Pour activer l'environnement manuellement, exécutez :")
    log(f"source {VENV_NAME}/Scripts/activate (Windows)")
    log(f"source {VENV_NAME}/bin/activate (Linux/Mac)")


if __name__ == "__main__":
    main()
