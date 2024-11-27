# from kagglehub
# from kagglehub import Api
import subprocess
import pandas as pd

# Initialiser l'API avec votre clé
# api = Api(api_key_path="~/.kaggle/kaggle.json")

# # Obtenir une liste de datasets
# datasets = api.datasets_list(search="iris")

# print("Liste des datasets trouvés :")
# for dataset in datasets[:5]:  # Afficher les 5 premiers
#     print(f"Référence : {dataset['ref']}")
#     print(f"Titre : {dataset['title']}")
#     print(f"Taille : {dataset['size']} Mo")
#     print(f"Téléchargements : {dataset['downloadCount']}")
#     print()

# echo "aggle datasets list"

# Commande à exécuter
command = ["kaggle", "datasets", "list"]

# Exécuter la commande et capturer le résultat
try:
    result = subprocess.run(command,
                            capture_output=True,
                            text=True,
                            check=True)

    # Sauvegarder le résultat dans un fichier CSV
    output_lines = result.stdout.splitlines()

    # Extraire les colonnes et les données
    columns = output_lines[0].split()  # Première ligne : colonnes
    data = [line.split(maxsplit=len(columns) - 1) for line in output_lines[1:]]

    # Créer un DataFrame pandas
    df = pd.DataFrame(data, columns=columns)

    # Sauvegarder le DataFrame dans un fichier CSV
    csv_file = "..//data//csv//dataset_kaggle.csv"
    # csv_file = "dataset_kaggle.csv"
    df.to_csv(csv_file, index=False)

    print(f"Résultats sauvegardés dans {csv_file}")
    print("Aperçu du DataFrame :")
    print(df.head())

except subprocess.CalledProcessError as e:
    print(f"Erreur lors de l'exécution de la commande : {e}")
    print(e.stderr)  # Afficher les détails de l'erreur
