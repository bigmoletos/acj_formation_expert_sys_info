-- Ouvrir la base de données
.open test.db

-- Créez une table demo
CREATE TABLE IF NOT EXISTS demo (id INTEGER PRIMARY KEY, name TEXT);

-- Créez une table utilisateurs
CREATE TABLE IF NOT EXISTS utilisateurs (
id INTEGER PRIMARY KEY ,
nom TEXT NOT NULL ,
email TEXT
);

-- Créez une table produits
CREATE TABLE IF NOT EXISTS produits (
id INTEGER PRIMARY KEY ,
nom TEXT NOT NULL ,
prix REAL NOT NULL ,
stock INTEGER DEFAULT 0,
UNIQUE(nom)
);

-- Créez une table commandes
CREATE TABLE IF NOT EXISTS commandes (
id INTEGER PRIMARY KEY ,
client_id INTEGER ,
produit TEXT NOT NULL ,
quantite INTEGER NOT NULL ,
FOREIGN KEY (client_id) REFERENCES clients(id)
);

-- Créez une table clients
CREATE TABLE IF NOT EXISTS clients (
id INTEGER PRIMARY KEY ,
nom TEXT NOT NULL ,
email TEXT UNIQUE
);

-- Insérer des données dans la table utilisateurs
INSERT OR IGNORE INTO utilisateurs (nom , email) VALUES ('Alice ', 'alice@example.com');
INSERT OR IGNORE INTO utilisateurs (nom , email) VALUES ('Bob', 'bob@example.com');

-- afficher les données de la table utilisateurs
SELECT * FROM utilisateurs;

-- Ajouter une colonne age à la table utilisateurs
ALTER TABLE utilisateurs ADD COLUMN age INTEGER CHECK (age >= 0 AND age <= 150);

-- afficher les données de la table utilisateurs avec l'age > 25
SELECT * FROM utilisateurs
WHERE age > 25
  AND age IS NOT NULL;


-- Insérer des données dans la table produits
INSERT OR IGNORE INTO produits (nom , prix , stock) VALUES ('Chaise ', 49.99 , 10);
-- Insérer des données dans la table produits
INSERT OR IGNORE INTO produits (nom , prix , stock) VALUES
('Table ', 89.99 , 5),
('Lampadaire ', 29.99 , 15);


INSERT OR IGNORE INTO clients (nom , email) VALUES
('Alice ', 'alice@example.com'),
('Bob', 'bob@example.com');
-- Ajoutez des commandes :
INSERT OR IGNORE INTO commandes (client_id , produit , quantite) VALUES
(1, 'Chaise ', 2),
(1, 'Table ', 1),
(2, 'Lampadaire ', 3);
-- afficher les données de la table produits
SELECT * FROM produits;

-- afficher les données de la table produits avec le stock > 5
SELECT nom , prix FROM produits WHERE stock > 5;

-- afficher les données de la table produits triées par prix ascendant et limité à 3
SELECT * FROM produits ORDER BY prix ASC LIMIT 3;

-- afficher les données de la table commandes
SELECT * FROM commandes;

-- afficher les données de la table clients
SELECT * FROM clients;

-- afficher les données de la table commandes avec le nom de client
SELECT c.nom , cmd.produit , cmd.quantite
FROM clients c
JOIN commandes cmd ON c.id = cmd.client_id
WHERE c.nom = 'Alice ';

-- mettre à jour le stock de la table produits
UPDATE produits SET stock = stock - 2 WHERE nom = 'Chaise ';

-- supprimer une commande de la table commandes
DELETE FROM commandes WHERE id = 1;

-- afficher les données de la table commandes avec le total vendu par produit
SELECT produit , SUM(quantite) as total_vendu
FROM commandes
GROUP BY produit
ORDER BY total_vendu DESC;

-- mettre à jour le stock de la table produits
UPDATE produits SET stock = stock - 2 WHERE nom = 'Chaise ';

-- supprimer une commande de la table commandes
DELETE FROM commandes WHERE id = 2;

-- activer les clés étrangères
PRAGMA foreign_keys = ON;

-- mettre à jour le stock de la table produits
UPDATE produits SET stock = stock - 1 WHERE nom = 'Table ';

-- supprimer une commande de la table commandes
DELETE FROM commandes WHERE id = 3;

-- Ajouter une clé étrangère
ALTER TABLE commandes ADD COLUMN client_id INTEGER;

