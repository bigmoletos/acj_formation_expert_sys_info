#include <stdio.h>
#include <ctype.h>  // Pour les caractères

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

int main() {
    char chaine[] = "Bonjour Le Monde!";

    printf("Chaîne originale: %s\n", chaine);

    // Convertir en majuscules
    convertir_en_majuscules(chaine);
    printf("Chaîne en majuscules: %s\n", chaine);

    // Convertir en minuscules
    convertir_en_minuscules(chaine);
    printf("Chaîne en minuscules: %s\n", chaine);

    // Compter le nombre de majuscules et minuscules
    int nb_majuscules = compter_majuscule(chaine);
    int nb_minuscules = compter_minuscule(chaine);

    printf("Nombre de majuscules: %d\n", nb_majuscules);
    printf("Nombre de minuscules: %d\n", nb_minuscules);

    return 0;
}
