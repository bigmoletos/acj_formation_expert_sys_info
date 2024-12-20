# Bibliothéque Dynamique MyFirstDll

## Preparation

1 - Avec visual Code generer un projet de librairie dynamique et créer les fichiers :

- exported_function.h
- exported_function.cpp

2 - Generer le build

3 - Creer un projet et dans le main.cpp faire include de la librairie créée precedement dans notre cas:  #include"exported_function.h"


## Compilation de la DLL Avec GCC ou Clang

On va generer une bibliotheque d'importation libMyFirstDll.a

```Shell
# Sous windows il faut parfois utiliser le -DBUILD_DLL
g++ -DBUILD_DLL -shared -o MyFirstDll.dll exported_function.cpp -Wl,--out-implib,libMyFirstDll.a
```

### Explications

- -DBUILD_DLL : Définit le préprocesseur BUILD_DLL pour signaler que nous compilons une DLL.
- -shared : Indique au compilateur de créer une bibliothèque dynamique.
- -Wl,--out-implib,libMyFirstDll.a : Génère une bibliothèque d'importation compatible avec GCC (libMyFirstDll.a).

## Compilation du projet Avec GCC ou Clang

Liez la bibliothèque avec l'option -L pour le répertoire et -l pour la bibliothèque

```Shell
g++ main.cpp -IMyFirstDll -LMyFirstDll/x64/Debug -lMyFirstDll -o prog.exe

```


### Explications

- -IMyFirstDll : Indique que main.cpp doit chercher les fichiers d'en-tête dans le répertoire actuel (.).
- -LMyFirstDll/x64/Debug : Spécifie où se trouve le fichier MyFirstDll.lib ou son équivalent.
- -lMyFirstDll : Indique le nom de la bibliothèque (sans préfixe lib et sans extension .lib).


prog.exe : Nom du fichier exécutable généré

!! ATTENTION IL N'Y A PAS D'ESPACE ENTRE LE -L ou le -I et le path

## Structure finale des fichiers

librairies/
    librairie_dynamique/
        main.cpp
        exported_function.h
        MyFirstDll.dll
        libMyFirstDll.a  # Bibliothèque d'importation générée par GCC



# Debug

le linker de MinGW, avec l'option -lMyFirstDll, attend une bibliothèque d'importation au format compatible GCC et utilisant la convention de nommage libMyFirstDll.a, et non MyFisrtDll.lib

```shell
mv MyFisrtDll.lib libMyFirstDll.a

```

## Étape 2 : Recompilez avec MinGW

Utilisez la commande suivante pour compiler votre projet client :

```shell
x86_64-w64-mingw32-g++ main.cpp -o prog.exe -I. -L. -lMyFirstDll

```

## Étape 3 : Vérifiez les fichiers nécessaires

libMyFirstDll.a : Le fichier de bibliothèque doit maintenant être correctement renommé.
MyFirstDll.dll : Ce fichier doit être dans le même répertoire que l'exécutable prog.exe lors de l'exécution.
exported_function.h : Fichier d'en-tête utilisé dans main.cpp.

## Résultat attendu

L'exécution de prog.exe devrait afficher le message suivant dans le terminal :


```shell
Appel de la fonction exportée depuis la DLL...
Message depuis la DLL dynamique !
```
