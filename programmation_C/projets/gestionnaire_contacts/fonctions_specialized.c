#include <stdio.h>
#include <ctype.h>  // Pour la fonction tolower()
#include <string.h>
#include  "proto.h"


//***************GESTIONNNAIRE CONTACT************** */
// Fonction pour le contrôle de la saisie d'une chaine de caracteres
char* saisir_contact(char* tab, size_t taille_chaine) {
    // char chaine[20];
    while (1) {
        printf("Veuillez entrer le nom et prenom du contact (%zu caracteres max ): \n", taille_chaine-1);

        // Vérifier la saisie et les conditions
           if (scanf(" %19[^\n]", tab) == 1 && strlen(tab) >  2 && strlen(tab) <  taille_chaine) {
            while (getchar() != '\n'); //vide le buffer
            return tab;  //  renvoyer la chaine sasie
        } else {
            printf("Saisie incorrecte. Veuillez entrer une chaine  de %zu characteres max et 2 mini .\n", taille_chaine);
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }

}
// Fonction pour le contrôle de la saisie d'un numero de tel
char* saisir_numero_tel(char* tel, size_t taille_chaine) {
    // char chaine[20];
    while (1) {
        printf("Veuillez entrer le numero de telephone du contact sans les espaces (%zu caracteres max) : \n", taille_chaine);

        // Vérifier la saisie et les conditions
           if (scanf("%10s", tel) == 1  && strlen(tel) == taille_chaine-1) {
            while (getchar() != '\n'); //vide le buffer
            return tel;  //  renvoyer la chaine sasie
        } else {
            printf("Saisie incorrecte. Veuillez entrer un numero de %zu characteres .\n", taille_chaine-1);
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }

}

// fonction pour afficher la liste des contacs
void affichage_liste_contact(char tab[][TAILLE_NOM], size_t taille_tableau) {
    printf("Liste des contacts :\n");
    for (size_t i = 0; i < taille_tableau; i++) {
        printf("Contact %zu : %s\n", i + 1, tab[i]);
    }
}
// fonction pour afficher  la liste des numeros de telephones
void affichage_liste_telephone(char tab[][TAILLE_TEL], size_t taille_tableau) {
    printf("Liste des telephones :\n");
    for (size_t i = 0; i < taille_tableau; i++) {
        printf("Telephone :%zu : %s\n", i + 1, tab[i]);
    }
}


// Fonction pour supprimer un contact dans un tableau de contacts et telephoone associé
void suppression_contact(char contact[][TAILLE_NOM], char tel[][TAILLE_TEL],size_t taille_tableau, int numero_contact) {
    if (numero_contact < 1 || numero_contact > taille_tableau) {
        printf("Numéro de contact invalide.\n");
        return;
    }

    printf("Suppression du contact numéro %d :\n", numero_contact);

    // Décaler les contacts après le contact à supprimer
    for (size_t i = numero_contact - 1; i < taille_tableau - 1; i++) {
        strcpy(contact[i], contact[i + 1]);
        strcpy(tel[i], tel[i + 1]);
    }

    // Mettre la dernière position à vide (car le contact a été décalé)
    contact[taille_tableau - 1][0] = '\0';  // Remplace la dernière chaîne par une chaîne vide
    tel[taille_tableau - 1][0] = '\0';  // Remplace la dernière chaîne par une chaîne vide
}

// afficher menu
void afficher_menu(void)
{
    printf("\n\n=================================\n");
    printf("    MENU     \n");
    printf("1- Ajouter un contact\n");
    printf("2- Supprimer un contact\n");
    printf("3- Rechercher un contact\n");
    printf("4- Afficher tous les contacts\n");
    printf("5- Quitter le menu\n");
    printf("=====================================\n\n");
}

// Fonction pour rechercher un contact par nom
int rechercher_contact(char contacts[][20], size_t taille_tableau, const char* nom)
{
    for (size_t i = 0; i < taille_tableau; i++) {
        if (strcmp(contacts[i], nom) == 0) {
            return i;  // Contact trouvé, retourner l'index
        }
    }
    return -1;  // Contact non trouvé
}

//***************FIN  GESTIONNNAIRE CONTACT************** */