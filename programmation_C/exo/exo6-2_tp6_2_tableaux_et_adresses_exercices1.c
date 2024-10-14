#include <stdio.h>
#include <stdlib.h>


/* Enoncé


2- Pour chaque cases, afficher l’index, le contenue et d’adresse
3- Faire la même chose mais en utilisant la syntaxe par pointeur
Objectifs
tab[0] = C (0060FEF9)
tab[1] = O (0060FEFA)
tab[2] = D (0060FEFB)
tab[3] = E (0060FEFC)
tab[4] = R (0060FEFD)


*/


/* SPOIL

1- type nom[taille] = {liste_valeurs};
2- Il faut utiliser %p pour afficher une adresse mémoire dans un printf.
3- tab[i] = *(tab+i)

*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées
int i = 0;
int taille = 0;

int main()
{
    // Affiche le titre du programme
    // Affiche le titre du programme
    printf("\n\n================================\n");
    printf("TP 6 6-2-tableaux_et_adresses_exercice_1 \n");
    printf("Exo1\n");
    printf("================================\n\n");

    //  déclaration du tableau
   char tab[] = {'C', 'O', 'D', 'E', 'R'};

   // Taille du tableau
    int taille = sizeof(tab) / sizeof(tab[0]);


    // Affichage des index, contenu et adresses version normale
    printf("Affichage classique avec tab[i]:\n");
    for (int i = 0; i < taille; i++) {
        printf("tab[%d] = %c (%p)\n", i, tab[i], (void*)&tab[i]);
    }

    // Affichage des index, contenu et adresses version par pointeur
    printf("\nAffichage avec les pointeurs *(tab + i):\n");
    for (int i = 0; i < taille; i++) {
        printf("*(tab + %d) = %c (%p)\n", i, *(tab + i), (void*)(tab + i));
    }

    return 0;

}
