#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Exercice 1 : Déclaration et utilisation de pointeurs simples
// Énoncé : Déclare un entier x, un pointeur vers un entier, et modifie la valeur de x à travers le pointeur.

void exo_one(){
int mon_entier=0;// Déclare un entier
int *pointeur=NULL; // initialise un pointeur
printf("Exercice 1: mon_entier = %d\n", mon_entier);
pointeur=&mon_entier;// Déclare un pointeur vers un entier
printf("Avant modification mon_entire = %d\n", mon_entier);
*pointeur = 256;  //modifie la valeur de x à travers le pointeur.
printf("Avant modification mon_entire = %d\n", mon_entier);
}

// Exercice 2 : Pointeur de pointeur
// Énoncé : Crée un programme qui déclare un entier, un pointeur vers cet entier, et un pointeur vers ce pointeur. Modifie la valeur de l'entier en utilisant le pointeur de pointeur.

void exo_two(){
int mon_entier=0;// Déclare un entier
int *pointeur1=NULL; // initialise un pointeur
int **pointeur2 = &pointeur1;// pointeur de pointeur1
printf("Exercice 2: mon_entier = %d\n", mon_entier);
printf("Avant modification mon_entire = %d\n", mon_entier);
pointeur1=&mon_entier;// Déclare un pointeur vers un entier
**pointeur2 = 455;  //modifie la valeur de x à travers le pointeur.
printf("Avant modification mon_entire = %d\n", mon_entier);
}



// Exercice 3 : Pointeur sur fonction
// Énoncé : Déclare une fonction qui prend deux entiers en paramètres et renvoie leur somme. Utilise un pointeur sur fonction pour appeler cette fonction.

int exo_three(int *val1, int *val2){

    int somme = 0;
    somme = *val1 + *val2;
    return somme;
}
//corrigé
int exo_three_bis(int val1, int val2){

    int somme = 0;
    somme = val1 + val2;
    return somme;
}

// Exercice 4
/* Écrire une programme qui

déclare un entier var et l'initialise à 18 ;
déclare un pointeur d'entier adresse ;
affecte l'adresse de var au pointeur ;
affiche var
affiche la variable pointée par adresse (*adresse).
*/

void exo_four(){
int mon_entier=18;// Déclare un entier et l'initialize
int *adresse=NULL; // initialise un pointeur
adresse=&mon_entier;// Déclare un pointeur vers un entier
printf("mon entier : %d\n", mon_entier);
printf("affiche la variable pointée par adresse: %d\n", *adresse);
}


/* Exercice 5
Écrire une programme qui

déclare un entier var et l'initialise à 27 ;
déclare un pointeur d'entier adresse ;
affecte l'adresse de varau pointeur ;
affiche l'adresse contenue dans le pointeur ;
ajoute 1 au pointeur ;
affiche l'adresse contenue dans le pointeur

*/

void exo_five(){
int mon_entier=27;// Déclare un entier et l'initialize
int *adresse=NULL; // initialise un pointeur

adresse=&mon_entier;// Déclare un pointeur vers un entier

printf("affiche l'adresse contenue dans le pointeur %p\n",  (void*)adresse);
printf("affiche la valeur du pointeur: %d\n",  *adresse);

adresse++; // ajoute 1 au pointeur ;

printf("affiche l'adresse contenue dans le pointeur: %p\n",  (void*)adresse);
printf("affiche la valeur du pointeur: %d\n",  *adresse);
}


int main() {
    // Test de chaque exercices
    printf("Test de l'exercice 1:\n");
    exo_one();

    printf("\nTest de l'exercice 2:\n");
    exo_two();

    printf("\nTest de l'exercice 3:\n");
    int a = 5, b = 10;
    int resultat = exo_three(&a, &b);
    printf("Exercice 3: Somme de %d et %d = %d\n", a, b, resultat);

    printf("\n Corrigé Test de l'exercice 3:\n");
    int (*fonct_pointeur)(int, int) = exo_three_bis; //déclaraion d'un pointeur de fonction
    int resultat_bis = fonct_pointeur(5, 23);
    printf("\n resultat addition 3: %d\n", resultat_bis);

    printf("\nTest de l'exercice 4:\n");
    exo_four();

    printf("\nTest de l'exercice 5:\n");
    exo_five();

    return 0;
}
