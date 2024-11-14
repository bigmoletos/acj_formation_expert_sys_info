# Héritage et Polymorphisme avec des Véhicules

## Partie 1 : Création des Classes

### Classe CVehicule :

- Créer une classe `CVehicule` avec une méthode `afficher()`.

### Classes CMoto et CVoiture :

- Créer des classes `CMoto` et `CVoiture` qui héritent de `CVehicule`.
- Redéfinir la méthode `afficher()` dans ces classes.

## Partie 2 : Test dans le Main

Dans la fonction `main` :

- Créer un objet de chaque classe (`CVehicule`, `CMoto`, `CVoiture`).
- Appeler la méthode `afficher()` pour chacun.

## Partie 3 : Tableau de CVehicule

- Créer un tableau de `CVehicule`.
- Insérer les instances de `CVehicule`, `CMoto`, et `CVoiture` dans ce tableau.
- Parcourir le tableau et appeler `afficher()` pour chaque objet.

### Question : Que se passe-t-il lors de l'appel de `afficher()` ?

## Partie 4 : Gestion de la Mémoire et Destructeurs

- Définir un constructeur et un destructeur dans chaque classe et afficher un message lors de la création et de la destruction.
- Créer un tableau de pointeurs `CVehicule*`.
- Insérer des instances de `CVehicule`, `CMoto`, et `CVoiture`.
- Parcourir le tableau et appeler `afficher()` pour chaque objet.
- Détruire ces instances avec `delete`.

### Question : Que se passe-t-il lors de la destruction des objets ?