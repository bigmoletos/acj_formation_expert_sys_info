
# Génération de Documentation avec Doxygen

Ce guide explique comment générer une documentation HTML et LaTeX depuis le terminal en utilisant **Doxygen** et **Graphviz**.

---

## Pré-requis

1. **Doxygen** :
   - **Linux** : `sudo apt install doxygen`
   - **Mac** : `brew install doxygen`
   - **Windows** : Téléchargez depuis [https://www.doxygen.nl/](https://www.doxygen.nl/).

2. **Graphviz** (pour les diagrammes) :
   - **Linux** : `sudo apt install graphviz`
   - **Mac** : `brew install graphviz`
   - **Windows** : Téléchargez depuis [https://graphviz.org/download/](https://graphviz.org/download/) et ajoutez-le au `PATH`.

3. **LaTeX** (pour générer des PDF) :
   - **Linux** : `sudo apt install texlive-full`
   - **Mac** : `brew install mactex`
   - **Windows** : Téléchargez MiKTeX depuis [https://miktex.org/](https://miktex.org/).

---

## Étapes pour générer la documentation

### 1. Générer le fichier de configuration
Exécutez la commande suivante dans votre terminal :
```bash
doxygen -g
```
Cela crée un fichier `Doxyfile` dans le dossier courant.

---

### 2. Configurer `Doxyfile`
Ouvrez le fichier `Doxyfile` avec un éditeur de texte et modifiez les paramètres suivants :

- **Nom du projet** :
  ```
  PROJECT_NAME = "Nom du projet"
  ```
- **Répertoire de sortie** :
  ```
  OUTPUT_DIRECTORY = ./docs
  ```
- **Fichiers analysés** :
  ```
  FILE_PATTERNS = *.cpp *.h
  ```
- **Activer Graphviz (si installé)** :
  ```
  HAVE_DOT = YES
  ```

---

### 3. Générer la documentation
Utilisez la commande suivante pour générer la documentation :
```bash
doxygen Doxyfile
```

- La documentation HTML sera générée dans **`docs/html`**.
- La documentation LaTeX sera générée dans **`docs/latex`**.

---

### 4. Générer un PDF avec LaTeX
Pour transformer la documentation LaTeX en PDF :
1. Naviguez dans le dossier LaTeX :
   ```bash
   cd docs/latex
   ```
2. Compilez le fichier principal `refman.tex` :
   ```bash
   pdflatex refman.tex
   ```
3. Le fichier PDF sera généré dans le même dossier.

---

## Résolution des problèmes

### 1. Erreur liée à Graphviz (`dot`)
Si Doxygen affiche une erreur concernant `dot`, assurez-vous que Graphviz est installé correctement :
- Testez l'installation avec :
  ```bash
  dot -V
  ```
- Si `dot` n'est pas trouvé, installez Graphviz (voir Pré-requis) ou désactivez Graphviz dans `Doxyfile` :
  ```
  HAVE_DOT = NO
  ```

### 2. Vérifiez les permissions
Assurez-vous d'avoir les droits nécessaires pour écrire dans le répertoire de sortie spécifié dans `Doxyfile`.

---

## Visualisation

- **HTML** :
  Ouvrez `docs/html/index.html` dans un navigateur.

- **PDF** :
  Ouvrez le fichier généré `docs/latex/refman.pdf` avec un lecteur PDF.

---

## Ressources utiles

- [Documentation officielle de Doxygen](https://www.doxygen.nl/manual/index.html)
- [Graphviz](https://graphviz.org/)
- [LaTeX Project](https://www.latex-project.org/)
