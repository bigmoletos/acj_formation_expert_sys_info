#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_NAME 20


/*
Exercice Exercice 1 : Définir et afficher une structure de personne

Énoncé : Déclare une structure Personne qui contient un nom, un âge et une taille. Crée ensuite une variable de type Personne, demande à l'utilisateur d'entrer les informations et affiche-les.
 */


struct Personne
{
    char name[TAILLE_NAME];
    int age;
    float taille;
} Agent;

int main(void){

    struct Personne Agent1;
    // Agent Agent1 ;

    printf("veuillez saisir le nom de l'agent: ");
    scanf("%[^\n]", Agent1.name);
    printf("veuillez saisir l'age de l'agent: ");
    scanf("%d", &Agent1.age);

    printf("veuillez saisir la taille de l'agent: ");
    scanf("%f", &Agent1.taille);



    // Agent Agent1 = {"luis", "91", "2.26"};

    printf("Carte de l'agent: \nNom: %s\nAge: %d\nTaille: %0.2f\n",Agent1.name,Agent1.age,Agent1.taille);

    return 0;
 }
