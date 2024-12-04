
# Cheatsheet SQLite pour Flask et Django

## Installation de SQLite
SQLite est intégré avec Python, mais vous pouvez installer `sqlite3` si ce n'est pas encore fait.
```bash
pip install sqlite3
```

---

## SQLite avec Flask

### Exemple : Configuration de SQLite dans Flask
```python
from flask import Flask, g
import sqlite3

app = Flask(__name__)
DATABASE = 'database.db'

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
    return db

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

@app.route('/')
def index():
    cur = get_db().cursor()
    cur.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT)')
    cur.execute('INSERT INTO users (name) VALUES (?)', ("Alice",))
    get_db().commit()
    return "Table and data initialized!"
```

### Exemple : Lecture des données
```python
@app.route('/users')
def users():
    cur = get_db().cursor()
    cur.execute('SELECT * FROM users')
    users = cur.fetchall()
    return {'users': users}
```

---

## SQLite avec Django

### Exemple : Configuration de SQLite dans Django
Dans `settings.py` :
```python
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.sqlite3',
        'NAME': BASE_DIR / 'db.sqlite3',
    }
}
```

### Exemple : Modèle simple
Dans `models.py` :
```python
from django.db import models

class User(models.Model):
    name = models.CharField(max_length=100)

    def __str__(self):
        return self.name
```

### Exemple : Migrer la base de données
```bash
python manage.py makemigrations
python manage.py migrate
```

### Exemple : Insérer des données via `shell`
```bash
python manage.py shell
```
```python
from myapp.models import User
User.objects.create(name="Alice")
```

### Exemple : Lire des données dans une vue
Dans `views.py` :
```python
from django.shortcuts import render
from .models import User

def user_list(request):
    users = User.objects.all()
    return render(request, 'user_list.html', {'users': users})
```

---

## Commandes SQLite utiles
### Connexion à une base SQLite
```bash
sqlite3 database.db
```

### Afficher les tables
```sql
.tables
```

### Créer une table
```sql
CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT);
```

### Insérer des données
```sql
INSERT INTO users (name) VALUES ('Alice');
```

### Lire des données
```sql
SELECT * FROM users;
```

---

## Bonnes pratiques
1. **Paramétrage des requêtes SQL** : Toujours utiliser des paramètres pour éviter les injections SQL.
2. **Gestion des erreurs** : Ajouter des blocs `try/except` autour des opérations SQLite.
3. **Connexion unique** : Réutiliser la même connexion autant que possible.

---

## Commandes SQLite supplémentaires

### Gestion des archives SQL
- `.archive ...` : Gérer les archives SQL.

### Affichage des autorisations
- `.auth ON|OFF` : Afficher les callbacks d'autorisation.

### Sauvegarde de la base de données
- `.backup ?DB? FILE` : Sauvegarder la base de données (par défaut "main") dans un fichier.

### Gestion des erreurs
- `.bail on|off` : Arrêter après une erreur. Par défaut OFF.

### Changer de répertoire
- `.cd DIRECTORY` : Changer le répertoire de travail.

### Afficher les changements
- `.changes on|off` : Afficher le nombre de lignes modifiées par SQL.

### Vérification des sorties
- `.check GLOB` : Échouer si la sortie depuis `.testcase` ne correspond pas.

### Clonage de la base de données
- `.clone NEWDB` : Cloner les données dans NEWDB depuis la base de données existante.

### Connexions aux bases de données
- `.connection [close] [#]` : Ouvrir ou fermer une connexion de base de données auxiliaire.

### Liste des bases de données attachées
- `.databases` : Lister les noms et fichiers des bases de données attachées.

### Configuration de la base de données
- `.dbconfig ?op? ?val?` : Lister ou changer les options sqlite3_db_config().

### Informations sur la base de données
- `.dbinfo ?DB?` : Afficher les informations de statut sur la base de données.

### Exportation de la base de données
- `.dump ?OBJECTS?` : Rendre le contenu de la base de données en SQL.

### Écho des commandes
- `.echo on|off` : Activer ou désactiver l'écho des commandes.

### Plan de requête
- `.eqp on|off|full|...` : Activer ou désactiver EXPLAIN QUERY PLAN automatique.

### Affichage dans un tableur
- `.excel` : Afficher la sortie de la prochaine commande dans un tableur.

### Quitter le programme
- `.exit ?CODE?` : Quitter ce programme avec le code de retour CODE.

### Suggestions d'index
- `.expert` : EXPÉRIMENTAL. Suggérer des index pour les requêtes.

### Formatage EXPLAIN
- `.explain ?on|off|auto?` : Changer le mode de formatage EXPLAIN. Par défaut : auto.

