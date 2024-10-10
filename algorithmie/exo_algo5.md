# Parti 5 Les Boucles
## ## Exercice 5.1
Ecrire un algorithme qui demande à l’utilisateur un nombre compris entre 1 et 3 jusqu’à ce que la réponse convienne.

```sh
Variables nbre en Numérique
Début
nbre <-0
TantQue nbre < 1 Et nbre > 3
    Ecrire "Veuillez entrer un nombre entre 1 et 3 :"
    Lire nbre
    FinTantQue
Ecrire "Votre saisie : ", nbre "est correcte "
Fin

```

## Exercice 5.2
Ecrire un algorithme qui demande un nombre compris entre 10 et 20, jusqu’à ce que la réponse convienne. En cas de réponse supérieure à 20, on fera apparaître un message : « Plus petit ! », et inversement, « Plus grand ! » si le nombre est inférieur à 10.
```sh
Variables nbre en Numérique

Début
nbre <- 0
Ecrire "Veuillez saisir un nombre entre 10 et 20 :"
    TantQue nbre < 10 Ou nbre > 20
        Lire nbre
        Si nbre > 20 Alors
            Ecrire "Votre nombre est trop grand  !",nbre
        Sinon Si nbre < 10 Alors
            Ecrire "Votre nombre est trop petit!",nbre
        FinSi
     FinTantQue

Ecrire "Votre saisie : ", nbre , "est bien comprise entre 10 et 20 "
Fin

```


## Exercice 5.3
Ecrire un algorithme qui demande un nombre de départ, et qui ensuite affiche les dix nombres suivants. Par exemple, si l'utilisateur entre le nombre 17, le programme affichera les nombres de 18 à 27.
```sh
Variables nbre, cpt en Entier
Début
nbre <- 0
cpt <- 0
Ecrire "Veuillez saisir un nombre entre 10 et 20 :"
Lire nbre
Ecrire "la lsite des 10 chiffres suivants sont:"
TantQue cpt <=10
  Ecrire nbre+1
  Ecrire ""
  cpt = cpt+1
FinTantQue
Fin
```



## Exercice 5.4
Réécrire l'algorithme précédent, en utilisant cette fois l'instruction Pour

