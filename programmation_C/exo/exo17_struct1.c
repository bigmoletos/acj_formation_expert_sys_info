#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_NAME 20


/*
Exercice Exercice 1 : Définir et afficher une structure de personne

Énoncé : Déclare une structure Personne qui contient un nom, un âge et une taille. Crée ensuite une variable de type Personne, demande à l'utilisateur d'entrer les informations et affiche-les.
 */

// creation de la strucute personne
typedef struct Personne
{
    char name[TAILLE_NAME];
    int age;
    float taille;
} Agent;

//fonction pour creer un agent type
void create_agent_type(Agent *a) {
    strcpy(a->name, "ELDUE");
    a->age = 123;
    a->taille = 2.28;
};

int main(void){

    //Creation Agent1
    Agent Agent1 ;

    printf("veuillez saisir le nom de l'agent: ");
    // scanf("%[^\n]", Agent1.name);
    // Vérifier la saisie et les conditions
    if (scanf(" %19[^\n]", Agent1.name) == 1 && strlen(Agent1.name) >  2 && strlen(Agent1.name) <  TAILLE_NAME) {
        while (getchar() != '\n'); //vide le buffer
        return Agent1.name;  //  renvoyer la chaine sasie
    } else {
        printf("Saisie incorrecte. Veuillez entrer une chaine  de %zu characteres max et 2 mini .\n", TAILLE_NAME);
        // Vider le buffer en cas de mauvaise saisie
        while (getchar() != '\n');
    }

    printf("veuillez saisir l'age de l'agent: ");
    scanf("%d", &Agent1.age);

    printf("veuillez saisir la taille de l'agent: ");
    scanf("%f", &Agent1.taille);

//affichage Agent1
    printf("Carte de l'agent: \nNom: %s\nAge: %d\nTaille: %0.2f\n",Agent1.name,Agent1.age,Agent1.taille);

    //utilization de la focntion create_agent_type
    Agent Agent2;
    create_agent_type(&Agent2);

//affichage Agent2
    printf("Carte de l'agent type : \nNom: %s\nAge: %d\nTaille: %0.2f\n",Agent2.name,Agent2.age,Agent2.taille);

    return 0;
 }
