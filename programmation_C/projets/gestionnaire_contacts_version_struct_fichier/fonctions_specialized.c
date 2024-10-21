#include <stdio.h>
#include <ctype.h>  // Pour la fonction tolower()
#include <string.h>
#include  "proto.h"


//***************GESTIONNNAIRE CONTACT************** */

// Fonction pour la saisie d'un contact avec struct
void saisir_repertoire(Contact *c) {
    printf("Veuillez entrer le nom du contact: ");
    scanf("%19[^\n]", c->nom);  // Limite à 19 caractères + '\0'

    printf("Veuillez entrer le numéro de téléphone (10 chiffres max) : ");
    scanf("%10s", c->telephone);  // Limite à 10 chiffres

        // Appel de la fonction pour enregistrer dans le fichier
    enregistrer_repertoire_fichier(c,1);
}

// enregistre le repertoire dans un fichier repertoire.json
void enregistrement_repertoire_fichier(Contact c,size_t taille){
   FILE *fp = fopen("repertoire.json", "a"); // Ouvre le fichier en mode ajout
    if (fp == NULL) {
        perror("Erreur d'ouverture de fichier");
        return;
    }

    // Si le fichier est vide, écrire l'ouverture du tableau JSON
    if (ftell(fp) == 0) {
        fprintf(fp, "[\n");
    } else {
        fprintf(fp, ",\n"); // Ajouter une virgule pour séparer les objets
    }

    // Écriture du contact au format JSON
    fprintf(fp, "  {\n");
    fprintf(fp, "    \"nom\": \"%s\",\n", c.nom);
    fprintf(fp, "    \"telephone\": \"%s\"\n", c.telephone);
    fprintf(fp, "  }");

    fclose(fp); // Ferme le fichier

}


// fonction pour afficher la liste des contacs
//fonctions avec la struct

// Fonction pour lire les contacts à partir du fichier JSON
void lire_repertoire_fichier() {
    FILE *fp = fopen("repertoire.json", "r");
    if (fp == NULL) {
        perror("Erreur d'ouverture de fichier");
        return;
    }

    char ligne[100];
    while (fgets(ligne, sizeof(ligne), fp)) {
        printf("%s", ligne);
    }
    fclose(fp);
}
// Fonction pour supprimer un contact tel et nom en  même temps avec struct dans un  fichier
void suppression_repertoire(Contact contacts[], size_t taille_tableau, int numero_contact) {
    if (numero_contact < 1 || numero_contact > taille_tableau) {
        printf("Numéro de contact invalide.\n");
        return;
    }

    printf("Suppression du contact numéro %d :\n", numero_contact);

    // Décale les contacts pour supprimer l'entrée
    for (size_t i = numero_contact - 1; i < taille_tableau - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    // Appel de la fonction pour mettre à jour le fichier JSON après suppression
    supprimer_entree_fichier(contacts, taille_tableau - 1);
}

void supprimer_entree_fichier(Contact contacts[], size_t taille_tableau) {
    FILE *fp = fopen("repertoire.json", "w");
    if (fp == NULL) {
        perror("Erreur d'ouverture de fichier");
        return;
    }

    fprintf(fp, "[\n");

    // Réécriture des contacts mis à jour dans le fichier JSON
    for (size_t i = 0; i < taille_tableau; i++) {
        fprintf(fp, "  {\n");
        fprintf(fp, "    \"nom\": \"%s\",\n", contacts[i].nom);
        fprintf(fp, "    \"telephone\": \"%s\"\n", contacts[i].telephone);
        fprintf(fp, "  }");
        if (i < taille_tableau - 1) {
            fprintf(fp, ",\n"); // Ajouter une virgule entre les objets sauf le dernier
        } else {
            fprintf(fp, "\n"); // Dernière ligne sans virgule
        }
    }

    fprintf(fp, "]\n");
    fclose(fp);
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

//***************FIN  GESTIONNNAIRE CONTACT************** */