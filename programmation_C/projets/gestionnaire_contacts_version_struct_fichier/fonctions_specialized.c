#include <stdio.h>
#include <ctype.h>  // Pour la fonction tolower()
#include <string.h>
#include  "proto.h"


//***************GESTIONNNAIRE CONTACT************** */

// Fonction pour la saisie d'un contact avec struct
void saisir_repertoire(Contact *c) {
    printf("Veuillez entrer le nom du contact: ");
    scanf("%19s", c->nom);  // Limite à 19 caractères + '\0'

    printf("Veuillez entrer le numéro de téléphone (10 chiffres max) : ");
    scanf("%10s", c->telephone);  // Limite à 10 chiffres
}

// fonction pour afficher la liste des contacs
//fonctions avec la struct
void affichage_repertoire(Contact contacts[], size_t taille_tableau) {
    printf("Liste des contacts :\n");
    for (size_t i = 0; i < taille_tableau; i++) {
         printf("Contact %zu : %s, Téléphone : %s\n", i + 1, contacts[i].nom, contacts[i].telephone);
    }
}

// Fonction pour supprimer un contact tel et nom en  même temps avec struct
void suppression_repertoire(Contact contacts[], size_t taille_tableau, int numero_contact) {
    if (numero_contact < 1 || numero_contact > taille_tableau) {
        printf("Numéro de contact invalide.\n");
        return;
    }

    printf("Suppression du contact numéro %d :\n", numero_contact);
    for (size_t i = numero_contact - 1; i < taille_tableau - 1; i++) {
        contacts[i] = contacts[i + 1];  // Décale les contacts
    }
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


int rechercher_repertoire(Contact contacts[], size_t taille_tableau, const char* nom) {
    for (size_t i = 0; i < taille_tableau; i++) {
        if (strcmp(contacts[i].nom, nom) == 0) {
            return (int)i;  // Contact trouvé, retourner l'index (cast en int pour éviter les warnings)
        }
    }
    return -1;  // Contact non trouvé
}

void enregistrement_repertoire_fichier(Contact contact[]){



}
//***************FIN  GESTIONNNAIRE CONTACT************** */