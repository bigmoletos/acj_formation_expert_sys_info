#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* Enoncé

Nous allons créer un petit jeu de type “Pierre Feuille Ciseaux”. Le joueur va jouer contre l’ordinateur.
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


int main()
{
    // Affiche le titre du programme
    printf("TP 6 Pierre Feuille Ciseaux\n");
    printf("les boucles\n\n");

    // declaration d'un chiffre aléatoire
    srand(time(NULL));
    // declaration et intialisation de nos variables
    int victoire_player1=0 ;
    int victoire_ordinateur=0 ;
    int jeu_joueur=0 ;
    int jeu_ordinateur = 0;
    // int compteur = 0;
    char resultat[]="X" ;
    const int VALEUR_MIN = 1, VALEUR_MAX = 3;

    // generation d'un nombre aleatoire
    jeu_ordinateur = (rand() % VALEUR_MAX) + VALEUR_MIN;


// le jeu ne peut se faire qu'en 3 manches
    while (victoire_ordinateur<VALEUR_MAX && victoire_player1<VALEUR_MAX){

        // saisies
        printf("Que voulez vous jouer (1- Pierre, 2- Papier, 3- Ciseaux) ?\n\n");
        scanf("%d", &jeu_joueur);

        if (!jeu_joueur==1 || !jeu_joueur==2 || !jeu_joueur==3){
            printf("Vous avez avez fait une erreur de saise, vous ne pouvez saisir que 1,2 ou 3");

        }else{

            if (jeu_joueur==jeu_ordinateur)
            {
                strcpy(resultat, "match nul");
                // printf("%s\n",resultat);
            // le joueur gagne si papier-2 sur pierre-1, ciseaux-3 sur papier-2, pierre-1 sur ciseaux-3
            }else if ((jeu_joueur==1 && jeu_ordinateur==3) || (jeu_joueur==2 && jeu_ordinateur==1) || (jeu_joueur==3 && jeu_ordinateur==2))
            {
                strcpy(resultat, "le joueur gagne la partie");
                // printf("%s\n",resultat);
                victoire_player1++;
            }else
            {
                strcpy(resultat, "l'ordinateur gagne la partie");
                victoire_ordinateur++;
                // printf("%s\n",resultat);
            }


            printf("Joueur joue %d et ordinateur joue %d >>>> %s", jeu_joueur, jeu_ordinateur, resultat);
        }
        if (victoire_ordinateur < victoire_player1)
        {
            strcpy(resultat, "l'ordinateur gagne le match");
            printf("%s\n",resultat);
        }else {
            strcpy(resultat, "le joueur gagne le match");
            printf("%s\n",resultat);

        }


    printf("%s\n",resultat);
    printf(" Points: Ordi: %d et joueur: %d", victoire_ordinateur, victoire_player1);
            // compteur++;
    }

}
