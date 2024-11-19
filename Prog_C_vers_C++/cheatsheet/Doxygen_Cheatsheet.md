
# Cheatsheet: Génération de documentation avec Doxygen

## 1. Installer Doxygen
- **Linux** : `sudo apt install doxygen`
- **Mac** : `brew install doxygen`
- **Windows** : Télécharger depuis [https://www.doxygen.nl/](https://www.doxygen.nl/)

## 2. Générer le fichier de configuration
- Commande : `doxygen -g`
- Crée un fichier `Doxyfile` par défaut dans le dossier courant.

## 3. Configurer le fichier `Doxyfile`
- Ouvrez `Doxyfile` et modifiez les paramètres suivants :
  - **Nom du projet** : `PROJECT_NAME = "Nom du projet"`
  - **Répertoire de sortie** : `OUTPUT_DIRECTORY = ./docs`
  - **Fichiers analysés** : `FILE_PATTERNS = *.cpp *.h`
  - **Graphviz** : Si Graphviz est installé, activez les diagrammes avec `HAVE_DOT = YES`.

## 4. Générer la documentation
- Commande : `doxygen Doxyfile`
- Lancez cette commande depuis le dossier contenant `Doxyfile`.

## 5. Visualiser la documentation
- **HTML** : Ouvrez `docs/html/index.html` dans un navigateur.
- **LaTeX** : Compilez `docs/latex/refman.tex` en PDF avec `pdflatex` :
  ```bash
  pdflatex refman.tex
  ```

## 6. Résoudre les problèmes avec Graphviz
- Si Doxygen affiche des erreurs liées à `dot` :
  - Installez Graphviz :
    - **Linux** : `sudo apt install graphviz`
    - **Mac** : `brew install graphviz`
    - **Windows** : Téléchargez depuis [https://graphviz.org/download/](https://graphviz.org/download/) et ajoutez-le au `PATH`.
  - Vérifiez l'installation avec : `dot -V`

---
