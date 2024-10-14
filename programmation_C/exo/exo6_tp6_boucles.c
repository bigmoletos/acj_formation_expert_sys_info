#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


/* Enoncé

Nous allons créer un petit jeu de type “Pierre Feuille Ciseaux”. Le joueur vas jouer contre l’ordinateur.
Cela signifie donc que l’on vas générer aléatoirement ce que joue l’ordinateur.
Pour simplifier les choses, le jeu se fait en 3 manches gagnantes. De plus, pour la saisie utilisateur nous
allons lire un entier (1- Pierre, 2- Papier, 3- Ciseaux)
Que voulez vous jouer (1- Pierre, 2- Papier, 3- Ciseaux): 1
Joueur joue 1 et ordinateur joue 1 >>>> match null
Points: Ordi: 0 et joueur: 0
Que voulez vous jouer (1- Pierre, 2- Papier, 3- Ciseaux): 1
Joueur joue 1 et ordinateur joue 3 >>>>  Joueur gagne 1 point
Points: Ordi: 0 et joueur: 1
Que voulez vous jouer (1- Pierre, 2- Papier, 3- Ciseaux):
Objectifs
A- Ajouter un compteur qui indique combien de manches chacuns a gagnés.
B- Gérer la fin de partie (3 manches gagnés)
Pour aller plus loin


*/


/* SPOIL

1- Il faut comparer les deux entiers joués. Si il sont égaux, on à un match null, sinon, il faut
tester les cas de victoire du joueur. Enfin, tous les autres, sont des victoires de l’ordinateur.
2- Utiliser une boucle do while sur la saisie utilisateur
A- Il faut créer un compteur de victoire par joueurs, donc deux.
B- Vérifier si l’ordinateur ou le joueur a son compteur de victoire qui arrive à 3.
Aide

*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées
int nbre1=0 ;
int nbre2=0 ;
int resultat=0 ;
char operateur_type;

int main()
{
    // Affiche le titre du programme
    printf("TP 6 Pierre Feuille Ciseaux\n");
    printf("les boucles\n\n");

    // declaration d'un chiffre aléatoire
    srand(time(NULL));
    // declaration de nos variables
    int jeu_ordinateur = 0, jeu_utilisateur = 0;
    const int VALEUR_MIN = 1, VALEUR_MAX = 3;
    // generation d'un nombre aleatoire
    jeu_ordinateur = (rand() % VALEUR_MAX) + VALEUR_MIN;

    // saisies



}
