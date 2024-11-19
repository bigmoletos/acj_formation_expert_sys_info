# Installation
## il faut installer MongoDB community  et éventuellement Altas
https://www.mongodb.com/try/download/community


## Il faut aussi installer mongoShell pour utiliser avec le terminal
https://www.mongodb.com/try/download/shell


## verifier que les paths sont okpour mongo.exe et mongosh.exe

# Opérateurs

- **$in** : Sélectionne les documents où la valeur d'un champ est dans un tableau spécifié.
- **$gt** : Sélectionne les documents où la valeur d'un champ est supérieure à une valeur spécifiée.
- **$lt** : Sélectionne les documents où la valeur d'un champ est inférieure à une valeur spécifiée.
- **$gte** : Sélectionne les documents où la valeur d'un champ est supérieure ou égale à une valeur spécifiée.
- **$lte** : Sélectionne les documents où la valeur d'un champ est inférieure ou égale à une valeur spécifiée.
- **$ne** : Sélectionne les documents où la valeur d'un champ n'est pas égale à une valeur spécifiée.
- **$and** : Rejoint les clauses de requête avec une opération logique AND.
- **$or** : Rejoint les clauses de requête avec une opération logique OR.
- **$not** : Inverse l'effet d'un opérateur de requête.
- **$nor** : Rejoint les clauses de requête avec une opération logique NOR.
- **$exists** : Sélectionne les documents où un champ existe ou non, quelle que soit sa valeur.
- **$type** : Sélectionne les documents où le type d'un champ correspond à un type BSON spécifié.
- **$regex** : Sélectionne les documents où les valeurs correspondent à une expression régulière spécifiée.
- **$text** : Effectue une recherche de texte sur le contenu des champs indexés par texte.
- **$elemMatch** : Sélectionne les documents si un champ est un tableau qui contient au moins un élément qui correspond à toutes les conditions spécifiées.
- **$size** : Sélectionne les documents si un champ est un tableau de la taille spécifiée.
- **$all** : Correspond aux tableaux qui contiennent tous les éléments spécifiés.
- **$group** : Regroupe les documents d'entrée par un identifiant spécifié.
- **$sort** : Trie les documents d'entrée.
- **$limit** : Limite le nombre de documents d'entrée.


# Commandes

- **db.help()** : Cette commande répertorie l’ensemble des commandes MongoDB disponibles[^1^][1].
- **mongo -version** : Cette commande vous indique la version de MongoDB que vous utilisez[^1^][1].
- **show dbs** : Cette commande permet d’afficher l’ensemble des bases de données sous la forme d’une liste[^1^][1].
- **use DATABASE_NAME** : Cette commande permet de créer une nouvelle base de données et de choisir son nom[^1^][1].
- **db.dropDatabase()** : Cette commande permet de supprimer la base de données actuellement sélectionnée[^1^][1].
- **db.collection.find()** : Cette commande permet de récupérer des documents dans une collection qui correspondent à une condition[^1^][1].
- **db.collection.insert()** : Cette commande permet d'insérer un ou plusieurs documents dans une collection[^1^][1].
- **db.collection.update()** : Cette commande permet de mettre à jour un ou plusieurs documents dans une collection[^1^][1].
- **db.collection.remove()** : Cette commande permet de supprimer un ou plusieurs documents d'une collection[^1^][1].
- **db.collection.count()** : Cette commande retourne le nombre de documents qui correspondent à une condition[^1^][1].
- **db.collection.distinct()** : Cette commande retourne une liste de valeurs distinctes pour la clé donnée parmi tous les documents de la collection[^1^][1].
- **db.collection.aggregate()** : Cette commande permet d'effectuer des opérations de traitement de données complexes sur les données d'une collection[^1^][1].
- **db.collection.mapReduce()** : Cette commande permet d'effectuer des opérations map-reduce sur une collection[^1^][1].
- **db.collection.createIndex()** : Cette commande crée un nouvel index sur une collection[^1^][1].
- **db.collection.getIndexes()** : Cette commande retourne une liste de tous les index sur une collection[^1^][1].
- **db.collection.dropIndex()** : Cette commande supprime un index d'une collection[^1^][1].
- **db.createUser()** : Cette commande crée un nouvel utilisateur[^1^][1].
- **db.dropUser()** : Cette commande supprime un utilisateur[^1^][1].
- **db.auth()** : Cette commande authentifie un utilisateur[^1^][1].
- **db.logout()** : Cette commande déconnecte un utilisateur[^1^][1].
