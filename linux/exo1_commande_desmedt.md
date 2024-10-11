# Exercice 1 : Création de fichiers et de dossiers
#
# Créer un répertoire :
# Crée un répertoire nommé projet dans ton dossier personnel (~/).
 mkdir  ~/projet
# Créer des sous-répertoires :
# Dans le répertoire projet, crée deux sous-répertoires nommés doc et src.
 mkdir ~/projet/doc
 mkdir ~/projet/src
#
# Créer des fichiers :
# Dans le répertoire doc, crée deux fichiers : README.txt et LICENSE.txt.
touch ~/projet/doc/README.txt
touch ~/projet/doc/LICENSE.txt
#
# Modifier un fichier :
# Ajoute le texte "Projet Open Source" dans le fichier README.txt.
#
nano ~/projet/doc/README.txt
ecrire:  "Projet Open Source"
enregistrer: CTRL + O
sortir de nano : CTRL + X
#
# Vérifier la structure :
# Liste tous les fichiers et répertoires du dossier projet avec une vue détaillée (afficher permissions, taille, etc.).
ls -la dans chaque dossiers
# ou
ls -lR ~/projet
# ou
tree

# Exercice 2 : Manipulation des fichiers

# Renommer un fichier :
# Renomme le fichier LICENSE.txt en LICENSE.md.
cd projet
cd doc
mv LICENSE.txt LICENSE.md

# Copier des fichiers :
# Copie le fichier README.txt dans le répertoire src.
cp README.txt ~/projet/src/

# Déplacer un fichier :
# Déplace le fichier LICENSE.md dans le répertoire src.
mv LICENSE.md ~/projet/src/

# Supprimer un fichier :
# Supprime le fichier README.txt dans le répertoire src.
cd ..
cd src
rm README.txt



# Exercice 3 : Gestion des utilisateurs et des permissions
#
# Créer un utilisateur :
# Crée un nouvel utilisateur nommé devuser sans créer de dossier personnel.
sudo adduser devuser
# Changer le mot de passe de l'utilisateur :
# Attribue un mot de passe à devuser.
sudo passwd devuser


# Changer les permissions :
# Change les permissions du fichier LICENSE.md pour qu'il soit lisible et modifiable seulement par le propriétaire, et lisible par les autres utilisateurs.
chmod 644 LICENSE.md
# Changer le propriétaire d’un fichier :
# Assigne le fichier LICENSE.md à l’utilisateur devuser.
sudo chown devuser LICENSE.md


# Exercice 4 : Gestion avancée des répertoires et fichiers
#
# Créer un lien symbolique :
# Crée un lien symbolique du fichier LICENSE.md dans le répertoire personnel de l'utilisateur courant.
ln -s LICENSE.md

# Trier les fichiers :
# Liste tous les fichiers du répertoire src triés par taille.
ls -lS ~/projet/src


# Compresser un répertoire :
# Compresse le répertoire projet dans un fichier projet.tar.gz.
cd ..
tar -czvf projet.tar.gz ~/projet


# Extraire un fichier compressé :
# Extrais l'archive projet.tar.gz dans un nouveau répertoire projet_copy.
cd ..
mkdir projet_copy
tar -xzvf projet.tar.gz -C /projet_copy


# Exercice 5 : Supprimer des utilisateurs et fichiers
#
# Supprimer un fichier :
# Supprime l'archive projet.tar.gz.
rm projet.tar.gz


# Supprimer un utilisateur :
# Supprime l'utilisateur devuser sans supprimer son répertoire personnel (s'il y en a un).
sudo userdel devuser


