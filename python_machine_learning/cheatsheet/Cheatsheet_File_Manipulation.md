
# Cheatsheet Python : Manipulation de fichiers (xlsx, csv, txt, json)

Ce guide présente les méthodes les plus courantes pour manipuler des fichiers dans Python, en utilisant les bibliothèques `pandas`, `openpyxl`, et les outils natifs.

---

## **1. Manipulation des fichiers CSV**
### Lecture d'un fichier CSV
```python
import pandas as pd

# Lire un fichier CSV
df = pd.read_csv("fichier.csv")

# Lire un fichier avec un séparateur spécifique
df = pd.read_csv("fichier.csv", sep=";")
```

### Écriture dans un fichier CSV
```python
# Sauvegarder un DataFrame dans un fichier CSV
df.to_csv("sortie.csv", index=False)

# Sauvegarder avec un autre séparateur
df.to_csv("sortie.csv", sep=";", index=False)
```

---

## **2. Manipulation des fichiers XLSX**
### Lecture d'un fichier Excel
```python
import pandas as pd

# Lire un fichier Excel
df = pd.read_excel("fichier.xlsx")

# Lire une feuille spécifique
df = pd.read_excel("fichier.xlsx", sheet_name="Feuille1")
```

### Écriture dans un fichier Excel
```python
# Sauvegarder un DataFrame dans un fichier Excel
df.to_excel("sortie.xlsx", index=False)

# Sauvegarder plusieurs feuilles
with pd.ExcelWriter("sortie_multifeuilles.xlsx") as writer:
    df1.to_excel(writer, sheet_name="Feuille1", index=False)
    df2.to_excel(writer, sheet_name="Feuille2", index=False)
```

---

## **3. Manipulation des fichiers JSON**
### Lecture d'un fichier JSON
```python
import pandas as pd

# Lire un fichier JSON dans un DataFrame
df = pd.read_json("fichier.json")

# Charger un fichier JSON en mode natif
import json
with open("fichier.json", "r") as f:
    data = json.load(f)
```

### Écriture dans un fichier JSON
```python
# Sauvegarder un DataFrame dans un fichier JSON
df.to_json("sortie.json", orient="records", indent=4)

# Sauvegarder avec la bibliothèque json
with open("sortie.json", "w") as f:
    json.dump(data, f, indent=4)
```

---

## **4. Manipulation des fichiers TXT**
### Lecture d'un fichier texte
```python
# Lire tout le contenu d'un fichier texte
with open("fichier.txt", "r") as f:
    contenu = f.read()

# Lire un fichier ligne par ligne
with open("fichier.txt", "r") as f:
    lignes = f.readlines()
```

### Écriture dans un fichier texte
```python
# Écrire dans un fichier texte
with open("sortie.txt", "w") as f:
    f.write("Bonjour, ceci est une ligne.")

# Ajouter à un fichier texte existant
with open("sortie.txt", "a") as f:
    f.write("\nNouvelle ligne ajoutée.")
```

---

## **5. Paramètres communs**
- **`encoding`** : Spécifie l'encodage (par exemple, `utf-8` ou `latin1`).
- **`index`** : Lors de l'écriture avec pandas, contrôle si l'index doit être sauvegardé.
- **`sep`** : Détermine le séparateur pour les fichiers CSV.
- **`sheet_name`** : Indique la feuille Excel à lire ou écrire.
- **`orient`** : Détermine le format JSON (ex. `"records"` ou `"index"`).
- **`indent`** : Indique le niveau d'indentation pour les fichiers JSON.

---

## **6. Utilisation avancée**
### Gérer des erreurs d'encodage
```python
# Lecture en ignorant les erreurs
df = pd.read_csv("fichier.csv", encoding="utf-8", error_bad_lines=False)
```

### Lire un fichier volumineux par morceaux
```python
# Lire par blocs
for chunk in pd.read_csv("fichier.csv", chunksize=1000):
    print(chunk.head())
```

---

### Notes :
- La bibliothèque **`pandas`** est idéale pour manipuler des données tabulaires.
- Utilisez la bibliothèque **`openpyxl`** pour des fonctionnalités Excel avancées.

---

