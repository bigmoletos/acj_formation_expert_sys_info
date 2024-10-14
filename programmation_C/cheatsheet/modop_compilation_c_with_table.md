
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
