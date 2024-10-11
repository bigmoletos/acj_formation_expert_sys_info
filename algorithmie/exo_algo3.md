# Les Tests
# EXo 3.1 à 3.6
### ex : test
Variable Temp en Entier
Début
Ecrire "Entrez la température de l’eau :"
Lire Temp
Si Temp =< 0 Alors
  Ecrire "C’est de la glace"
Sinon
  Si Temp < 100 Alors
    Ecrire "C’est du liquide"
  Sinon
    Ecrire "C’est de la vapeur"
  Finsi
Finsi
Fin
```


## exo 3.1
### Écrire un algorithme qui demande un nombre à l’utilisateur, et l’informe ensuite si ce nombre est positif ou négatif (on laisse de côté le cas où le nombre vaut zéro).

```sh

Variables nbre en Numérique
Début
Ecrire "Veuillez saisir un nombre entier non nul"
lire nbre
Si nbre > 0 Alors
    Ecrire "le nombre est positif"
Sinon
    Ecrire " le nombre est negatif"
Finsi
Fin
```


## exo 3.2
### Ecrire un algorithme qui demande deux nombres à l’utilisateur et l’informe ensuite si leur produit est négatif ou positif (on laisse de côté le cas où le produit est nul). Attention toutefois : on ne doit pas calculer le produit des deux nombres.

```sh

Variables A, B en Numérique
Début
Ecrire "Veuillez saisir le nombre entier non nul A "
Lire A
Ecrire "Veuillez saisir le nombre entier non nul B "
Lire B
Si (A > 0 Et B > 0) ou (A < 0 Et B < 0) Alors
    Ecrire "Le produit est positif."
Sinon
    Ecrire "Le produit est négatif."
Fin Si
Fin
```


## exo 3.3
### Ecrire un algorithme qui demande trois noms à l’utilisateur et l’informe ensuite s’ils sont rangés ou non dans l’ordre alphabétique.

```sh

Variables nom1, nom2, nom3 en Caractéres
Début
Ecrire "EnVeuillez saisir le premier nom  :"
Lire nom1
Ecrire "Veuillez saisir le deuxième nom :"
Lire nom2
Ecrire "Veuillez saisir le troisième nom :"
Lire nom3
Si nom1 < nom2 Et nom2 < nom3 Alors
    Ecrire "Les noms sont dans l'ordre alphabétique."
Sinon
    Ecrire "Les noms ne sont pas dans l'ordre alphabétique."
Fin Si

Fin
```


## exo 3.4
### Ecrire un algorithme qui demande un nombre à l’utilisateur, et l’informe ensuite si ce nombre est positif ou négatif (on inclut cette fois le traitement du cas où le nombre vaut zéro).

```sh

Variables nbre en Numérique
Début
Ecrire "Veuillez saisir un nombre entier ou nul"
lire nbre
Si nbre > 0 Alors
    Ecrire "le nombre est positif"
Sinon
    Si nbre <0 Alors
        Ecrire "le nombre est négatif"

Sinon
    Ecrire " le nombre est nul"
Finsi
Fin
```



## exo 3.5
### Ecrire un algorithme qui demande deux nombres à l’utilisateur et l’informe ensuite si le produit est négatif ou positif (on inclut cette fois le traitement du cas où le produit peut être nul). Attention toutefois, on ne doit pas calculer le produit !

```sh


Variables A, B en Numériques
Début
Ecrire "Veuillez saisir le nombre entier ou nul A "
Lire A
Ecrire "Veuillez saisir le nombre entier ou nul B "
Lire B
Si (A > 0 Et B > 0) ou (A < 0 Et B < 0) Alors
    Ecrire "Le produit est positif."
Sinon
    Si A=0 ou B=0 Alors
    Ecrire " le produit est nul"
Sinon
    Ecrire "Le produit est négatif."
FinSi
Fin
```


## exo 3.6
Écrire un algorithme qui demande l'âge d'un enfant à l'utilisateur. Ensuite, il l'informe de sa catégorie :

- **Poussin** : de 6 à 7 ans
- **Pupille** : de 8 à 9 ans
- **Minime** : de 10 à 11 ans
- **Cadet** : après 12 ans

```sh
Variables age en Numérique
Début
Ecrire "Veuillez saisir l'âge de l'enfant :"
Lire age
Si age=0 ou age<0 ou age < 20 Alors
    Ecrire "Veuillez saisir un age superieur à 0 Et inférieur à 20"
Si age >= 6 Et age <= 7 Alors
    Ecrire "Catégorie : Poussin"
Sinon Si age >= 8 Et age <= 9 Alors
    Ecrire "Catégorie : Pupille"
Sinon Si age >= 10 Et age <= 11 Alors
    Ecrire "Catégorie : Minime"
Sinon Si age >= 12 Alors
    Ecrire "Catégorie : Cadet"
Sinon
    Ecrire "Vous avez du faire une erreur dans la saisie de l'age.", age

FinSi
Fin
```


Peut-on concevoir plusieurs algorithmes équivalents menant à ce résultat ?
- Version code imbriqué
```sh

Variables age en Numérique
Début
Ecrire "Veuillez saisir l'âge de l'enfant :"
Lire age
Si age=<0 Ou age < 20 Alors
    Ecrire "Veuillez saisir un age superieur à 0 Et inférieur à 20"
FinSi
Si age >= 6 Et age <= 7 Alors
    Ecrire "Catégorie : Poussin"
FinSi
Si age >= 8 Et age <= 9 Alors
    Ecrire "Catégorie : Pupille"
FinSi
Si age >= 10 Et age <= 11 Alors
    Ecrire "Catégorie : Minime"
FinSi
Si age >= 12 Alors
    Ecrire "Catégorie : Cadet"
Sinon
    Ecrire "Vous avez du faire une erreur dans la saisie de l'age.", age

FinSi
Fin
```

- version avec les booléens
```sh
Variables age en Numérique
Variables A,B,C,D en Booléen
Début
Ecrire "Veuillez saisir l'âge de l'enfant :"
Lire age
A <- age >= 6 Et age <= 7
B <- age >= 8 Et age <= 9
C <- age >= 10 Et age <= 11
D <- age >= 12

Si age=< 0 Ou age < 20 Alors
    Ecrire "Veuillez saisir un age superieur à 0 Et inférieur à 20. Verifiez que vous avez bien saisi un nombre et non des caractéres: ", age

SinonSi A Alors
    Ecrire "Catégorie : Poussin"

SinonSi B Alors
    Ecrire "Catégorie : Pupille"

SinonSi C Alors
    Ecrire "Catégorie : Minime"

SinonSi D Alors
    Ecrire "Catégorie : Cadet"

Sinon
    Ecrire "Vous avez dû faire une erreur dans la saisie de l'age.", age

FinSi
Fin
```