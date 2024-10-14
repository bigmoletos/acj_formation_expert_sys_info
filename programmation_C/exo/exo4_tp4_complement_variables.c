#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
Quelle est le rayon du cercle?  1
Ce cercle a pour diametre 2
Ce cercle a pour circonférence 6.2832
Ce cercle a pour aire 3.1416
Quelle est la hauteur du cylindre ?  2
Ce cylindre a pour volume 6.2832
*/


/* SPOIL
1- Utilisez la fonction scanf avec %d
2- Diamètre du cercle D = R * 2
3- Circonférence du cercle C = 2 * PI * R: Attention au type !
4- Aire du cercle A = PI * R²: Attention au type !
A.1- Utilisez deux fonctions scanf avec un %d ou une fonction scanf avec deux %d
A.2- Volume d'un cylindre V = PI * R² * H
B- Volume du cône V = PI × R² × h ÷ 3
V - SPOIL! (aide)
*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées
const double PI_VAL= 3.141592653589793;  //on pourrait aussi utiliser la valeur pi de la fonctin math M_PI


int main()
{
// Déclaration et intialisation des variables globales avec des valeurs appropriées
int rayon=0 ;
int hauteur=0 ;
double diametre=0 ;
double circonference=0 ;
double aire=0 ;
double volume=0 ;
    // Affiche le titre du programme
    printf("Tp4_complement_variables\n\n");

    // saisie de la taille d'un coté
    printf("Quelle est le rayon du cercle?\t");
    scanf("%d", &rayon);

    // calculs
    diametre=2*rayon;
    circonference = 2*PI_VAL*rayon;
    // avec la constante de la fonction math
    // circonference=2 * M_PI * (float)diametre;
    aire=PI_VAL * pow(rayon, 2);
    // avec la constante de la fonction math
    // aire=M_PI* * pow(rayon, 2);
    printf("\nCe cercle a pour diametre: %0.2f cm\n",diametre );
    printf("Ce cercle a une circonference de: %0.2f cm \n",circonference );
    printf("Ce cercle a une aire de: %0.2f cm2 \n",aire );

    // saisi
    printf("\nQuelle est la hauteur du cylindre?\t");
    scanf("%d", &hauteur);
    // calcul du volume avec saisi de la hauteur
    volume = PI_VAL*pow(rayon,2)*hauteur*3;
    printf("Ce cylindre a pour volume: %0.2f cm3\n",volume );


}
