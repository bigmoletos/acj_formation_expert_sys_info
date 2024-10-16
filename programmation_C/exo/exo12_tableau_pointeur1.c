#include <stdio.h>
#include <stdlib.h>
#define TAILLE_TAB 11


/* OBJECTIF

Copier un tableau à l'aide de pointeurs
Énoncé : Écris un programme qui copie les éléments d'un tableau dans un autre tableau de même taille en utilisant uniquement des pointeurs.
*/

 /* AIDE
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

int main()
{
    int tableau[TAILLE_TAB]={1,2,3,4,5,6,7,8,9,10,11};
    int tableau2[TAILLE_TAB];

    // taille du 2éme tableau
    taille_tableau=sizeof(tableau2)/sizeof(*tableau2);

    printf("taille_tableau: %d\n", taille_tableau);

    //  affichage tableau 1
    affichage_tableau(tableau2, taille_tableau);

    printf("Tableau1 :\n");
    //  copie du tableau 1 dans le tableau2 tableau 1
    copie_tableau(tableau, tableau2, taille_tableau);
    //  affichage tableau 2
    printf("Tableau2 :\n");
    affichage_tableau(tableau2, taille_tableau);


    return 0;

}
