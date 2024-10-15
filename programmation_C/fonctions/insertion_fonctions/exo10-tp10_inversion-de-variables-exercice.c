#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "prototypes.h"  //integration du header contenant les fonctions controle de saisi et sortie prog


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

// Déclaration et intialisation des variables globales avec des valeurs appropriées
int temp;

// Fonction d'inversion de 2 valeurs avec pointeurs
void inverser_valeurs(int *val1, int *val2) {
    int temp = *val1; // variable tampon
    *val1 = *val2;
    *val2 = temp;
}
// Fonction d'inversion de 2 valeurs sans pointeurs en passant par 2 fonctins
int inverser_valeurs_sans_pointeur(int val10, int val20) {
    int temp2 = val10; // variable tampon
    val10 = val20;
    val20 = temp2;
    return val10;
}



int main()
{
    char quitter = 'n';  // Initialisation pour que le programme commence

   do
   {
    // Affiche le titre du programme
    printf("\n\n=====================================\n");
    printf("tp10-les fonctions\n");
    printf("Inversion de 2 valeurs\n");
    printf("========================================\n\n");

    // Déclaration et initialisation de nos variables
    int valeur1 = 0, valeur2 = 0;
    int valeur10 =0, valeur20 =0;


    // Saisie des valeurs avec contrôle, appel à la fonction importée
    valeur1 = saisir_entier(100);
    valeur2 = saisir_entier(100);

    // Affichage des valeurs avant inversion
    printf("*************************************************\n");
    printf("Avant inversion : valeur1 = %d, valeur2 = %d\n", valeur1, valeur2);


    // Utilisation de la fonction d'inversion des valeurs avec pointeur
    inverser_valeurs(&valeur1, &valeur2);

    // Utilisation de la fonction d'inversion des valeurs sans pointeur
    valeur10 = inverser_valeurs_sans_pointeur(valeur1, valeur2);
    valeur20 = valeur1;  //bon ok c'est un peu de la triche !!

    // Affichage des valeurs après l'inversion
    printf("************************************************\n");
    printf("Avec pointeur\nAprès inversion : valeur1 = %d, valeur2 = %d\n", valeur1, valeur2);
    printf("Sans Pointeur\nAprès inversion : valeur1 = %d, valeur2 = %d\n", valeur10, valeur20);
    printf("************************************************\n");

    // Gestion de la sortie (Oui/Non) avec appel à la fonction importée
    if (demander_quitter() == 'o') {
        printf("Vous avez choisi de quitter le programme. Au revoir !\n");
        quitter = 'o';
    } else {
        printf("Vous avez choisi de continuer.\n");
    }
   } while (quitter == 'n');

    return 0;


}
