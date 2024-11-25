# Configuration du Workflow GitHub Actions

Pour intégrer votre fichier `ci-cd.yml` dans GitHub Actions, vous allez devoir créer un workflow GitHub Actions dans votre dépôt GitHub. Je vais vous guider étape par étape pour mettre en place et tester ce fichier `ci-cd.yml` :

### Étape 1 : Structure du Répertoire GitHub Actions
Le fichier `ci-cd.yml` doit être placé dans le répertoire `.github/workflows` de votre dépôt. Voici comment procéder :

1. Assurez-vous que vous avez bien un dépôt GitHub pour votre projet.
2. Clonez votre dépôt en local, si ce n’est pas encore fait :

   ```bash
   git clone https://github.com/username/nom_du_depot.git
   cd nom_du_depot
   ```

3. Créez un dossier `.github/workflows` à la racine de votre dépôt :

   ```bash
   mkdir -p .github/workflows
   ```

4. Déplacez votre fichier `ci-cd.yml` dans ce répertoire :

   ```bash
   mv chemin/vers/ci-cd.yml .github/workflows/
   ```

5. Renommez éventuellement `ci-cd.yml` en `main.yml` ou en un nom plus descriptif si vous souhaitez indiquer une intention précise pour ce workflow.

### Étape 2 : Pousser le Fichier dans le Dépôt GitHub
Une fois que votre fichier est dans le répertoire `.github/workflows`, vous devez le pousser sur GitHub :

1. Ajoutez les fichiers au suivi Git :

   ```bash
   git add .github/workflows/ci-cd.yml
   ```

2. Créez un commit avec un message approprié :

   ```bash
   git commit -m "Ajout du fichier ci-cd pour GitHub Actions"
   ```

3. Poussez votre modification sur la branche de votre choix, par exemple `main` :

   ```bash
   git push origin main
   ```

### Étape 3 : Tester le Workflow GitHub Actions

Une fois le fichier `ci-cd.yml` poussé sur GitHub, GitHub Actions devrait automatiquement détecter et exécuter ce workflow lors de l'événement spécifié (par exemple `push` ou `pull_request`). Voici comment vérifier que tout fonctionne correctement :

1. **Ouvrir la page GitHub du dépôt** : Rendez-vous sur la page de votre dépôt sur GitHub.

2. **Accéder aux Actions** :
   - Cliquez sur l'onglet `Actions` en haut de la page du dépôt.
   - Vous y verrez une liste de workflows disponibles. Le workflow que vous venez de créer devrait apparaître.

3. **Vérifier le Statut du Workflow** :
   - Cliquez sur le nom de votre workflow pour voir les détails de l'exécution.
   - Si le workflow est en cours d'exécution, vous verrez un indicateur en cours (`In progress`).
   - En cas de succès, vous verrez une coche verte, sinon une croix rouge (`Failed`) indiquera un problème.

4. **Déboguer un Échec** :
   - Cliquez sur le workflow échoué pour voir les logs.
   - Analysez les messages d’erreur pour identifier ce qui ne fonctionne pas et ajustez votre fichier `ci-cd.yml` en conséquence.

### Étape 4 : Tester en Local (Optionnel)

Il est possible de tester des GitHub Actions localement avec un outil comme [**act**](https://github.com/nektos/act), qui simule l'exécution des workflows GitHub. Voici comment faire :

1. Installez `act` en suivant les instructions de leur documentation.

```bash
choco install act-cli

```

2. Utilisez la commande suivante pour tester un workflow localement :

```bash

act --version
# lancer act
act
# lancer act avec push
act push
# possibilité aussi de spécifier une image Docker de plus grande capacité
act -P ubuntu-latest=ghcr.io/catthehacker/ubuntu:full-latest

```

   Cette commande exécutera les workflows dans un environnement simulé. Cela permet de repérer des erreurs avant même de pousser sur GitHub.

### Exemple de Fichier `ci-cd.yml`

Voici un exemple de fichier `ci-cd.yml` qui est utilisé pour tester une application Python :

```yaml
name: CI-CD Pipeline

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Set up Python
      uses: actions/setup-python@v2
      with:
        python-version: '3.8'

    - name: Install dependencies
      run: |
        python -m pip install --upgrade pip
        pip install -r requirements.txt

    - name: Run Tests
      run: |
        pytest
```

Ce fichier effectue les tâches suivantes :
1. **Trigger le workflow** sur `push` ou `pull_request`.
2. **Vérifie le dépôt** (cloner le code).
3. **Configure Python** pour l’environnement.
4. **Installe les dépendances** listées dans `requirements.txt`.
5. **Exécute les tests unitaires** avec `pytest`.

### Conclusion

En résumé :
- Placez votre fichier `ci-cd.yml` dans `.github/workflows`.
- Poussez le fichier sur GitHub pour qu'il soit automatiquement pris en charge.
- Vérifiez le statut dans l’onglet `Actions` sur GitHub.
- Utilisez `act` pour tester en local, si besoin.

N’hésitez pas à vérifier les logs de l’exécution pour déboguer et ajuster votre workflow en cas de problèmes. Est-ce que cela répond à vos questions ?