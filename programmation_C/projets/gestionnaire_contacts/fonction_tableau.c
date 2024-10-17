#include <stdio.h>
#include <ctype.h>
#include  "proto.h"

void affichage_tableau(int *tab, size_t taille_tableau){

    printf("Tableau: ");
    for (size_t i = 0; i < taille_tableau; i++)
    {
        printf("%d", *(tab +i));
        if (i < taille_tableau - 1) {
            printf(", ");
        }

    }
    printf("\n\n");
}

void copie_tableau(int *tab1, int *tab2,size_t taille_tableau){

    for (size_t i = 0; i < taille_tableau; i++)
    {
        *(tab2 + i) =*(tab1 + i);
    }
}

void double_valeur_tableau(int *tab, size_t taille_tableau){

    for (size_t i = 0; i < taille_tableau; i++)
    {
        *(tab + i) *=2;
    }
}