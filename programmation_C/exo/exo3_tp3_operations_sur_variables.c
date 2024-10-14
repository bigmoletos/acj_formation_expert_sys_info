#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Quelle est la taille d’un cote du carre?  1
// Ce carre a pour perimetre 4
// Ce carre a pour surface 1


/* SPOIL
1- Utilisez la fonction scanf avec %d
2- Périmètre d’un carré = 4*côté
3- Surface d’un carré = côté*côté
4- Utilisez la fonction printf avec %d
A.1- Utilisez deux fonctions scanf avec un %d ou une fonction scanf avec deux %d
A.2- (P = 2*H + 2*L)
A.3- (S = L*H)
*/
// Déclaration des variables globales avec des valeurs appropriées
int largeur_cote ;              // Valeur entière
int perimetre_carre ;              // Valeur entière
int surface_carre ;              // Valeur entière

int main()
{
    // Affiche le titre du programme
    printf("TP3: operations sur variables \n\n");

    // saisie de la taille d'un coté
    printf("Quelle est la taille d’un cote du carre? \n");
    scanf("%d", &largeur_cote);

    // calcul du perimetre et de la surface du carré
    perimetre_carre = largeur_cote * 4;
    surface_carre = largeur_cote * largeur_cote;
    printf("Ce carre a pour perimetre  %d \n",perimetre_carre );
    printf("Ce carre a pour surface  %d \n",surface_carre );



}
