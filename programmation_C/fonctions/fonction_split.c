#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction split qui découpe une chaîne selon un délimiteur
//char** est un pointeur vers un pointeur de caracteres  donc un tableau de chaine de caracteres
char** split(const char* str, const char* delim, int* num_tokens) {
    char* str_copy = strdup(str);  // Crée une copie de la chaîne pour la manipuler
    char* token;
    int tokens_alloc = 10;  // Taille initiale pour le tableau de sous-chaînes
    int tokens_used = 0;    // Nombre de sous-chaînes trouvées

    // Alloue de la mémoire pour le tableau de sous-chaînes
    char** tokens = malloc(tokens_alloc * sizeof(char*));
    if (tokens == NULL) {
        printf("Échec de l'allocation de mémoire\n");
        exit(1);
    }

    // Découpe la chaîne en utilisant le délimiteur
    token = strtok(str_copy, delim);
    while (token != NULL) {
        if (tokens_used == tokens_alloc) {
            tokens_alloc *= 2;
            tokens = realloc(tokens, tokens_alloc * sizeof(char*));
            if (tokens == NULL) {
                printf("Échec de l'allocation de mémoire lors du realloc\n");
                exit(1);
            }
        }

        // Alloue de la mémoire pour chaque sous-chaîne
        tokens[tokens_used] = strdup(token);
        tokens_used++;

        // Continue avec le prochain token
        token = strtok(NULL, delim);
    }

    // Marque la fin du tableau avec NULL
    tokens[tokens_used] = NULL;

    // Met à jour le nombre de tokens trouvés
    *num_tokens = tokens_used;

    // Libère la mémoire allouée pour la copie de la chaîne
    free(str_copy);

    return tokens;
}

// Fonction pour libérer la mémoire du tableau de sous-chaînes
void free_tokens(char** tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

int main() {
    const char* str = "Hello,World,This,Is,A,Test";
    const char* delim = ",";
    int num_tokens;

    // Appel à la fonction split
    char** tokens = split(str, delim, &num_tokens);

    // Affichage des sous-chaînes
    for (int i = 0; i < num_tokens; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
    }

    // Libération de la mémoire
    free_tokens(tokens);

    return 0;
}
