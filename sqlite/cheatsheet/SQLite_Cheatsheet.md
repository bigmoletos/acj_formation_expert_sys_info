
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

