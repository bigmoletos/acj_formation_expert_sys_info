#include <stdio.h>
#include  "prototypes.h"

void affichage(int *valeur){
    printf("\n\n************************************************\n");
    printf("Premiere valeur  = %d\n", *valeur);
    printf("************************************************\n\n");

}
void affichage2valeur(int *valeur1, int *valeur2){
    printf("\n\n************************************************\n");
    printf("Résultat des 2 valeur1 : valeur1= %d, valeur2 = %d\n", *valeur1, *valeur2);
    printf("************************************************\n\n");

}


//fonction affichage tableau par pointeur

void affichage_tableau(int *tab, size_t taille_tableau){
// Déclaration et intialisation des variables globales avec des valeurs appropriées
int i = 0;
taille_tableau = 0;

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
