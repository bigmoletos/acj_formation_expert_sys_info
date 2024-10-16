
# C Cheatsheet: Fonctions, Pointeurs et Tableaux

## Fonctions en C

### Définition de base d'une fonction
```c
type_retour nom_fonction(type_param1 param1, type_param2 param2, ...) {
    // Corps de la fonction
    return valeur;
}
```

### Exemple de fonction simple
```c
#include <stdio.h>

int addition(int a, int b) {
    return a + b;
}

int main() {
    int resultat = addition(5, 3);
    printf("Résultat: %d\n", resultat);
    return 0;
}
```

### Passer des paramètres par valeur
- Les paramètres passés par valeur créent une **copie** de la valeur d'origine.
- Les modifications à l'intérieur de la fonction n'affectent pas les variables d'origine.

### Passer des paramètres par référence (avec des pointeurs)
- Passer un pointeur permet de modifier la valeur d'origine à l'extérieur de la fonction.

```c
void incrementer(int *valeur) {
    (*valeur)++;
}

int main() {
    int x = 10;
    incrementer(&x);  // Modifie directement x
    printf("Nouvelle valeur de x: %d\n", x);  // x = 11
    return 0;
}
```

## Pointeurs en C

### Définition d'un pointeur
- Un pointeur stocke l'adresse mémoire d'une variable.

```c
int *ptr;
int valeur = 10;
ptr = &valeur;  // ptr contient l'adresse de `valeur`
```

### Déréférencement d'un pointeur
- Utiliser `*` pour accéder à la valeur pointée par un pointeur.

```c
int x = 5;
int *p = &x;

printf("Valeur de x via le pointeur: %d\n", *p);  // Affiche 5
```

### Pointeurs et tableaux
- Le nom d'un tableau est un pointeur vers le premier élément du tableau.

```c
int tableau[5] = {1, 2, 3, 4, 5};
int *p = tableau;  // Équivaut à &tableau[0]

printf("Premier élément: %d\n", *p);  // Affiche 1
```

### Pointeurs et chaînes de caractères
- Les chaînes de caractères sont des tableaux de `char`, donc on peut utiliser des pointeurs pour parcourir une chaîne.

```c
char *str = "Hello";
while (*str != '\0') {
    printf("%c", *str);
    str++;
}
```

## Tableaux en C

### Déclaration d'un tableau
- Un tableau est une collection de variables du même type, stockées en mémoire de manière contiguë.

```c
int tableau[5];  // Tableau de 5 entiers
```

### Initialisation d'un tableau
```c
int tableau[5] = {1, 2, 3, 4, 5};  // Tableau initialisé
```

### Parcourir un tableau avec une boucle
```c
int tableau[5] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++) {
    printf("%d\n", tableau[i]);
}
```

### Passer un tableau à une fonction
- En réalité, on passe un **pointeur** vers le premier élément du tableau.

```c
void afficher_tableau(int arr[], int taille) {
    for (int i = 0; i < taille; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int tableau[5] = {1, 2, 3, 4, 5};
    afficher_tableau(tableau, 5);
    return 0;
}
```

## Résumé des opérateurs de pointeurs et tableaux

| Opérateur | Description                                   |
|-----------|-----------------------------------------------|
| `*`       | Déréférencement d'un pointeur (accès à la valeur pointée) |
| `&`       | Obtention de l'adresse d'une variable         |
| `[]`      | Accès à un élément de tableau                 |

pointeur : variable contenant l'adresse d'une autre variable

## [variables]
- **_mavariable** : valeur de la variable
- **_&mavariable** : adresse de la variable

## [pointeur]
- **monpointeur** : adresse de la variable pointé
- **_*monpointeur_** : valeur de variable pointé
- **_&monpointeur_** : adresse du pointeur

## [déclaration et init d'un pointeur]
- **_*monpointeur** = NULL
ou
- **_*monpointeur** = &variable



## Exemples d'erreurs fréquentes
- **Ne pas initialiser un pointeur** : Utiliser un pointeur non initialisé peut causer des erreurs.
- **Déréférencement de pointeur NULL** : Tenter d'accéder à un pointeur NULL peut provoquer une erreur d'exécution.
- **Dépassement de tableau** : Accéder à un indice en dehors de la taille du tableau est dangereux et peut causer des erreurs.

## acces par pointeur avec *tableau car les elements d'un tableau sont des pointeurs donc des cases memoires

```c
// [acces] tableau
tableau[x] //: element indice X
tableau //: adresse du tableau
*tableau //: premier element du tableau
*(tableau + X) //: element d indice X
```

