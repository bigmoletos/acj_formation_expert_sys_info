#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* Enoncé

1- Créez un tableau de 5 entiers positifs et demander à l’utilisateur de le remplir.
2- Afficher le max et le min du tableau.
3- Afficher la moyenne du tableau.
Objectifs
Remplir le tableau suivant:
tab[0]: 12
tab[1]: 1
tab[2]: 8
tab[3]: 3
tab[4]: 33
max = 33, min=1, moyenne=11.4




*/


/* SPOIL

1- Il faut faire une boucle for pour parcourir le tableau. Pour chaque case, faire un scanf
2- Faire une autre boucle for pour trouver le min le max.
3- En plus du min et du max, faire la somme des cases. Ensuite diviser cette somme par le
nombre de case pour avoir la moyenne.


*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées


int main()
{
    // Affiche le titre du programme
    printf("\n\n================================\n");
    printf("tp6-3-statistiques_exercice\n");
    printf("Statistiques\n");
    printf("================================\n\n");

    // declaration et intialisation de nos variables
    int nbre=0, somme=0, min=0, max=0 ;
    int count = 5;
    float moy = 0.0;

    int tab[5]; // intialisation tableau

// saisie clavier des variables
    for (size_t i = 0; i < count; i++)
    {
        printf("Veuillez saisir un entier positif non nul: ");
        // scanf("%d", &nbre)

        // scanf("%d",&age);
    // Controles de saisie
            //  controle de la saisie de l'age
        if (scanf("%d", &nbre) != 1 || nbre <= 0 ) {
            printf("Erreur: veuillez entrer un âge valide (nombre entier positif).\n");
            // vide le buffer
            fflush(stdin);  // Vider le tampon d'entrée en cas d'erreur
            exit(1) ;
        }else{

            tab[i] = nbre;
        }

        // calcul du min du max et de la sommme
        // initialisation de min et de max à la premiere valeur du tableau
        min = tab[0];
        max = tab[0];

    }
    for (size_t i = 0; i < count; i++)
    {
        if (tab[i]<min)
        {
            min=tab[i];
        }
        if (tab[i]>max)
        {
            max = tab[i];
        }
        // calcul de la somme
        somme += tab[i];
    }
    // calcul de la moyenne
    moy = (float)somme / count;

    printf("Valeur min= %d\nValeur max= %d\nMoyenne= %0.2f\n",min,max,moy);


    //  impression du tableau
    printf("\n================================\n");
    printf("impression du tableau\n");
    printf("================================\n\n");
    for (size_t i = 0; i < count; i++)
    {
        printf("tab[%d] = %d\n", i, tab[i]);
    }
    printf("\n================================\n\n");

    return 0;
}
