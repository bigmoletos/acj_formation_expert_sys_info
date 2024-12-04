import sqlite3

# Connectez-vous à une base SQLCipher et appliquez un mot de passe
conn = sqlite3.connect("file:produits_secure.db?mode=memory&cache=shared",
                       uri=True)
cursor = conn.cursor()

# Activez le chiffrement avec une clé
cursor.execute("PRAGMA key = 'votre_mot_de_pass';")

# Créez une table chiffrée
cursor.execute("""
CREATE TABLE IF NOT EXISTS produits (
    id INTEGER PRIMARY KEY,
    nom TEXT NOT NULL,
    prix REAL NOT NULL
)
""")

# Insérez des données
cursor.execute("INSERT INTO produits (nom, prix) VALUES (?, ?)",
               ("Chaise", 49.99))

conn.commit()
conn.close()
