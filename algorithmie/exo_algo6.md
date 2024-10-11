# PARTIE 6
# Les tableaux
## Enoncé des Exercices

### Exercice 6.1
Écrire un algorithme qui déclare et remplisse un tableau de 7 valeurs numériques en les mettant toutes à zéro.
```sh
Tableau T[7] en Numérique
Début
  Pour i ← 0 à 6
    T[i] ← 0
  i suivant
Fin

```

### Exercice 6.2
Écrire un algorithme qui déclare et remplisse un tableau contenant les six voyelles de l’alphabet latin.
```sh
Tableau Voyelles[6] en Caractère
Début
  Voyelles[0] ← 'a'
  Voyelles[1] ← 'e'
  Voyelles[2] ← 'i'
  Voyelles[3] ← 'o'
  Voyelles[4] ← 'u'
  Voyelles[5] ← 'y'
Fin

```

### Exercice 6.3
Écrire un algorithme qui déclare un tableau de 9 notes, dont on fait ensuite saisir les valeurs par l’utilisateur.
```sh
Tableau Notes[9] en Numérique
Variable i en Entier
Début
  Pour i ← 0 à 8
    Ecrire "Saisissez la note", i + 1
    Lire Notes[i]
  i suivant
Fin


```

### Exercice 6.4
Que produit l’algorithme suivant ?
```sh
Tableau Nb[5] en Entier
Variable i en Entier
Début
Pour i ← 0 à 5
  Nb[i] ← i * i
i suivant
Pour i ← 0 à 5
  Écrire Nb[i]
i suivant
Fin
```
- ce script produit un tableau de 5 nombres des carrés des valeurs de 1 à 5 ensuite il affiche le résultat
0 1 4 9 16 25
Peut-on simplifier cet algorithme avec le même résultat ?
- on peut faire une seuel boucle

```sh
Tableau Nb[5] en Entier
Variable i en Entier
Début
Pour i ← 0 à 5
  Nb[i] ← i * i
  Écrire Nb[i]
i suivant

Fin
```

### Exercice 6.5
Que produit l’algorithme suivant ?
```sh
Tableau N[6] en Entier
Variables i, k en Entier
Début
N[0] ← 1
Pour k ← 1 à 6
  N[k] ← N[k-1] + 2
k Suivant
Pour i ← 0 à 6
  Écrire N[i]
i suivant
Fin
```
ce script produit un tableau de 6 entiers affecte la valeur 1 à l'indice 0 du tableau
boucle de 1 à 6, donc sur les valeurs du tableau
rajoute 2 par rapport à la valeur precedente et affiche le résultat
1 3 5 7 9 11 13

Peut-on simplifier cet algorithme avec le même résultat ?
```sh
Tableau N[6] en Entier
Variables k en Entier
Début
N[0] ← 1
Pour k ← 1 à 6
  N[k] ← N[k-1] + 2
  Écrire N[k]
k Suivant

Fin
```


### Exercice 6.6
Que produit l’algorithme suivant ?
```sh
Tableau Suite[7] en Entier
Variable i en Entier
Début
Suite[0] ← 1
Suite[1] ← 1
Pour i ← 2 à 7
  Suite[i] ← Suite[i-1] + Suite[i-2]
i suivant
Pour i ← 0 à 7
  Écrire Suite[i]
i suivant
Fin

```
- ce script affecte la valeur 0 à l'indice 1 et 2 du tableau de 7 elements
les valeur suivantes seraont égales à la somme des 2 valeurs precedentes. Ensuite il affiche les valeurs du tableau
1 1 2 3 5 8 13 21
c'est la suite de fibonacci !!


### Exercice 6.7
Écrivez la fin de l’algorithme 6.3 afin que le calcul de la moyenne des notes soit effectué et affiché à l’écran.
```sh
Tableau Notes[9] en Numérique
Variable i en Entier
Variable  som, moy en Numerique
Début
  Pour i ← 0 à 8
    Ecrire "Saisissez la note", i + 1
    Lire Notes[i]
    som <- som + Notes[i]
  i suivant
  moy <- som/9
  Ecrire "La moyenne des notes est  ", moy
Fin

```

### Exercice 6.8
Écrivez un algorithme permettant à l’utilisateur de saisir un nombre quelconque de valeurs, qui devront être stockées dans un tableau. L’utilisateur doit donc commencer par entrer le nombre de valeurs qu’il compte saisir. Il effectuera ensuite cette saisie. Enfin, une fois la saisie terminée, le programme affichera le nombre de valeurs négatives et le nombre de valeurs positives.
```sh


```

### Exercice 6.9
Écrivez un algorithme calculant la somme des valeurs d’un tableau (on suppose que le tableau a été préalablement saisi).
```sh

```

### Exercice 6.10
Écrivez un algorithme constituant un tableau, à partir de deux tableaux de même longueur préalablement saisis. Le nouveau tableau sera la somme des éléments des deux tableaux de départ.

**Tableau 1** :
4  8  7  9  1  5  4  6

**Tableau 2** :
7  6  5  2  1  3  7  4

**Tableau à constituer** :
11  14  12  11  2  8  11  10
```sh

```

### Exercice 6.11
Toujours à partir de deux tableaux précédemment saisis, écrivez un algorithme qui calcule le schtroumpf des deux tableaux. Pour calculer le schtroumpf, il faut multiplier chaque élément du tableau 1 par chaque élément du tableau 2, et additionner le tout.

**Tableau 1** :
4  8  7  12

**Tableau 2** :
3  6

Le Schtroumpf sera :
3 * 4 + 3 * 8 + 3 * 7 + 3 * 12 + 6 * 4 + 6 * 8 + 6 * 7 + 6 * 12 = 279
```sh

```

### Exercice 6.12
Écrivez un algorithme qui permette la saisie d’un nombre quelconque de valeurs, sur le principe de l’exercice 6.8. Toutes les valeurs doivent être ensuite augmentées de 1, et le nouveau tableau sera affiché à l’écran.
```sh

```

### Exercice 6.13
Écrivez un algorithme permettant, toujours sur le même principe, à l’utilisateur de saisir un nombre déterminé de valeurs. Le programme, une fois la saisie terminée, renvoie la plus grande valeur en précisant quelle position elle occupe dans le tableau. On prendra soin d’effectuer la saisie dans un premier temps, et la