-- Ajoutez la contrainte :
CREATE TABLE commandes_nouvelle (
id INTEGER PRIMARY KEY ,
client_id INTEGER ,
produit TEXT NOT NULL ,
quantite INTEGER NOT NULL ,
FOREIGN KEY (client_id) REFERENCES clients(id)
);

-- Tester l’intégrité relationnelle :
INSERT INTO commandes (client_id , produit , quantite) VALUES (99, '
Chaise ', 1);

-- Supprimer des clients et voir l’impact sur les commandes :
DELETE FROM clients WHERE id = 1;
-- Mettre à jour une relation :
UPDATE commandes SET client_id = 2 WHERE id = 1;


-- COUNT : Compte le nombre de lignes.
SELECT COUNT (*) FROM commandes;
-- SUM : Calcule le total.
SELECT SUM(quantite) FROM commandes;
-- AVG : Calcule la moyenne.
SELECT AVG(prix) FROM produits;
-- MIN/MAX : Trouve la valeur minimale ou maximale.
SELECT MIN(prix), MAX(prix) FROM produits;


-- BEGIN : Démarrer une transaction.
-- COMMIT : Valider les modifications.
-- ROLLBACK : Annuler les modifications en cas de problème.
-- Exemple :
BEGIN;
UPDATE produits SET stock = stock - 1 WHERE nom = 'Chaise ';
 -- Annule l'opération
ROLLBACK;
-- Valide l'opération
COMMIT;

-- Accélérer vos requêtes avec des index
-- Un index améliore la vitesse de recherche dans une table.
-- Syntaxe :
CREATE INDEX idx_nom ON produits (nom);
-- Vérifier l’utilisation d’un index :
EXPLAIN QUERY PLAN SELECT * FROM produits WHERE nom = 'Table ';


-- Exercice pratique : Créer et utiliser un index Objectif : Créer un index pour optimiser
-- une recherche.
-- 1 Créer un index sur la table produits :
CREATE INDEX idx_nom_produits ON produits (nom);
-- 2 Effectuer une recherche optimisée :
SELECT * FROM produits WHERE nom = 'Table ';
-- 3 Analyser le plan d’exécution :
EXPLAIN QUERY PLAN SELECT * FROM produits WHERE nom = 'Table ';


-- Titre : Intégration avec Python : module sqlite3
-- 1 Connexion à une base de données :
import sqlite3
conn = sqlite3.connect('ma_base.db')
cursor = conn.cursor ()
-- 2 Exécuter des requêtes :
cursor.execute("CREATE TABLE IF NOT EXISTS produits (id INTEGER PRIMARY KEY , nom TEXT , prix REAL)")

-- Insérer et lire des données :
cursor.execute("INSERT INTO produits (nom , prix) VALUES ('Chaise ', 49.99)")
conn.commit ()
cursor.execute("SELECT * FROM produits")
print(cursor.fetchall ())


-- Utiliser SQLite avec PHP
-- Titre : Intégration avec PHP
-- 1 Connexion à une base SQLite :
$db = new SQLite3('ma_base.db');
-- 2 Exécuter des requêtes :
$db ->exec("CREATE TABLE IF NOT EXISTS produits (id INTEGER PRIMARY KEY , nom TEXT , prix REAL)");
-- insérer des données
$db ->exec("INSERT INTO produits (nom , prix) VALUES ('Table ', 89.99)");
-- 3 Lire les données :
$result = $db ->query("SELECT * FROM produits");
-- afficher les données
while ($row = $result ->fetchArray ()) {echo $row['nom'] . " - " . $row['prix'] . "\n";}

-- Exporter et importer des données
-- Titre : Échanger des données avec SQLite
-- Exporter vers CSV :
.headers ON
.mode csv
.output produits.csv
SELECT * FROM produits;
.output stdout
-- Importer un fichier CSV :
.mode csv
.import produits.csv produits
-- Exporter/importer en SQL :
sqlite3 ma_base.db .dump > sauvegarde.sql
sqlite3 ma_base.db < sauvegarde.sql


-- Concepts de sécurité de base
-- Titre : Protéger vos données
-- Chiffrer les données sensibles : Utiliser des bibliothèques comme SQLCipher.
-- Limiter les accès :
-- Contrôler qui peut lire ou écrire dans le fichier SQLite.
-- Configurer les permissions système.
-- Valider les entrées :
cursor.execute("INSERT INTO produits (nom , prix) VALUES (?, ?)", ('Chaise ', 49.99))

-- Exercice : Script Python pour SQLite
-- Titre : Exercice pratique : Connecter SQLite avec Python Objectif : Écrire un script Python
-- pour manipuler une base SQLite.
-- 1 import sqlite3

conn = sqlite3.connect('ma_base.db')
cursor = conn.cursor ()

cursor.execute("CREATE TABLE IF NOT EXISTS produits (id INTEGER PRIMARY
KEY , nom TEXT , prix REAL)")
cursor.execute("INSERT INTO produits (nom , prix) VALUES (?, ?)", ('
Chaise ', 49.99))

conn.commit ()
cursor.execute("SELECT * FROM produits")
print(cursor.fetchall ())
conn.close ()

-- Exercice : Importer et exporter des données
-- Titre : Exercice pratique : Importer et exporter des fichiers Objectif : Tester l’importation et
-- l’exportation de données avec SQLite.
-- 1 Exporter vos données actuelles en CSV :
.headers ON
.mode csv
.output produits.csv
SELECT * FROM produits;
-- Importer un fichier CSV existant :
.mode csv
.import nouveaux_produits.csv produits
-- Exporter en SQL :
sqlite3 ma_base.db .dump > sauvegarde.sql


-- Gestion des erreurs courantes
-- Titre : Identifier et résoudre les erreurs
-- 1 Fichier SQLite verrouillé :
-- Cause : Accès simultané non géré.
-- Solution :
PRAGMA busy_timeout = 3000;
-- 2 Violation de contrainte (UNIQUE, FOREIGN KEY) :
-- Cause : Données non conformes aux règles définies.
-- Solution : Vérifiez les données avant insertion.
-- 3 Erreur de syntaxe SQL :
-- Cause : Requête mal écrite.
-- Solution : Utilisez .schema pour valider la structure de la table et corrigez la requête.

-- Bonnes pratiques pour SQLite
-- Titre : Optimiser votre usage de SQLite
-- 1 Structuration des bases :
-- Utilisez des noms explicites pour les tables et colonnes.
-- Normalisez vos données pour éviter les redondances.
-- 2 Sauvegarde des données :
sqlite3 ma_base.db .dump > sauvegarde.sql
-- 3 Performances :
CREATE INDEX idx_nom ON produits (nom);


-- Solution suggérée pour le projet fictif
-- Titre : Proposition de structure et requêtes Structure suggérée :
Table clients :
CREATE TABLE clients (
id INTEGER PRIMARY KEY ,
nom TEXT ,
email TEXT
);
Table produits :
CREATE TABLE produits (
id INTEGER PRIMARY KEY ,
nom TEXT ,
prix REAL ,
stock INTEGER
);

-- Table commandes :
CREATE TABLE commandes (
id INTEGER PRIMARY KEY ,
client_id INTEGER ,
produit_id INTEGER ,
quantite INTEGER ,
FOREIGN KEY (client_id) REFERENCES clients(id),
FOREIGN KEY (produit_id) REFERENCES produits(id)
);


-- Deuxième étape : Construisez la base SQLite Objectif : Créer votre base de données
-- avec les tables définies.
-- Exemple pour un inventaire :
CREATE TABLE produits (
id INTEGER PRIMARY KEY ,
nom TEXT NOT NULL ,
stock INTEGER DEFAULT 0,
prix REAL NOT NULL
);
CREATE TABLE categories (id INTEGER PRIMARY KEY ,nom TEXT NOT NULL );
ALTER TABLE produits ADD COLUMN categorie_id INTEGER;
FOREIGN KEY (categorie_id) REFERENCES categories(id);


-- Exercice : Créer un programme Python
-- Titre : Troisième étape : Programmez une interface Python Objectif : Connecter Python à
-- votre base et implémenter des actions courantes.
import sqlite3

conn = sqlite3.connect('mon_projet.db')
cursor = conn.cursor ()

cursor.execute("INSERT INTO produits (nom , stock , prix) VALUES (?, ?, ?) ", ('Table ', 10, 79.99))
conn.commit ()

cursor.execute("SELECT * FROM produits")
for row in cursor.fetchall ():
 print(row)
conn.close ()

-- Mise à jour des âges des utilisateurs
UPDATE utilisateurs SET age = 30 WHERE nom = 'Alice ';
UPDATE utilisateurs SET age = 35 WHERE nom = 'Bob';


