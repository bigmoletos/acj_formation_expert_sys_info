
# Mode Opératoire : Compilation d'un programme C sous WSL avec GCC

## Formats d'impression en C

Voici une liste des principaux formats d'impression utilisés en C avec leur correspondance :

| Format  | Conversion en        | Écriture                         |
|---------|----------------------|----------------------------------|
| %d      | int                  | Décimale signée                  |
| %ld     | long int             | Décimale signée                  |
| %u      | unsigned int         | Décimale non signée              |
| %lu     | unsigned long int    | Décimale non signée              |
| %o      | unsigned int         | Octale non signée                |
| %lo     | unsigned long int    | Octale non signée                |
| %x      | unsigned int         | Hexadécimale non signée          |
| %lx     | unsigned long int    | Hexadécimale non signée          |
| %f      | float                | Décimale virgule fixe            |
| %lf     | double               | Décimale virgule fixe            |
| %e      | double               | Décimale notation exponentielle  |
| %le     | long double          | Décimale notation exponentielle  |
| %g      | double               | Représentation la plus courte    |
| %lg     | long double          | Représentation la plus courte    |
| %c      | char                 | Caractère                        |
| %s      | char*                | Chaîne de caractères             |

# Spécifications des types et tailles en C

| Format  | Conversion en        | Écriture                         | Taille (octets) | Valeur min                                                  | Valeur max                                                  |
|---------|----------------------|----------------------------------|-----------------|-------------------------------------------------------------|-------------------------------------------------------------|
| %d      | int                  | Décimale signée                  | 2 ou 4          | -32,768 (2 octets) / -2,147,483,648 (4 octets)              | 32,767 (2 octets) / 2,147,483,647 (4 octets)                |
| %ld     | long int             | Décimale signée                  | 4 ou 8          | -2,147,483,648 (4 octets) / -9,223,372,036,854,775,808 (8 octets) | 2,147,483,647 (4 octets) / 9,223,372,036,854,775,807 (8 octets) |
| %u      | unsigned int         | Décimale non signée              | 2 ou 4          | 0                                                           | 65,535 (2 octets) / 4,294,967,295 (4 octets)                |
| %lu     | unsigned long int    | Décimale non signée              | 4 ou 8          | 0                                                           | 4,294,967,295 (4 octets) / 18,446,744,073,709,551,615 (8 octets) |
| %o      | unsigned int         | Octale non signée                | 2 ou 4          | 0                                                           | 65,535 (2 octets) / 4,294,967,295 (4 octets)                |
| %lo     | unsigned long int    | Octale non signée                | 4 ou 8          | 0                                                           | 4,294,967,295 (4 octets) / 18,446,744,073,709,551,615 (8 octets) |
| %x      | unsigned int         | Hexadécimale non signée          | 2 ou 4          | 0                                                           | 65,535 (2 octets) / 4,294,967,295 (4 octets)                |
| %lx     | unsigned long int    | Hexadécimale non signée          | 4 ou 8          | 0                                                           | 4,294,967,295 (4 octets) / 18,446,744,073,709,551,615 (8 octets) |
| %f      | float                | Décimale virgule fixe            | 4               | ~ -3.4E+38                                                  | ~ 3.4E+38                                                   |
| %lf     | double               | Décimale virgule fixe            | 8               | ~ -1.7E+308                                                 | ~ 1.7E+308                                                  |
| %e      | double               | Décimale notation exponentielle  | 8               | ~ -1.7E+308                                                 | ~ 1.7E+308                                                  |
| %le     | long double          | Décimale notation exponentielle  | 8, 12, ou 16    | ~ -1.1E+4932                                                | ~ 1.1E+4932                                                 |
| %g      | double               | Représentation la plus courte    | 8               | ~ -1.7E+308                                                 | ~ 1.7E+308                                                  |
| %lg     | long double          | Représentation la plus courte    | 8, 12, ou 16    | ~ -1.1E+4932                                                | ~ 1.1E+4932                                                 |
| %c      | char                 | Caractère                        | 1               | -128                                                        | 127                                                         |
| %s      | char*                | Chaîne de caractères             | dépend de la chaîne | N/A                                                       | N/A                                                         |
## Spécifications des types et tailles en C

- **unsigned int** :
  - Taille : 2 / 4 octets
  - Valeur minimale : 0
  - Valeur maximale : 65535 / 4294967295
  - Format d'affichage : `%u`

- **signed int** :
  - Taille : 2 / 4 octets
  - Valeur minimale : -32768 / -2147483648
  - Valeur maximale : 32767 / 2147483647
  - Format d'affichage : `%d`

- **int** :
  - Taille : 2 / 4 octets
  - Valeur minimale : -32768 / -2147483648
  - Valeur maximale : 32767 / 2147483647
  - Format d'affichage : `%d`

- **unsigned char** :
  - Taille : 1 octet
  - Valeur minimale : 0
  - Valeur maximale : 255
  - Format d'affichage : `%c`

- **signed char** :
  - Taille : 1 octet
  - Valeur minimale : -128
  - Valeur maximale : 127
  - Format d'affichage : `%c`

- **float** :
  - Taille : 4 octets
  - Valeur minimale : -3.4e38
  - Valeur maximale : 3.4e38
  - Format d'affichage : `%f`

- **double** :
  - Taille : 8 octets
  - Valeur minimale : -1.7e308
  - Valeur maximale : 1.7e308
  - Format d'affichage : `%f`


## Caractères d'échappement en C

Voici une liste des caractères d'échappement fréquemment utilisés en C pour la manipulation des chaînes et sorties formatées :

- `\n` : Nouvelle ligne
- `\r` : Retour chariot
- `\t` : Tabulation horizontale
- `\f` : Saut de page
- `\v` : Tabulation verticale
- `\a` : Signal d'alerte
- `\b` : Retour arrière

## Règles de nommage des variables

Voici les règles à suivre pour nommer des variables en C :

- Pas de nombre en début de nom
- Pas de caractères spéciaux à l'exception de `_`
- Pas de mots réservés en C (comme des types de variable)
- Pas d'accent (`à`, `é`, etc.)
- Pas d'espaces
- Utiliser des noms explicites pour la lisibilité
- Utiliser les minuscules avec des `_` pour séparer les mots


## Constantes mathématiques - Liste des expressions et valeurs

- **M_E** : e
  - Valeur : 2.71828182845904523536

- **M_LOG2E** : log2(e)
  - Valeur : 1.44269504088896340736

- **M_LOG10E** : log10(e)
  - Valeur : 0.434294481903251827651

- **M_LN2** : ln(2)
  - Valeur : 0.693147180559945309417

- **M_LN10** : ln(10)
  - Valeur : 2.30258509299404568402

- **M_PI** : pi
  - Valeur : 3.14159265358979323846

- **M_PI_2** : pi/2
  - Valeur : 1.57079632679489661923

- **M_PI_4** : pi/4
  - Valeur : 0.785398163397448309616

- **M_1_PI** : 1/pi
  - Valeur : 0.318309886183790671538

- **M_2_PI** : 2/pi
  - Valeur : 0.636619772367581343076

- **M_2_SQRTPI** : 2/sqrt(pi)
  - Valeur : 1.12837916709551257390

- **M_SQRT2** : sqrt(2)
  - Valeur : 1.41421356237309504880
"""

# Save the content to a .md file
file_path_math_constants = "/mnt/data/math_constants_list.md"
with open(file_path_math_constants, "w") as file:
    file.write(md_content)

file_path_math_constants
