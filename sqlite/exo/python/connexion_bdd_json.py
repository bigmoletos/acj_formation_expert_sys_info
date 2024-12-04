import json
import sqlite3

# Charger le fichier JSON
with open(r'sqlite\exo\python\database-client-config.json', 'r') as file:
    data = json.load(file)

# Extraire le chemin de la base de données
db_path = data['database']['1733319295700']['dbPath']

# Se connecter à la base de données SQLite
conn = sqlite3.connect(db_path)
cursor = conn.cursor()

# Exemple : Lire les tables de la base de données
cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
tables = cursor.fetchall()

print("Tables in the database:", tables)

# Fermer la connexion
conn.close()
