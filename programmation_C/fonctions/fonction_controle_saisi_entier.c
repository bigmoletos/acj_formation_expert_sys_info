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

// Fonction pour le contrôle de la saisie d'un caractere
int saisir_char() {
    char lettre;
    while (1) {
        printf("Veuillez entrer un seul caractére : ");

        // Vérifier la saisie et les conditions
        if (scanf(" %c", &lettre) == 1 && isalpha(lettre) ) {
            return lettre;  //  renvoyer la lettre sasie
        } else {
            printf("Saisie incorrecte. Veuillez entrer un seul charactere %s.\n", );
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }
    return 0;
}


// Fonction pour le contrôle de la saisie d'une chaine de caracteres
int saisir_chaine(size_t taille_chaine) {
    char chaine;
    while (1) {
        printf("Veuillez entrer une chaine de %zu caracteres max : ", taille_chaine);

        // Vérifier la saisie et les conditions
           if (scanf(" %[^\n]", chaine) == 1 && strlen(chaine) <=  taille_chaine) {
            return chaine;  //  renvoyer la lettre sasie
        } else {
            printf("Saisie incorrecte. Veuillez entrer une chaine  de %zu characteres max .\n", taille_chaine);
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }
    return 0;
}