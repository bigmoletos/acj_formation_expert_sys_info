#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// #include <sys/resource.h>
#include <stdbool.h>
#include "prototypes.h"  //intégration du header contenant les fonctions de contrôle de saisie et sortie prog

/* Enoncé
1- Créer une fonction qui permet d’inverser le contenu de deux entiers passés
en paramètre.
2- Afficher les entiers dans la fonction main, avant et après utilisation de la
fonction du point 1.
Objectifs :
var1 = 12 et var2 = 9
Inversion ...
var1 = 9 et var2 = 12
*/

// Fonction d'inversion de 2 valeurs avec pointeurs
void inverser_valeurs_avec_pointeur(int *val1, int *val2) {
    int temp = *val1; // variable tampon
    *val1 = *val2;
    *val2 = temp;
}

// Fonction d'inversion de 2 valeurs sans pointeur
// En renvoyant les deux valeurs à travers deux appels
int inverser_valeur1_sans_pointeur(int val1, int val2) {
    return val2;
}

int inverser_valeur2_sans_pointeur(int val1, int val2) {
    return val1;
}

int main() {
        // Capturer le temps de début
    clock_t start = clock();
    #ifdef __linux__  // Cette partie ne fonctionne que sous Linux/Unix
        struct rusage usage; // pour la mesure de la cahrge
    #endif
    char quitter = 'n';  // Initialisation pour que le programme commence

    do {
        // Affiche le titre du programme
        printf("\n\n=====================================\n");
        printf("tp10 - les fonctions\n");
        printf("Inversion de 2 valeurs\n");
        printf("=====================================\n\n");

        // Déclaration et initialisation de nos variables
        int valeur1 = 0, valeur2 = 0;
        int valeur10 = 0, valeur20 = 0;

        // Saisie des valeurs avec contrôle, appel à la fonction importée
        valeur1 = saisir_entier(100);
        valeur2 = saisir_entier(100);

        // Affichage des valeurs avant inversion
        printf("*************************************************\n");
        // printf("Avant inversion : valeur1 = %d, valeur2 = %d\n", valeur1, valeur2);

        // appel fonction vaffichage
        affichage2valeur(&valeur1, &valeur2);

        // Utilisation de la fonction d'inversion des valeurs avec pointeur
        printf("-------------------------------------------------------------------------------\n");
        inverser_valeurs_avec_pointeur(&valeur1, &valeur2);
        printf("-------------------------------------------------------------------------------\n");

        // Utilisation de la fonction d'inversion des valeurs sans pointeur
        valeur10 = inverser_valeur1_sans_pointeur(valeur1, valeur2);
        valeur20 = inverser_valeur2_sans_pointeur(valeur1, valeur2);

        // Affichage des valeurs après l'inversion
        printf("-------------------------------------------------------------------------------\n");
        printf("Avec pointeur\nAprès inversion : valeur1 = %d, valeur2 = %d\n", valeur1, valeur2);
        printf("Sans pointeur\nAprès inversion : valeur1 = %d, valeur2 = %d\n", valeur10, valeur20);
        printf("---------------------------------------------------------------------------------\n");

        // appel fonction vaffichage
        printf("-------------------------------------------------------------------------------\n");
        affichage2valeur(&valeur1, &valeur2);
        printf("-------------------------------------------------------------------------------\n");
        // Gestion de la sortie (Oui/Non) avec appel à la fonction importée
        if (demander_quitter() == 'o') {
            printf("-----------------------------------------------------\n");
            printf("Vous avez choisi de quitter le programme. Au revoir !\n\n");
            quitter = 'o';
        } else {
            printf("Vous avez choisi de continuer.\n");
        }
    } while (quitter == 'n');


    // Capturer le temps de fin
    clock_t end = clock();

    // Calculer le temps d'exécution en millisecondes
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Le programme a pris %f ms pour s'exécuter\n", time_taken);

// la mesure de la charge ram et proc ne fonctionne que sous linux
#ifdef __linux__  // Cette partie ne fonctionne que sous Linux/Unix
        // Récupérer les statistiques d'utilisation des ressources
    getrusage(RUSAGE_SELF, &usage);
    // Récupérer les statistiques d'utilisation des ressources
    getrusage(RUSAGE_SELF, &usage);

    // Afficher l'utilisation de la CPU en microsecondes (user et system time)
    printf("Temps CPU utilisé (user) : %ld.%06ld secondes\n",
           usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("Temps CPU utilisé (system) : %ld.%06ld secondes\n",
           usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
#endif

    return 0;
}
