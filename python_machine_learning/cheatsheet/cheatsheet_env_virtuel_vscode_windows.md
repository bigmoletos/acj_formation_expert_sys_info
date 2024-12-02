
# Cheatsheet : Création d'un Environnement Virtuel avec VS Code sous Windows

## Pré-requis
- **Python** installé (version 3.6 ou plus récente recommandée)
- **VS Code** installé
- Extension **Python** pour VS Code installée

---

## Étapes

### 1. Vérification de l'installation de Python
```bash
python --version
```

### 2. Création d'un répertoire de projet
Créer un dossier pour votre projet :
```bash
mkdir mon_projet
cd mon_projet
```

### 3. Création d'un environnement virtuel
Créer un environnement virtuel dans le dossier `env` :
```bash
python -m venv env
```

### 4. Activation de l'environnement virtuel
Activer l'environnement virtuel :
- **Cmd** :
  ```bash
  env\Scripts\activate
  ```
- **PowerShell** :
  ```bash
  .\env\Scripts\Activate.ps1
  ```
- **Git Bash** :
  ```bash
  source env/Scripts/activate
  ```

### 5. Ouverture du projet dans VS Code
Lancer VS Code dans le dossier du projet :
```bash
code .
```

### 6. Configuration de l'interpréteur Python
- Ouvrir la **palette de commande** (`Ctrl+Shift+P`)
- Taper `Python: Select Interpreter`
- Sélectionner l'interpréteur correspondant à l'environnement virtuel (chemin affiché : `env`).

### 7. Installation des dépendances
Installer les dépendances nécessaires à votre projet :
```bash
pip install -r requirements.txt
```

### 8. Création ou édition de fichiers
- Créer un fichier **`main.py`** ou d'autres fichiers nécessaires pour votre projet.

### 9. Désactivation de l'environnement virtuel
Quitter l'environnement virtuel :
```bash
deactivate
```

### 10. Suppression de l'environnement virtuel
Pour supprimer l'environnement virtuel, il suffit de supprimer le dossier `env` :
```bash
rm -r env
```

---

## Conseils
- **Bonnes pratiques** : Ajouter le dossier `env` au fichier `.gitignore` pour éviter de le versionner.
- **Fichier `requirements.txt`** : Utiliser la commande suivante pour sauvegarder les dépendances :
  ```bash
  pip freeze > requirements.txt
  ```

---

## Ressources utiles
- [Documentation officielle Python](https://docs.python.org/3/tutorial/venv.html)
- [Guide Python pour VS Code](https://code.visualstudio.com/docs/python/python-tutorial)

---

**Auteur** : Big MOLETOS
