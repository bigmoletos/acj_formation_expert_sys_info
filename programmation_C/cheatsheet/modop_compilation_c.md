
# Mode Opératoire : Compilation d'un programme C sous WSL avec GCC

## Objectif

Ce document explique comment compiler et exécuter un programme C sous WSL en utilisant le compilateur **GCC**.

## Prérequis

- Avoir installé **WSL** (Windows Subsystem for Linux) sur votre machine.
- Avoir installé **GCC** dans l'environnement WSL.



- pour **connaitre la version** de son compilateur et de son C

```bash
gcc --version
gcc -dM -E - < /dev/null | grep __STDC_VERSION__
```

### Installation de GCC sous WSL

Si GCC n'est pas installé, voici les étapes pour l'installer :

1. Mettre à jour la liste des paquets :

```bash
sudo apt update
sudo apt upgrade
sudo apt install build-essential -y
sudo apt install mingw-w64

```

2. Installer le compilateur GCC :
```bash
sudo apt install gcc
```

3. Vérifier l'installation de GCC :
```bash
gcc --version
```


## Étapes pour compiler un programme C

### 1. Créer un fichier source C

1. Ouvrir un éditeur de texte sous WSL (par exemple, `nano` ou `vim`).
```bash
nano hello.c
```

2. Écrire le programme C dans ce fichier :

```bash
#include <stdio.h>

int main() {
      printf("Hello, World!\n");
      return 0;
}
```

3. Sauvegarder et quitter l'éditeur :
   - Pour `nano` : `CTRL+O` pour enregistrer, puis `CTRL+X` pour quitter.

### 2. Compiler le fichier source

1. Utiliser GCC pour compiler le fichier source :

```bash

gcc hello.c -o hello

```

2. Cette commande crée un fichier exécutable appelé `hello`.

3. Compiler un exe fonctionnant sous windows :

```bash

x86_64-w64-mingw32-gcc -o mon_prog.exe fichier_source.c

```

2. Cette commande crée un fichier exécutable appelé `hello`.
### 3. Exécuter le programme compilé

1. Exécuter l'exécutable généré avec la commande suivante :
```bash
./hello
```

2. Vous devriez voir le message suivant s'afficher :
```bash
Hello, World!
```



## Options de compilation courantes

- **-o** : Spécifie le nom de l'exécutable. Exemple :
```bash
gcc fichier.c -o nom_programme
```

- **-Wall** : Active tous les avertissements. Exemple :
```bash
gcc -Wall fichier.c -o programme
```

- **-g** : Inclut des informations de débogage dans l'exécutable. Exemple :
```bash
gcc -g fichier.c -o programme
```

- **-O2** : Active des optimisations de niveau 2 pour améliorer les performances. Exemple :
```bash
gcc -O2 fichier.c -o programme
```

- **-lm** : Lien avec la bibliothèque mathématique `libm` pour utiliser des fonctions mathématiques. Exemple :
```bash
gcc fichier.c -o programme -lm
```



## Variables

```bash
#include <stdio.h>

int main() {
    // Déclarations de variables de différents types
    int int_var = 42;
    long long_var = 1234567890L;
    unsigned int uint_var = 300;
    unsigned long ulong_var = 4000000000UL;
    float float_var = 3.14159f;
    double double_var = 2.718281828459;
    long double ldouble_var = 1.61803398875L;
    char char_var = 'A';
    char string_var[] = "Hello, World!";

    // Impression des différentes variables avec les formats appropriés
    printf("Int: %d\n", int_var);
    printf("Long Int: %ld\n", long_var);
    printf("Unsigned Int: %u\n", uint_var);
    printf("Unsigned Long Int: %lu\n", ulong_var);

    // Représentation en octal et hexadécimal
    printf("Unsigned Int (octal): %o\n", uint_var);
    printf("Unsigned Int (hexadécimal): %x\n", uint_var);
    printf("Unsigned Long Int (hexadécimal): %lx\n", ulong_var);

    // Valeurs flottantes et doubles
    printf("Float: %f\n", float_var);
    printf("Double: %f\n", double_var);
    printf("Long Double: %Lf\n", ldouble_var);

    // Notation exponentielle
    printf("Double (exponentielle): %e\n", double_var);
    printf("Long Double (exponentielle): %Le\n", ldouble_var);

    // Notation courte entre %f et %e
    printf("Double (notation courte): %g\n", double_var);
    printf("Long Double (notation courte): %Lg\n", ldouble_var);

    // Caractère et chaîne de caractères
    printf("Char: %c\n", char_var);
    printf("String: %s\n", string_var);

    return 0;
}

---
