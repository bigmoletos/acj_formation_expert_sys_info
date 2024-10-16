#include <stdio.h>
#include <ctype.h>

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

    printf("\n");
    printf("Tableau: ");
    for (size_t i = 0; i < taille_tableau; i++)
    {
        printf("%d", *(tab1 +i));
        if (i < taille_tableau - 1) {
            printf(", ");

        }
        *(tab2 + i) =*(tab1 + i);

    }
    printf("\n\n");
}

void double_valeur_tableau(int *tab, size_t taille_tableau){

    printf("\n");
    printf("Tableau: ");
    for (size_t i = 0; i < taille_tableau; i++)
    {
        printf("%d", *(tab +i));
        if (i < taille_tableau - 1) {
            printf(", ");

        }
        *(tab + i) *=2;

    }
    printf("\n\n");
}