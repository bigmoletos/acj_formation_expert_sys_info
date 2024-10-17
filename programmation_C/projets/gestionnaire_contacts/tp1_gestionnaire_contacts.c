#include <stdio.h>
#include <stdlib.h>
#include "proto.h"
#define TAILLE_NOM 20
#define TAILLE_TEL 10
/* Enoncé


--- Gestionnaire de Contacts ---
1. Ajouter un contact
2. Rechercher un contact
3. Afficher tous les contacts
4. Supprimer un contact
5. Quitter

Choisissez une option: 5
Quitter le programme.


*/


/* SPOIL

utiliser 2 tableaux 1 pour les noms et un pour les telephones
utiliser des fonctionss avec proto
ne pas utiliser struct


*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées
int i = 0;
int taille = 0;

int main()
{


    char contacts[TAILLE_NOM] ;
    char telephones[TAILLE_TEL] ;
    size_t taille_chaine = 0;
    size_t taille_chaine2 = 0;
    // Affiche le titre du programme
    // Affiche le titre du programme
    printf("\n\n================================\n");
    printf("Projet Tableaux - String\n");
    printf("----Gestionnaire de contact------\n");
    printf("================================\n\n");

    //  déclaration du tableau
   char tab[] = {'C', 'O', 'D', 'E', 'R'};

   // Taille du tableau
    int taille = sizeof(tab) / sizeof(tab[0]);
print

    // Affichage des index, contenu et adresses version normale
    printf("Affichage classique avec tab[i]:\n");
    for (int i = 0; i < taille; i++) {
        printf("tab[%d] = %c (%p)\n", i, tab[i], (void*)&tab[i]);s
    }

    // Affichage des index, contenu et adresses version par pointeur
    printf("\nAffichage avec les pointeurs *(tab + i):\n");
    for (int i = 0; i < taille; i++) {
        printf("*(tab + %d) = %c (%p)\n", i, *(tab + i), (void*)(tab + i));
    }

    return 0;

}
