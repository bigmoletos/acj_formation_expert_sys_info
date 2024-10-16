// fonction_controle_saisi_entier.c
#include <stdio.h>
#include <ctype.h>
// #include  "fonction_controle_saisi_entier.h"

// int saisir_entier(int max_valeur);
// char demander_quitter();

// Fonction pour le contrôle de la saisie d'un entier avec une limite
int saisir_entier(int ma_valeur) {
    int valeur;
    while (1) {
        printf("Veuillez entrer un entier positif inférieur à %d : ", ma_valeur);

        // Vérifier la saisie et les conditions
        if (scanf("%d", &valeur) == 1 && valeur > 0 && valeur < ma_valeur) {
            return valeur;  // Saisie correcte, renvoyer la valeur
        } else {
            printf("Saisie incorrecte. Veuillez entrer un entier positif inférieur à %d.\n", ma_valeur);
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }
}

