#include <stdio.h>
#include <stdlib.h>
#define TAILLE_TAB  11


/* Enoncé

1- Créez un tableau de 5 entiers et initialisez le
2- Afficher le contenue du tableau
3- Afficher le contenue du tableau dans l’ordre inverse
Objectifs
Tableau: 1 2 3 4 5
Inverse: 5 4 3 2 1



*/


/* SPOIL
1- type nom[] = {liste_valeurs}; ou type nom[taille];
2- Il faut faire une boucle for pour parcourir le tableau. Attention, la première case est à
l’indexe 0!
3- Il faut parcourir le tableau dans le sens inverse on commence alors à l’index n-1 .
Aide

*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées
int i = 0;
int taille = 0;

//fonction affichage tableau par pointeur

void affichage_tableau(int tab[], size_t taille_tableau){

    for (size_t i = 0; i < taille_tableau; i++)
    {
        printf("Tableau\n");
        printf("%d", tab[i]);
    }

}

int main()
{
    // Affiche le titre du programme
    printf("\n\n================================\n");
    printf("TP 6 6-1-Affichage de tableaux_exercice_1 \n");
    printf("Exo1 Tableau inverse\n");
    printf("================================\n\n");

    //  déclaration du tableau
   int tab[] = {1,2,3,4,5};

   // Taille du tableau
    int taille = sizeof(tab) / sizeof(tab[0]);
    printf("\nTaille du tableau %d\n", taille);

    // Affichage du tableau
    printf("Affichage du tableau:\n");
    for (int i = 0; i < taille; i++) {
        printf("tab[%d] = %d\n", i, tab[i]);
    }

    // Affichage inverse du tableau
    printf("Affichage inverse du tableau:\n");
    for (int i = taille-1; i >= 0; i--) {
        printf("tab[%d] = %d\n", i, tab[i]);
    }


//############################################################
    // solution avec un #define TAILLE_TAB 11
    int tableau[TAILLE_TAB]={1,2,3,4,5,6,7,8,9,10,11};
    size_t taille_tableau=sizeof(taille_tableau)/sizeof(*tableau);
    printf("taille_tableau: %d\n", taille_tableau);

        printf("[ ");
    for ( i = 0; i < TAILLE_TAB; i++)
    {
        printf("%d",  tableau[i]);
         if (i < TAILLE_TAB - 1) {
            printf(" , ");
        }
        // printf("\n\n");
        tableau[2] = 99;
    }
        printf(" ]");
        printf("\n\n");

    printf("[ ");
    for (i = 0; i < TAILLE_TAB; i++) {
        printf("%d", tableau[i]);
        if (i < TAILLE_TAB - 1) {
            printf(" , ");
        }
    }
    printf(" ]\n");

// idem avec utilisation d'une fonction popur afficher le tableau
affichage_tableau(tableau, taille_tableau);



    return 0;

}
