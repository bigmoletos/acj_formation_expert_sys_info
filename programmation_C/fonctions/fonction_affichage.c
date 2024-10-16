#include <stdio.h>


void affichage(int *valeur){
    printf("\n\n************************************************\n");
    printf("Avec pointeur\nAprès inversion : valeur1 = %d\n", *valeur);
    printf("************************************************\n\n");

}


/*
// [acces] tableau
tableau[x] //: element indice X
tableau //: adresse du tableau
*tableau //: premier element du tableau
*(tableau + X) //: element d indice X
*/


// Déclaration et intialisation des variables globales avec des valeurs appropriées
int i = 0;
size_t taille_tableau = 0;

//fonction affichage tableau par pointeur

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
