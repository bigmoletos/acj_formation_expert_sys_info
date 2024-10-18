#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
Exercice Exercice 1 : Définir et afficher une structure de personne

Énoncé : Déclare une structure Personne qui contient un nom, un âge et une taille. Crée ensuite une variable de type Personne, demande à l'utilisateur d'entrer les informations et affiche-les.
 */


struct Personne
{
    char* name;
    int age;
    int taille;
    printf("veuillez saisir le nom de l'agent");
    scanf("%[^\n]", &name);
    printf("veuillez saisir l'age de l'agent");
    scanf("%[^\n]", &age);

    printf("veuillez saisir la taille de l'agent");
    scanf("%[^\n]", &taille);
} Agent;

int main(){
    // char *nom;
    // int age;
    // int taille;




    Agent Agent1 = {"luis", "91", "2.26"};
    Agent Agent1 = {"luis", "91", "2.26"};

    printf("Carte de l'agent. \nNom: %s\nAge: %d\nTaille: %d8n",Agent1.name,Agent1.age,Agent1.taille);

    return 0;
 }