```sh
Variables nbre, cpt en Entier
Début
nbre <- 0
cpt <- 0
Ecrire "Veuillez saisir un nombre entre 10 et 20 :"
Lire nbre
Ecrire "la lsite des 10 chiffres suivants sont:"
Pour cpt <- nbre à nbre + 10
  Ecrire cpt
  Ecrire ""
cpt suivant
Fin
```
## Exercice 5.5
Ecrire un algorithme qui demande un nombre de départ, et qui ensuite écrit la table de multiplication de ce nombre, présentée comme suit (cas où l'utilisateur entre le nombre 7) :
Table de 7 :
7 x 1 = 7
7 x 2 = 14
7 x 3 = 21
…
7 x 10 = 70

```sh
Variables nbre, cpt en Entier
Début
nbre <- 0
cpt <- 0
Ecrire "Veuillez saisir un nombre entier non nul :"

Lire nbre
Ecrire "la lsite de mulitplication jusqu'à 10 est la suivantes :"
Ecrire "la table de " , nbre, " :"
Pour cpt <- 1 à  10
  Ecrire nbre , "x", cpt , " = " , nbre*cpt
  Ecrire ""
cpt suivant
Fin
```

## Exercice 5.6
Ecrire un algorithme qui demande un nombre de départ, et qui calcule la somme des entiers jusqu’à ce nombre. Par exemple, si l’on entre 5, le programme doit calculer :
1 + 2 + 3 + 4 + 5 = 15
NB : on souhaite afficher uniquement le résultat, pas la décomposition du calcul.

```sh
Variables nbre, cpt, resultat en Entier
Début
nbre <- 0
cpt <- 0
resultat <- 0
Ecrire "Veuillez saisir un nombre entier non nul :"
Lire nbre
Ecrire "la somme des entiers de ", nbre , "est :"
Pour cpt <- 1 à  nbre
   resultat <- resultat + cpt

cpt suivant
Ecrire resultat
Fin
```

## Exercice 5.7
Ecrire un algorithme qui demande un nombre de départ, et qui calcule sa factorielle.
NB : la factorielle de 8, notée 8 !, vaut
1 x 2 x 3 x 4 x 5 x 6 x 7 x 8
```sh
Variables nbre, cpt, resultat en Entier
Début
nbre <- 0
cpt <- 0
resultat <- 0
Ecrire "Veuillez saisir un nombre entier non nul :"
Lire nbre
Pour cpt <- 1 à  nbre
   resultat <- resultat * cpt

cpt suivant
Ecrire "la factorielle de ", nbre , "! est :", resultat

Fin
```

## Exercice 5.8
Ecrire un algorithme qui demande successivement 20 nombres à l’utilisateur, et qui lui dise ensuite quel était le plus grand parmi ces 20 nombres :
Entrez le nombre numéro 1 : 12
Entrez le nombre numéro 2 : 14
etc.
Entrez le nombre numéro 20 : 6
Le plus grand de ces nombres est  : 14
Modifiez ensuite l’algorithme pour que le programme affiche de surcroît en quelle position avait été saisie ce nombre :
C’était le nombre numéro 2

```sh
Variables nbre, cpt, max en Entier
Début
nbre <- 0
cpt <- 0
max <- 0
Ecrire "Veuillez saisir 20 nombres entier non nul :"
Pour cpt <- 1 à  20
  Ecrire "Entrez le nombre numéro " , cpt , ":"
  Lire nbre
  si max <nbre alors
    max <- nbre
  finsi
cpt suivant
Ecrire "Sur les 20 nombres que vous avez saisi, le plus grand nombre est ", max
Fin
```

## Exercice 5.9
Réécrire l’algorithme précédent, mais cette fois-ci on ne connaît pas d’avance combien l’utilisateur souhaite saisir de nombres. La saisie des nombres s’arrête lorsque l’utilisateur entre un zéro.

```sh
Variables nbre,rep, cpt, max en Entier
Début
nbre <- 0
cpt <- 0
rep <- 0
max <- 0
Ecrire "Combien de nombres voulez-vous saisir ?"
lire rep
Ecrire "Veuillez saisir ", rep , "nombres entier non nul :"
Pour cpt <- 1 à  rep
  Ecrire "Entrez le nombre numéro " , cpt , ":"
  Lire nbre
  si max <nbre alors
    max <- nbre
  finsi
cpt suivant
Ecrire "Sur les 20 nombres que vous avez saisi, le plus grand nombre est ", max
Fin
```

## Exercice 5.10
Lire la suite des prix (en euros entiers et terminée par zéro) des achats d’un client. Calculer la somme qu’il doit, lire la somme qu’il paye, et simuler la remise de la monnaie en affichant les textes "10 Euros", "5 Euros" et "1 Euro" autant de fois qu’il y a de coupures de chaque sorte à rendre.

```sh
Variables cpt,nbreArticle, prixArticle ,totalDu, sommePayé, reste ,billet10, billet5, piece1  en Entier
Variable condi en Booléen

Début
cpt <- 0
prixArticle <- 0
totalDu <- 0
sommePayé <- 0
reste <- 0
billet10 <- 0
billet5 <- 0
piece1 <- 0
nbreArticle <- 1
condi <- vrai

TantQue condi
  Ecrire "Veuillez saisir le montant de l'Article. Veuillez saisir 0 pour arreter la saisie des articles"
  lire prixArticle
    si prixArticle = 0 alors
      Ecrire "Saisie terminée."
      condi <- faux
    sinon
      totalDu <- totalDu + prixArticle
      nbreArticle <- nbreArticle + 1
    fin si
FinTantQue
Ecrire "vous avez acheté", nbreArticle, " articles. Vous nous devez: ", totalDu
Ecrire "Veuillez entrer la somme que vous payez : "
lire sommepayé

Si sommePayee < totalDu Alors
    Ecrire "La somme payée est insuffisante. Veuillez entrer une somme suffisante."
Sinon
    reste <- sommePayee - totalDu
    Ecrire "Nous vous devons ", reste, " € en monnaie."

    TantQue reste >= 10
        billet10 <- billet10 + 1
        reste <- reste - 10
    FinTantQue

    TantQue reste >= 5
        billet5 <- billet5 + 1
        reste <- reste - 5
    FinTantQue

    piece1 <- reste

    Ecrire "Rendu monnaie :"
    Ecrire "Nombre de Billets de 10€ : ", billet10
    Ecrire "Nombre de Billets de 5€ : ", billet5
    Ecrire "Nombre de Pièces de 1€ : ", piece1

FinSi
Fin
```


## Exercice 5.11
Écrire un algorithme qui permette de connaître ses chances de gagner au tiercé, quarté, quinté et autres impôts volontaires.
On demande à l’utilisateur le nombre de chevaux partants, et le nombre de chevaux joués. Les deux messages affichés devront être :
Dans l’ordre : une chance sur X de gagner
Dans le désordre : une chance sur Y de gagner
X et Y nous sont donnés par la formule suivante, si n est le nombre de chevaux partants et p le nombre de chevaux joués (on rappelle que le signe ! signifie "factorielle", comme dans l'## Exercice 5.7 ci-dessus) :
X = n ! / (n - p) !
Y = n ! / (p ! * (n – p) !)
NB : cet algorithme peut être écrit d’une manière simple, mais relativement peu performante. Ses performances peuvent être singulièrement augmentées par une petite astuce. Vous commencerez par écrire la manière la plus simple, puis vous identifierez le problème, et écrirez une deuxième version permettant de le résoudre.

```sh
Variables
Début

Fin
```
