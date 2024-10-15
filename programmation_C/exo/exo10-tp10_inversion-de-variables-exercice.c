#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>


/* Enoncé
1- Créer une fonction qui permet d’inverser le contenue de deux entiers passés
en paramètre.
2- Afficher les entiers dans la fonction main, avant et après utilisation de la
fonction du point 1
Objectifs
var1 = 12 et var2 = 9
Inversion ...
var1 = 9 et var2 = 12

*/


/* SPOIL



*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées
int temp;

// Fonction d'inversion de 2 valeurs
void inverser_valeurs(int *val1, int *val2) {
    int temp = *val1; // variable tampon
    *val1 = *val2;
    *val2 = temp;
}


int main()
{
    // Affiche le titre du programme
    printf("\n\n====================================\n");
    printf("tp10-les fonctinos\n");
    printf("Inversion des valeurs\n");
    printf("========================================\n\n");

    // Déclaration et initialisation de nos variables
    int valeur1 = 0, valeur2 = 0;

    // Saisie clavier des variables
    printf("Quel est votre choix de votre 1 er valeur : ");

        // Contrôle de saisie
        if (scanf("%d", &valeur1) != 1 || valeur1 >= 100)
        {
            printf("Veuillez saisir une valeur positive et inférieure à 100.\n");
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
            return 1;
        }

    // Saisie clavier des variables
    printf("Quel est votre choix de votre 2éme valeur : ");

        // Contrôle de saisie
        if (scanf("%d", &valeur2) != 1 || valeur2 >= 100)
        {
            printf("Veuillez saisir une valeur positive et inférieure à 100.\n");
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
            return 1;
        }

    // Affichage des valeurs avant inversion
    printf("Avant inversion : valeur1 = %d, valeur2 = %d\n", valeur1, valeur2);


    printf("Valeur de val1 : %d\n", valeur1);// Affiche la valeur de 'val1'


    printf("Adresse de val1 : %p\n", (void*)&valeur1); // Affiche l'adresse de 'a'
    printf("Adresse stockée dans pointeur : %p\n", (void*)valeur1);  // Affiche l'adresse stockée dans le pointeur
    printf("Valeur pointée par pointeur : %d\n", *valeur1); // Affiche la valeur pointée par le pointeur


    // Utilisation de la fonction d'inversion des valeurs
    inverser_valeurs(&valeur1, &valeur2);

    // Affichage des valeurs après l'inversion
    printf("Après inversion : valeur1 = %d, valeur2 = %d\n", valeur1, valeur2);

    return 0;

}