### Contrôle de fichier
- `.filectrl CMD ...` : Exécuter diverses opérations sqlite3_file_control().

### Schéma complet
- `.fullschema ?--indent?` : Afficher le schéma et le contenu des tables sqlite_stat.

### En-têtes
- `.headers on|off` : Activer ou désactiver l'affichage des en-têtes.

### Aide
- `.help ?-all? ?PATTERN?` : Afficher le texte d'aide pour PATTERN.

### Importation de données
- `.import FILE TABLE` : Importer des données de FILE dans TABLE.

### Index
- `.indexes ?TABLE?` : Afficher les noms des index.

### Vérification d'intégrité
- `.intck ?STEPS_PER_UNLOCK?` : Exécuter une vérification d'intégrité incrémentale sur la base de données.

### Limites
- `.limit ?LIMIT? ?VAL?` : Afficher ou changer la valeur d'une limite SQLITE.

### Analyse de schéma
- `.lint OPTIONS` : Signaler les problèmes potentiels de schéma.

### Chargement d'extensions
- `.load FILE ?ENTRY?` : Charger une bibliothèque d'extension.

### Journalisation
- `.log FILE|on|off` : Activer ou désactiver la journalisation. FILE peut être stderr/stdout.

### Mode de sortie
- `.mode MODE ?OPTIONS?` : Définir le mode de sortie.

### Valeur NULL
- `.nullvalue STRING` : Utiliser STRING à la place des valeurs NULL.

### Sortie unique
- `.once ?OPTIONS? ?FILE?` : Sortie pour la prochaine commande SQL uniquement vers FILE.

### Ouverture de fichier
- `.open ?OPTIONS? ?FILE?` : Fermer la base de données existante et rouvrir FILE.

### Sortie
- `.output ?FILE?` : Envoyer la sortie vers FILE ou stdout si FILE est omis.

### Gestion des paramètres SQL
- `.parameter CMD ...` : Gérer les liaisons de paramètres SQL.

### Impression
- `.print STRING...` : Imprimer la chaîne littérale STRING.

### Gestion du progrès
- `.progress N` : Invoquer le gestionnaire de progrès après chaque N opcodes.

### Invite
- `.prompt MAIN CONTINUE` : Remplacer les invites standard.

### Quitter
- `.quit` : Arrêter l'interprétation du flux d'entrée, quitter si primaire.

### Lecture de fichier
- `.read FILE` : Lire l'entrée depuis FILE ou la sortie de commande.

### Récupération
- `.recover` : Récupérer autant de données que possible depuis une base de données corrompue.

### Restauration
- `.restore ?DB? FILE` : Restaurer le contenu de DB (par défaut "main") depuis FILE.

### Sauvegarde
- `.save ?OPTIONS? FILE` : Écrire la base de données dans FILE (un alias pour .backup ...).

### Statistiques de scan
- `.scanstats on|off|est` : Activer ou désactiver les métriques sqlite3_stmt_scanstatus().

### Schéma
- `.schema ?PATTERN?` : Afficher les instructions CREATE correspondant à PATTERN.

### Séparateurs
- `.separator COL ?ROW?` : Changer les séparateurs de colonne et de ligne.

### Sessions
- `.session ?NAME? CMD ...` : Créer ou contrôler des sessions.

### Somme SHA3
- `.sha3sum ...` : Calculer un hachage SHA3 du contenu de la base de données.

### Shell
- `.shell CMD ARGS...` : Exécuter CMD ARGS... dans un shell système.

### Affichage des paramètres
- `.show` : Afficher les valeurs actuelles pour divers paramètres.

### Statistiques
- `.stats ?ARG?` : Afficher les statistiques ou activer/désactiver les statistiques.

### Système
- `.system CMD ARGS...` : Exécuter CMD ARGS... dans un shell système.

### Tables
- `.tables ?TABLE?` : Lister les noms des tables correspondant au modèle LIKE TABLE.

### Timeout
- `.timeout MS` : Essayer d'ouvrir des tables verrouillées pendant MS millisecondes.

### Minuteur
- `.timer on|off` : Activer ou désactiver le minuteur SQL.

### Trace
- `.trace ?OPTIONS?` : Sortir chaque instruction SQL au fur et à mesure de son exécution.

### Version
- `.version` : Afficher les versions de la source, de la bibliothèque et du compilateur.

### Informations VFS
- `.vfsinfo ?AUX?` : Informations sur le VFS de niveau supérieur.

### Liste des VFS
- `.vfslist` : Lister tous les VFS disponibles.

### Nom du VFS
- `.vfsname ?AUX?` : Imprimer le nom de la pile VFS.

### Largeur des colonnes
- `.width NUM1 NUM2 ...` : Définir les largeurs minimales des colonnes pour la sortie en colonnes.

