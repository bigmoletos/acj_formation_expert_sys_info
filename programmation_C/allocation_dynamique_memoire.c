#include <stdio.h>
#include <stdlib.h>

int nombrejoueurs = 0;  // Variable pour stocker le nombre de joueurs
int *liste_joueurs = NULL;  // Pointeur pour stocker la liste des joueurs
int i;  // Variable d'index utilisée pour les boucles

/*
malloc(); //allocation de la mémoire à utiliser forcement avec un Free pour liberer la mémoire
calloc(); // remet à la gestion de la memoire
realloc(); //reallocation de la mémoire à utiliser forcement avec un Free pour liberer la mémoire
*/


int main(void) {
    int nombreJoueurs = 2;  // Initialisation du nombre de joueurs
    int *liste_joueurs = NULL;  // Pointeur pour la liste des joueurs
    int i;  // Variable d'index utilisée dans les boucles

    // Allocation de mémoire pour le nombre initial de joueurs
    liste_joueurs = malloc(nombreJoueurs * sizeof(int));

    // Vérification de l'allocation mémoire
    if (liste_joueurs == NULL) {
        exit(1);  // Sortie du programme en cas d'échec de l'allocation
    }

    // Remplir la liste des joueurs avec des valeurs
    for (i = 0; i < nombreJoueurs; i++) {
        printf("Joueur %d --> numero %d\n", i + 1, i * 3);
        liste_joueurs[i] = i * 3;  // Affectation des valeurs calculées
    }

    // Afficher la liste des joueurs
    for (i = 0; i < nombreJoueurs; i++) {
        printf("%d ", liste_joueurs[i]);  // Affichage des numéros des joueurs
    }

    printf("\n");

    // Changement du nombre de joueurs (modification dynamique de la taille)
    nombreJoueurs = 5;

    // Redimensionnement de la mémoire allouée avec realloc
    liste_joueurs = realloc(liste_joueurs, nombreJoueurs * sizeof(int));

    // Vérification de l'allocation mémoire après le redimensionnement
    if (liste_joueurs == NULL) {
        exit(1);  // Sortie en cas d'échec de realloc
    }

    // Libérer la mémoire allouée dynamiquement
    free(liste_joueurs);

    return 0;  // Indiquer que le programme s'est terminé correctement
}
