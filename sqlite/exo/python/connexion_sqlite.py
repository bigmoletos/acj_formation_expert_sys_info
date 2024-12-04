import sqlite3

# Ouvrir une connexion à la base de données
conn = sqlite3.connect(r'sqlite\exo\python\test.db')

# Créer un curseur pour exécuter des requêtes SQL
cursor = conn.cursor()

# Simulation de USE DATABASE (non nécessaire pour SQLite, mais pour la cohérence)
# SQLite utilise un fichier de base de données unique, donc pas de commande USE

# Création de la table clients
cursor.execute("""
CREATE TABLE IF NOT EXISTS clients (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL,
    email TEXT
)
""")

# Création de la table produits
cursor.execute("""
CREATE TABLE IF NOT EXISTS produits (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL,
    prix REAL NOT NULL
)
""")

# Création de la table commandes
cursor.execute("""
CREATE TABLE IF NOT EXISTS commandes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    client_id INTEGER,
    produit_id INTEGER,
    quantite INTEGER,
    FOREIGN KEY (client_id) REFERENCES clients(id),
    FOREIGN KEY (produit_id) REFERENCES produits(id)
)
""")

# Insertion de données dans la table clients avec IGNORE pour éviter les doublons
cursor.execute("""
INSERT OR IGNORE INTO clients (nom, email) VALUES
    ('Romain', 'romain@example.com'),
    ('John', 'john@example.com'),
    ('Jane', 'jane@example.com'),
    ('Alice', 'alice@example.com')
""")

# Insertion de données dans la table commandes
cursor.execute("""
INSERT OR IGNORE INTO commandes (client_id, produit_id, quantite) VALUES (
    (SELECT id FROM clients WHERE nom = 'Romain'),
    (SELECT id FROM produits WHERE nom = 'Chaise'),
    2
)
""")

# insertion de données dans la table produits
cursor.execute("""
INSERT OR IGNORE INTO produits (nom, prix) VALUES
               ('Chaise', 100.0),
               ('Table', 200.0),
               ('Armoire', 300.0),
 ('Tableau', 20.0)

""")
#  autre possibilite enpassant par une liste
liste_produits = [('stylo', 100.0), ('papaier', 200.0), ('clavier', 300.0),
                  ('lette', 20.0)]

# insertion de données dans la table produits
cursor.executemany("INSERT OR IGNORE INTO produits (nom, prix) VALUES (?,?)",
                   liste_produits)

# Exécuter une requête SQL
print("liste des clients")
cursor.execute("SELECT * FROM clients ORDER BY nom")
#  liste des produits
print("liste des produits")
cursor.execute("SELECT * FROM produits ORDER BY nom")

# Récupérer les résultats
results = cursor.fetchall()
print(results)

# Fermer la connexion
conn.close()
