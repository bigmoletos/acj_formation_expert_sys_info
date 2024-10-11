# Lecture ecriture
# EXo 2.1 à 2.4

## exo 2.1
231
462
## exo 2.2
### Ecrire un programme qui demande un nombre à l’utilisateur, puis qui calcule et  affiche le carré de ce nombre.
Variables nombre, carre numériques
Début
Ecrire "Entrez un nombre :"
Lire nombre
Carre ← nombre * nombre  // Calcul du carré
Ecrire "Le carré du nombre est : ", carre
Fin
## exo 2.3
### Écrire un programme qui demande son prénom à l'utilisateur et affiche un message de salutation.


Variables prenom en Caractères
Début
Ecrire "Quel est ton prénom ?"
Lire prenom
Ecrire "Bonjour, ", prenom, " je suis content de te revoir !"
Fin
## exo 2.4
### Ecrire un programme qui lit le prix HT d’un article, le nombre d’articles et le taux de TVA, et qui fournit le prix total TTC correspondant. Faire en sorte que des libellés apparaissent clairement.

Variables tva, prix_ht, nombre_article, prix_ttc
Début
Ecrire "Quel est le prix de ce produit ht"
lire prix_ht
Ecrire "Quel est le nombre d'articles?"
lire nombre_article
Ecrire "Quel est le taux de TVA (en %) ?"
lire tva
prix_ttc=prix_ht*nombre_acrticles*(1+taux/100)
Ecrire "le prix total TTC = ", prix_ttc, "€"
Fin

