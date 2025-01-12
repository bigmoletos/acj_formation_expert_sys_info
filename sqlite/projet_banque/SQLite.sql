-- SQLite
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
ALTER TABLE utilisateurs ADD COLUMN age INTEGER;

-- afficher les données de la table utilisateurs avec l'age > 25
SELECT * FROM utilisateurs WHERE age > 25;


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