#include <stdio.h>
#include <ctype.h>  // Pour les caractères
#include <string.h>  // Pour utiliser strlen() et strstr()


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

// Fonction pour compter certains caractéres (find_type) dans une chaîne
int compter_char_type(const char tableau[],char find_type) {
    int compteur = 0;
    int i = 0;
    while (tableau[i] != '\0') {
        if (tableau[i] ==find_type) {
            compteur++;
        }
        i++;
    }
    return compteur;
}

// // Fonction pour compter une chaine de caractéres (find_chaine) dans une chaîne
// int compter_chaine_char(const char tableau[],char find_chaine []) {
//     int compteur = 0;
//     int i = 0;
//     while (tableau[i] != '\0') {
//         if (tableau[i] ==find_chaine) {
//             compteur++;
//         }
//         i++;
//     }
//     return compteur;
// }


// Fonction pour compter une sous-chaîne (find_chaine) dans une chaîne principale (tableau)
int compter_chaine_char(const char tableau[], const char find_chaine[]) {
    int compteur = 0;
    int i = 0;
    int longueur_chaine = strlen(find_chaine); // Longueur de la chaîne à rechercher

    while (tableau[i] != '\0') {
        // Utiliser strncmp pour comparer les sous-chaînes de longueur_chaine
        if (strncmp(&tableau[i], find_chaine, longueur_chaine) == 0) {
            compteur++;
            i += longueur_chaine - 1;  // Avancer dans la chaîne pour éviter les comptages redondants
        }
        i++;
    }

    return compteur;
}



int main() {
    char chaine[] = "Exemple de chaîne avec des caractères spéciaux!";
    char caractere_a_chercher = 'e';
    char sous_chaine[] = "chaîne";

    int nombre_de_caracteres = compter_char_type(chaine, caractere_a_chercher);

    printf("Le caractère '%c' apparaît %d fois dans la chaîne.\n", caractere_a_chercher, nombre_de_caracteres);


    int nombre_de_sous_chaines = compter_chaine_char(chaine, sous_chaine);

    printf("La sous-chaîne '%s' apparaît %d fois dans la chaîne.\n", sous_chaine, nombre_de_sous_chaines);


    return 0;
}