#ifndef HEADER_H  // Si la macro HEADER_H n'est pas encore définie
#define HEADER_H  // Définition de la macro

#define TAILLE_NOM 20 //taille d'un contact
#define TAILLE_TEL 11 //taille d'un num de tel
#define NBRE_CONTACT 5 //nombre de contact possibles


#include <stddef.h>  // Pour la taille (size_t)

// Déclaration de la structure Contact
typedef struct {
    char nom[TAILLE_NOM];
    char telephone[TAILLE_TEL];
} Contact;


// Prototypes des fonctions

//*********fonctions specifiques à la gestion des contacts***************

void saisir_repertoire(Contact *c); // avec struct

// void affichage_repertoire(Contact contacts[], size_t taille_tableau);// avec struct

void suppression_repertoire(Contact contacts[], size_t taille_tableau, int numero_contact); // avec struct

void rechercher_repertoire(Contact contacts[], size_t taille_tableau, const char* nom) ;// avec struct

void afficher_menu(void);

void enregistrement_repertoire_fichier(Contact c);
void lire_repertoire_fichier();

#endif  // Fin de la protection contre l'inclusion multiple

