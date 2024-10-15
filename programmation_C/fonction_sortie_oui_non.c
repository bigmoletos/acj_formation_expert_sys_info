#include <stdio.h>
#include <ctype.h>  // Pour la fonction tolower()

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
