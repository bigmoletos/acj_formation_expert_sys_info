#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* Enoncé

1- Afficher la table de multiplication de l'entier saisie par l'utilisateur.
2- Afficher les tables de multiplications comprise entre 0 et l’entier saisie par
l’utilisateur.
Objectifs
Quelle table de multiplication afficher? 3
3x0 = 0
3x1 = 3
3x2 = 6
3x3 = 9

*/


/* SPOIL

1- Utiliser une boucle for pour faire 10 multiplications (une par ligne de la table).
2- Il faut imbriquer deux boucles. Une boucle pour les tables et une autre pour les lignes
d’une table (point 1).
Aide


*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées


int main()
{
    // Affiche le titre du programme
    printf("\n\n====================================\n");
    printf("tp7-4-6\n");
    printf("Tables de multiplication \n");
    printf("========================================\n\n");

    // declaration et intialisation de nos variables
    int nbre = 0, compteur=0, multiplicateur=10, i=0;
    int resultat = 0;

    // saisie clavier des variables
    printf("Saisissez un nombre positif non nul: ");

        // Controle de saisie
        if ( scanf("%d", &nbre) != 1 ||nbre <=0 )
        {
            printf("Veuillez saisir un nombre positif non nul ! Ce n'est pas le cas de votre saisie %d\n", nbre);
            exit(1);
        }

    // saisie clavier des variables
        printf("Quelle table de multiplication souhaitez vous? ");

        // Controle de saisie
        if ( scanf("%d", &multiplicateur) !=1 ||multiplicateur <=0)
        {
            printf("Veuillez saisir un nombre positif non nul ! Ce n'est pas le cas de votre saisie %d\n",multiplicateur);
            exit(1);
        }

    printf("\n------------------------------------\n");
    printf("Table de %d par %d\n",nbre,multiplicateur);
    printf("\n------------------------------------\n\n");

    // impression de toutes les tables de 1 à x
    for (int i = 0; i < nbre+1 ; i++)
    {
            printf("\n****************************\n");
            printf("\nAffichage de la table de %d par %d\n", i, multiplicateur);
            printf("\n****************************\n");

        for (int j = 0; j <= multiplicateur; j++)
        {
            // covir la 2éme boucle dans notre cas !!
            resultat = i * j;
            printf("%d x %d = %d\n", i, j, resultat);
        }

}


    printf("\n========================================\n\n");

    return 0;
}
