# Parti 4 Encore de la Logique
## Exercice 4.1
Formulez un algorithme équivalent à l’algorithme suivant :
Si Tutu > Toto + 4 OU Tata = "OK" Alors
  Tutu ← Tutu + 1
Sinon
  Tutu ← Tutu – 1
Finsi
```sh
Variables tutu, Toto en Caractères
Début
Si Tutu <= Toto + 4 ET Tata ≠ "OK" Alors
    Tutu ← Tutu – 1
Sinon
    Tutu ← Tutu + 1

FinSi
Fin
```

## Exercice 4.2
Cet algorithme est destiné à prédire l'avenir, et il doit être infaillible !
Il lira au clavier l’heure et les minutes, et il affichera l’heure qu’il sera une minute plus tard. Par exemple, si l'utilisateur tape 21 puis 32, l'algorithme doit répondre :
"Dans une minute, il sera 21 heure(s) 33".
NB : on suppose que l'utilisateur entre une heure valide. Pas besoin donc de la vérifier.
```sh
Variables heure, minutes en Numérique
Début
Ecrire "Entrez l'heure :"
Lire heure
Ecrire "Entrez les minutes :"
Lire minutes
minutes ← minutes + 1
Si minutes = 60 Alors
minutes ← 0
heure ← heure + 1
Si heure = 24 Alors
heure ← 0
FinSi
FinSi
Ecrire "Dans une minute, il sera ", heure, " heure(s) ", minutes
Fin

```

## Exercice 4.3
De même que le précédent, cet algorithme doit demander une heure et en afficher une autre. Mais cette fois, il doit gérer également les secondes, et afficher l'heure qu'il sera une seconde plus tard.
Par exemple, si l'utilisateur tape 21, puis 32, puis 8, l'algorithme doit répondre : "Dans une seconde, il sera 21 heure(s), 32 minute(s) et 9 seconde(s)".
NB : là encore, on suppose que l'utilisateur entre une date valide.



```sh
Variables heure, minutes, secondes en Numérique
Début
Ecrire "Entrez l'heure :"
Lire heure
Ecrire "Entrez les minutes :"
Lire minutes
Ecrire "Entrez les secondes :"
Lire secondes
secondes ← secondes + 1
Si secondes = 60 Alors
secondes ← 0
minutes ← minutes + 1
Si minutes = 60 Alors
minutes ← 0
heure ← heure + 1
Si heure = 24 Alors
heure ← 0
FinSi
FinSi
FinSi
Ecrire "Dans une seconde, il sera ", heure, " heure(s), ", minutes, " minute(s) et ", secondes, " seconde(s)"
Fin

```

## Exercice 4.4
Un magasin de reprographie facture 0,10 E les dix premières photocopies, 0,09 E les vingt suivantes et 0,08 E au-delà. Ecrivez un algorithme qui demande à l’utilisateur le nombre de photocopies effectuées et qui affiche la facture correspondante.
```sh
Variables nb_photos, total en Numérique
Début
Ecrire "Entrez le nombre de photocopies :"
Lire nb_photos
Si nb_photos <= 10 Alors
total ← nb_photos * 0.10
Sinon Si nb_photos <= 30 Alors
total ← 10 * 0.10 + (nb_photos - 10) * 0.09
Sinon
total ← 10 * 0.10 + 20 * 0.09 + (nb_photos - 30) * 0.08
FinSi
Ecrire "Le montant total est : ", total, " €"
Fin

```

## Exercice 4.5
Les habitants de Zorglub paient l’impôt selon les règles suivantes :
les hommes de plus de 20 ans paient l’impôt
les femmes paient l’impôt si elles ont entre 18 et 35 ans
les autres ne paient pas d’impôt
Le programme demandera donc l’âge et le sexe du Zorglubien, et se prononcera donc ensuite sur le fait que l’habitant est imposable.
```sh
Variables age en Numérique, sexe en Caractère
Début
Ecrire "Entrez l'âge :"
Lire age
Ecrire "Entrez le sexe (H ou F) :"
Lire sexe
Si sexe = "H" et age > 20 Alors
Ecrire "Vous êtes imposable"
Sinon Si sexe = "F" et age >= 18 et age <= 35 Alors
Ecrire "Vous êtes imposable"
Sinon
Ecrire "Vous n'êtes pas imposable"
FinSi
Fin

```

