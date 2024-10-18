#include <stdio.h>
#include <ctype.h>  // Pour la fonction tolower()
#include <string.h>
#include  "proto.h"

// Fonction pour demander si l'utilisateur veut continuer ou quitter
char demander_quitter() {
    char reponse;
    while (1) {
        printf("Souhaitez-vous quitter le programme ? (O/N) : ");

        if (scanf(" %c", &reponse) == 1) {
            reponse = tolower(reponse);  // Convertir en minuscule pour accepter 'O' ou 'N'

            if (reponse == 'o' || reponse == 'n') {
                return reponse;  // Réponse correcte, renvoyer 'o' ou 'n'
            }
        }

        // Si on arrive ici, la saisie est incorrecte
        printf("Saisie incorrecte. Veuillez entrer 'O' pour Oui ou 'N' pour Non.\n");
        // Vider le buffer en cas de mauvaise saisie
        while (getchar() != '\n');
    }
}

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
            printf("Saisie incorrecte. Veuillez entrer un seul charactere .\n");
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }
    return 0;
}


void affichage_tableau(int *tab, size_t taille_tableau){

    printf("Tableau: ");
    for (size_t i = 0; i < taille_tableau; i++)
    {
        printf("%d", *(tab +i));
        if (i < taille_tableau - 1) {
            printf(", ");
        }

    }
    printf("\n\n");
}

void copie_tableau(int *tab1, int *tab2,size_t taille_tableau){

    for (size_t i = 0; i < taille_tableau; i++)
    {
        *(tab2 + i) =*(tab1 + i);
    }
}

void double_valeur_tableau(int *tab, size_t taille_tableau){

    for (size_t i = 0; i < taille_tableau; i++)
    {
        *(tab + i) *=2;
    }
}

// Fonction pour convertir une chaîne en majuscules
void convertir_en_majuscules(char tableau[]) {
    int i = 0;
    while (tableau[i] != '\0') {
        tableau[i] = toupper(tableau[i]);
        i++;
    }
}

// Fonction pour convertir une chaîne en minuscules
void convertir_en_minuscules(char tableau[]) {
    int i = 0;
    while (tableau[i] != '\0') {
        tableau[i] = tolower(tableau[i]);
        i++;
    }
}

// Fonction pour compter le nombre de majuscules dans une chaîne
int compter_majuscule(const char tableau[]) {
    int compteur = 0;
    int i = 0;
    while (tableau[i] != '\0') {
        if (isupper(tableau[i])) {
            compteur++;
        }
        i++;
    }
    return compteur;
}

// Fonction pour compter le nombre de minuscules dans une chaîne
int compter_minuscule(const char tableau[]) {
    int compteur = 0;
    int i = 0;
    while (tableau[i] != '\0') {
        if (islower(tableau[i])) {
            compteur++;
        }
        i++;
    }
    return compteur;
}
