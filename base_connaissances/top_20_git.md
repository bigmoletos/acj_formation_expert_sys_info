# Top 20 des commandes Git résumé
1. `git init` - Initialise un nouveau dépôt Git.
2. `git clone <url>` - Clone un dépôt Git existant.
3. `git status` - Affiche l'état du dépôt Git.
4. `git add <fichier>` - Ajoute un fichier à l'index.
5. `git commit -m "<message>"` - Enregistre les modifications dans le dépôt.
6. `git push <remote> <branche>` - Pousse les commits vers une branche d'un dépôt distant.
7. `git pull <remote> <branche>` - Récupère les modifications d'un dépôt distant et les fusionne.
8. `git branch` - Affiche les branches du dépôt.
9. `git checkout <branche>` - Change de branche.
10. `git merge <branche>` - Fusionne une branche dans la branche actuelle.
11. `git log` - Affiche l'historique des commits.
12. `git diff` - Affiche les modifications non indexées.
13. `git stash` - Met de côté les modifications non commitées.
14. `git fetch <remote>` - Récupère les mises à jour d'un dépôt distant.
15. `git rebase <branche>` - Rejoue les commits sur une autre branche.
16. `git reset --hard <commit>` - Réinitialise l'état du dépôt à un commit spécifique.
17. `git rm <fichier>` - Supprime un fichier du dépôt.
18. `git tag <tag>` - Crée un tag pour un commit.
19. `git show <commit>` - Affiche les informations sur un commit.
20. `git config --global user.name "<nom>"` - Définit le nom de l'utilisateur Git.

# SUITE ERRREUR DE MERGE
## suite à une erruer de merge d'une branche, par exemple je suis sur master et je fais un merge main qui vient ecrasé tout master
## alors que je voulais faire l'inverse pour tout annuler et revenir à l'état initial. Cela fonctionne si on as pas encore fait le push sur github
`git checkout -- .`


# Top 20 des commandes Git avec exmples
1. `git init`
   - Initialise un nouveau dépôt Git.
   - Exemple : `git init`
2. `git clone <url>`
   - Clone un dépôt Git existant.
   - Exemple : `git clone https://github.com/username/repo.git`
3. `git status`
   - Affiche l'état du dépôt Git.
   - Exemple : `git status`
4. `git add <fichier>`
   - Ajoute un fichier à l'index.
   - Exemple : `git add README.md`
5. `git commit -m "<message>"`
   - Enregistre les modifications dans le dépôt.
   - Exemple : `git commit -m "Ajout de README"`
6. `git push <remote> <branche>`
   - Pousse les commits vers une branche d'un dépôt distant.
   - Exemple : `git push origin main`
7. `git pull <remote> <branche>`
   - Récupère les modifications d'un dépôt distant et les fusionne.
   - Exemple : `git pull origin main`
8. `git branch`
   - Affiche les branches du dépôt.
   - Exemple : `git branch`
9. `git checkout <branche>`
   - Change de branche.
   - Exemple : `git checkout develop`
10. `git merge <branche>`
    - Fusionne une branche dans la branche actuelle.
    - Exemple : `git merge feature`
11. `git log`
    - Affiche l'historique des commits.
    - Exemple : `git log`
12. `git diff`
    - Affiche les modifications non indexées.
    - Exemple : `git diff`
13. `git stash`
    - Met de côté les modifications non commitées.
    - Exemple : `git stash`
14. `git fetch <remote>`
    - Récupère les mises à jour d'un dépôt distant.
    - Exemple : `git fetch origin`
15. `git rebase <branche>`
    - Rejoue les commits sur une autre branche.
    - Exemple : `git rebase main`
16. `git reset --hard <commit>`
    - Réinitialise l'état du dépôt à un commit spécifique.
    - Exemple : `git reset --hard 0d1d7fc32`
17. `git rm <fichier>`
    - Supprime un fichier du dépôt.
    - Exemple : `git rm README.md`
18. `git tag <tag>`
    - Crée un tag pour un commit.
    - Exemple : `git tag v1.0.0`
19. `git show <commit>`
    - Affiche les informations sur un commit.
    - Exemple : `git show 0d1d7fc32`
20. `git config --global user.name "<nom>"`
    - Définit le nom de l'utilisateur Git.
    - Exemple : `git config --global user.name "Votre Nom"`



# Top 20 des commandes avancées:

1. `git commit -m "<message>"`
   - Enregistre les modifications dans le dépôt.
   - Exemple : `git commit -m "Ajout de README"`
2. `git commit --amend -m "<nouveau message>"`
   - Modifie le dernier commit.
   - Exemple : `git commit --amend -m "Ajout de README et LICENSE"`
3. `git revert <commit>`
   - Annule un commit en créant un nouveau commit qui inverse les modifications.
   - Exemple : `git revert 0d1d7fc32`
4. `git stash`
   - Met de côté les modifications non commitées.
   - Exemple : `git stash`
5. `git stash pop`
   - Applique les modifications mises de côté par la dernière commande `git stash`.
   - Exemple : `git stash pop`
6. `git reset --hard <commit>`
   - Réinitialise l'état du dépôt à un commit spécifique.
   - Exemple : `git reset --hard 0d1d7fc32`
7. `git reset --soft <commit>`
   - Déplace la tête à un commit spécifique, mais conserve les modifications non commitées.
   - Exemple : `git reset --soft 0d1d7fc32`
8. `git rebase <branche>`
   - Rejoue les commits sur une autre branche.
   - Exemple : `git rebase main`
9. `git rebase -i <commit>`
   - Commence un rebase interactif, qui permet de modifier, supprimer ou réorganiser les commits.
   - Exemple : `git rebase -i 0d1d7fc32`
10. `git prune`
    - Supprime les objets non atteignables de la base de données.
    - Exemple : `git prune`
11. `git stash list`
    - Affiche la liste des modifications mises de côté.
    - Exemple : `git stash list`
12. `git stash apply <stash>`
    - Applique une modification mise de côté spécifique.
    - Exemple : `git stash apply stash@{0}`
13. `git stash drop <stash>`
    - Supprime une modification mise de côté spécifique.
    - Exemple : `git stash drop stash@{0}`
14. `git reset <fichier>`
    - Retire un fichier de l'index, mais conserve les modifications.
    - Exemple : `git reset README.md`
15. `git reset --mixed <commit>`
    - Déplace la tête à un commit spécifique et retire les fichiers de l'index, mais conserve les modifications.
    - Exemple : `git reset --mixed 0d1d7fc32`
16. `git rebase --abort`
    - Annule l'opération de rebase en cours.
    - Exemple : `git rebase --abort`
17. `git rebase --continue`
    - Continue l'opération de rebase après avoir résolu les conflits.
    - Exemple : `git rebase --continue`
18. `git prune --dry-run`
    - Affiche les objets qui seraient supprimés par la commande `git prune`, sans les supprimer réellement.
    - Exemple : `git prune --dry-run`
19. `git reflog`
    - Affiche l'historique des mouvements de la tête.
    - Exemple : `git reflog`
20. `git show <commit>`
    - Affiche les informations sur un commit.
    - Exemple : `git show 0d1d7fc32`


