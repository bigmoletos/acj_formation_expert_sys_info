import os
import re


def add_doxygen_to_file(filepath):
    """
    Ajoute des commentaires Doxygen aux fonctions présentes dans un fichier.

    Args:
        filepath (str): Chemin du fichier à traiter.

    Returns:
        None
    """
    try:
        with open(filepath, 'r') as file:
            lines = file.readlines()

        output_lines = []  # Contient les lignes finales du fichier
        inside_comment_block = False  # Indique si on est à l'intérieur d'un bloc de commentaire
        modified = False  # Indique si des modifications ont été effectuées

        for i, line in enumerate(lines):
            # Vérifier si la ligne actuelle est le début ou l'intérieur d'un bloc de commentaire
            if re.match(r'^\s*/\*\*', line):  # Début d'un bloc de commentaire
                inside_comment_block = True
            elif inside_comment_block and re.match(r'^\s*\*/', line):  # Fin d'un bloc
                inside_comment_block = False

            # Si on est dans un bloc de commentaire, ne pas ajouter de nouveaux commentaires
            if inside_comment_block:
                output_lines.append(line)
                continue

            # Détecter les fonctions dans les fichiers .hpp et .cpp
            match_function = re.match(
                r'^\s*(\w[\w\s\*&:<>]+)\s+(\w+)\((.*)\)\s*([;{]?)\s*$', line)
            if match_function:
                return_type, func_name, params, ending = match_function.groups(
                )

                # Vérifier si un commentaire Doxygen est déjà présent au-dessus
                if i > 0 and re.match(r'^\s*/\*\*', lines[i - 1]):
                    output_lines.append(line)
                    continue

                # Ajouter un bloc de documentation Doxygen au-dessus de la fonction
                output_lines.append(f"/**\n")
                output_lines.append(
                    f" * @brief [Description de {func_name}]\n")
                output_lines.append(f" *\n")
                if params.strip():
                    # Ajouter les paramètres
                    for param in params.split(','):
                        param_name = param.strip().split()[-1]
                        output_lines.append(
                            f" * @param {param_name} [Description du paramètre]\n"
                        )
                else:
                    output_lines.append(
                        f" * @param Aucun [Cette fonction n'a pas de paramètres]\n"
                    )
                output_lines.append(
                    f" * @return {return_type.strip()} [Description du retour]\n"
                )
                output_lines.append(f" */\n")

                modified = True

            # Ajouter la ligne originale
            output_lines.append(line)

        # Écrire les modifications uniquement si nécessaire
        if modified:
            print(f"Modification appliquée à : {filepath}")
            with open(filepath, 'w') as file:
                file.writelines(output_lines)
        else:
            print(f"Aucune modification pour : {filepath}")

    except Exception as e:
        print(f"Erreur dans le fichier {filepath} : {e}")


def process_directory(directory):
    """
    Parcourt récursivement tous les fichiers d'un répertoire et traite chaque fichier.

    Args:
        directory (str): Chemin du répertoire à analyser.

    Returns:
        None
    """
    for root, dirs, files in os.walk(directory):
        # Ne pas limiter les sous-dossiers ici
        for file in files:
            # Vérifier les extensions des fichiers pris en charge
            if file.endswith(('.c', '.cpp', '.h', '.hpp', '.py')):
                filepath = os.path.join(root, file)
                try:
                    print(f"Traitement du fichier : {filepath}")
                    add_doxygen_to_file(filepath)
                except Exception as e:
                    print(f"Erreur lors du traitement de {filepath} : {e}")


if __name__ == "__main__":
    """
    Point d'entrée principal du script.

    Définit le chemin du projet comme le répertoire courant et lance la fonction
    `process_directory` pour parcourir les fichiers et ajouter les commentaires Doxygen.
    """
    # Utiliser le répertoire courant
    project_path = os.path.abspath(os.getcwd())
    print(f"Analyse du répertoire : {project_path}")

    # Parcourir tous les fichiers et sous-dossiers
    process_directory(project_path)