## Exercice 4.6
Les élections législatives, en Guignolerie Septentrionale, obéissent à la règle suivante :
lorsque l'un des candidats obtient plus de 50% des suffrages, il est élu dès le premier tour.
en cas de deuxième tour, peuvent participer uniquement les candidats ayant obtenu au moins 12,5% des voix au premier tour.
Vous devez écrire un algorithme qui permette la saisie des scores de quatre candidats au premier tour. Cet algorithme traitera ensuite le candidat numéro 1 (et uniquement lui) : il dira s'il est élu, battu, s'il se trouve en ballottage favorable (il participe au second tour en étant arrivé en tête à l'issue du premier tour) ou défavorable (il participe au second tour sans avoir été en tête au premier tour).
```sh
Variables score1, score2, score3, score4 en Numérique
Début
Ecrire "Entrez le score du candidat 1 :"
Lire score1
Ecrire "Entrez le score du candidat 2 :"
Lire score2
Ecrire "Entrez le score du candidat 3 :"
Lire score3
Ecrire "Entrez le score du candidat 4 :"
Lire score4
Si score1 > 50 Alors
Ecrire "Le candidat 1 est élu dès le premier tour"
Sinon Si score1 < 12.5 Alors
Ecrire "Le candidat 1 est battu"
Sinon Si score1 >= score2 et score1 >= score3 et score1 >= score4 Alors
Ecrire "Le candidat 1 est en ballottage favorable"
Sinon
Ecrire "Le candidat 1 est en ballottage défavorable"
FinSi
Fin

```

## Exercice 4.7
Une compagnie d'assurance automobile propose à ses clients quatre familles de tarifs identifiables par une couleur, du moins au plus onéreux : tarifs bleu, vert, orange et rouge. Le tarif dépend de la situation du conducteur :
un conducteur de moins de 25 ans et titulaire du permis depuis moins de deux ans, se voit attribuer le tarif rouge, si toutefois il n'a jamais été responsable d'accident. Sinon, la compagnie refuse de l'assurer.
un conducteur de moins de 25 ans et titulaire du permis depuis plus de deux ans, ou de plus de 25 ans mais titulaire du permis depuis moins de deux ans a le droit au tarif orange s'il n'a jamais provoqué d'accident, au tarif rouge pour un accident, sinon il est refusé.
un conducteur de plus de 25 ans titulaire du permis depuis plus de deux ans bénéficie du tarif vert s'il n'est à l'origine d'aucun accident et du tarif orange pour un accident, du tarif rouge pour deux accidents, et refusé au-delà
De plus, pour encourager la fidélité des clients acceptés, la compagnie propose un contrat de la couleur immédiatement la plus avantageuse s'il est entré dans la maison depuis plus de cinq ans. Ainsi, s'il satisfait à cette exigence, un client normalement "vert" devient "bleu", un client normalement "orange" devient "vert", et le "rouge" devient orange.
Ecrire l'algorithme permettant de saisir les données nécessaires (sans contrôle de saisie) et de traiter ce problème. Avant de se lancer à corps perdu dans cet exercice, on pourra réfléchir un peu et s'apercevoir qu'il est plus simple qu'il n'en a l'air (cela s'appelle faire une analyse !)
```sh


```

## Exercice 4.8
Ecrivez un algorithme qui a près avoir demandé un numéro de jour, de mois et d'année à l'utilisateur, renvoie s'il s'agit ou non d'une date valide.
Cet exercice est certes d’un manque d’originalité affligeant, mais après tout, en algorithmique comme ailleurs, il faut connaître ses classiques ! Et quand on a fait cela une fois dans sa vie, on apprécie pleinement l’existence d’un type numérique « date » dans certains langages…).
Il n'est sans doute pas inutile de rappeler rapidement que le mois de février compte 28 jours, sauf si l’année est bissextile, auquel cas il en compte 29. L’année est bissextile si elle est divisible par quatre. Toutefois, les années divisibles par 100 ne sont pas bissextiles, mais les années divisibles par 400 le sont. Ouf !
Un dernier petit détail : vous ne savez pas, pour l’instant, exprimer correctement en pseudo-code l’idée qu’un nombre A est divisible par un nombre B. Aussi, vous vous contenterez d’écrire en bons télégraphistes que A divisible par B se dit « A dp B ».

```sh
Variables jour, mois, annee en Numérique
Début
Ecrire "Entrez le jour :"
Lire jour
Ecrire "Entrez le mois :"
Lire mois
Ecrire "Entrez l'année :"
Lire annee
Si (mois = 2) Alors
Si (annee dp 4 et (non annee dp 100 ou annee dp 400)) Alors
Si jour <= 29 Alors
Ecrire "Date valide"
Sinon
Ecrire "Date non valide"
FinSi
Sinon Si jour <= 28 Alors
Ecrire "Date valide"
Sinon
Ecrire "Date non valide"
FinSi
Sinon Si mois est dans {4, 6, 9, 11} Alors
Si jour <= 30 Alors
Ecrire "Date valide"
Sinon
Ecrire "Date non valide"
FinSi
Sinon
Si jour <= 31 Alors
Ecrire "Date valide"
Sinon
Ecrire "Date non valide"
FinSi
FinSi
Fin

```