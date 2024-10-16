#include <stdio.h>
#include <stdlib.h>
#define TAILLE_TAB  11


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

    printf("\n");
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

int main()
{
    int tableau[TAILLE_TAB]={1,2,3,4,5,6,7,8,9,10,11};
    int tableau2[]={1,2,3,4,5,6,7,8,9,10,11};

    // taille du 2éme tableau
    taille_tableau=sizeof(tableau2)/sizeof(*tableau2);

    printf("taille_tableau: %d\n", taille_tableau);
    printf("\n");
    // affichage tableau version classique
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
//************************************************************************************************ */
    // idem avec utilisation d'une fonction popur afficher le tableau
    // printf(" Modification du tableau :\n");
    affichage_tableau(tableau2, taille_tableau);

    printf("Modification du tableau :\n");
    tableau[5] = 455555;

    affichage_tableau(tableau2, taille_tableau);


    return 0;

}
