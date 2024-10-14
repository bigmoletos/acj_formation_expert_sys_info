
# Cheat Sheet - Conditions et Opérateurs en C

## Conditions en C

Les instructions conditionnelles permettent de contrôler le flux d'exécution d'un programme en fonction de certaines conditions.

### Syntaxe de base :

#### 1. `if`

```c
if (condition) {
    // code exécuté si la condition est vraie
}
```

#### 2. `if-else`

```c
if (condition) {
    // code exécuté si la condition est vraie
} else {
    // code exécuté si la condition est fausse
}
```

#### 3. `else if`

```c
if (condition1) {
    // code exécuté si condition1 est vraie
} else if (condition2) {
    // code exécuté si condition2 est vraie
} else {
    // code exécuté si aucune condition n'est vraie
}
```

#### 4. `switch-case`

```c
switch (variable) {
    case valeur1:
        // code si variable == valeur1
        break;
    case valeur2:
        // code si variable == valeur2
        break;
    default:
        // code si aucune des valeurs n'est trouvée
        break;
}
```

## Opérateurs en C

### 1. Opérateurs arithmétiques

- `+` : Addition
- `-` : Soustraction
- `*` : Multiplication
- `/` : Division
- `%` : Modulo (reste de la division entière)

Exemple :
```c
int a = 5, b = 2;
int somme = a + b;     // somme = 7
int produit = a * b;   // produit = 10
int division = a / b;  // division = 2 (division entière)
int reste = a % b;     // reste = 1
```

### 2. Opérateurs de comparaison

- `==` : Égal à
- `!=` : Différent de
- `>`  : Supérieur à
- `<`  : Inférieur à
- `>=` : Supérieur ou égal à
- `<=` : Inférieur ou égal à

Exemple :
```c
if (a == b) {
    // code exécuté si a est égal à b
}
```

### 3. Opérateurs logiques

- `&&` : ET logique (vrai si les deux conditions sont vraies)
- `||` : OU logique (vrai si au moins une condition est vraie)
- `!`  : NON logique (inverse de la condition)

Exemple :
```c
if (a > 0 && b < 10) {
    // code exécuté si a est supérieur à 0 ET b est inférieur à 10
}
```

### 4. Opérateurs d'incrémentation et de décrémentation

- `++` : Incrémentation (ajoute 1 à la valeur)
- `--` : Décrémentation (soustrait 1 à la valeur)

Exemple :
```c
int x = 5;
x++;  // x vaut maintenant 6
x--;  // x vaut maintenant 5
```

### 5. Opérateurs d'affectation

- `=`  : Affectation
- `+=` : Ajout puis affectation
- `-=` : Soustraction puis affectation
- `*=` : Multiplication puis affectation
- `/=` : Division puis affectation
- `%=` : Modulo puis affectation

Exemple :
```c
int x = 10;
x += 5;   // x vaut maintenant 15
x *= 2;   // x vaut maintenant 30
```

### 6. Opérateurs bit à bit (bitwise)

- `&`  : ET bit à bit
- `|`  : OU bit à bit
- `^`  : XOR (OU exclusif) bit à bit
- `~`  : NON bit à bit
- `<<` : Décalage à gauche
- `>>` : Décalage à droite

Exemple :
```c
int x = 5;  // binaire : 0101
int y = 3;  // binaire : 0011

int z = x & y;  // z = 1  (binaire : 0001)
int w = x | y;  // w = 7  (binaire : 0111)
```

### 7. Opérateurs ternaires

L'opérateur ternaire est une forme raccourcie de la structure `if-else`.

Syntaxe :
```c
condition ? expression1 : expression2;
```

Exemple :
```c
int a = 10, b = 20;
int max = (a > b) ? a : b;  // max vaut 20
```

