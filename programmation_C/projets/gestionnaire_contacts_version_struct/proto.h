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

//*********Fonctions générales***************
// Fonction pour demander si l'utilisateur veut continuer ou quitter
char demander_quitter(void);

// Fonction pour le contrôle de la saisie d'un entier avec une limite
int saisir_entier(int ma_valeur);

// Fonction pour le contrôle de la saisie d'un seul caractère
int saisir_char(void);


// Fonctions liées aux tableaux
void affichage_tableau(int *tab, size_t taille_tableau);
void copie_tableau(int *tab1, int *tab2, size_t taille_tableau);
void double_valeur_tableau(int *tab, size_t taille_tableau);

// Fonctions de conversion de chaîne
void convertir_en_majuscules(char tableau[]);
void convertir_en_minuscules(char tableau[]);

// Fonctions pour compter les majuscules et minuscules dans une chaîne
int compter_majuscule(const char tableau[]);
int compter_minuscule(const char tableau[]);

//*********fonctions specifiques à la gestion des contacts***************

// // Fonction pour le contrôle de la saisie et de l'affichage des contact et numero de tel
// char* saisir_contact(char* tab, size_t taille_chaine);
// void affichage_liste_contact(char tab[][TAILLE_NOM], size_t taille_tableau);

// char* saisir_numero_tel(char* tab, size_t taille_chaine);
// void affichage_liste_telephone(char tab[][TAILLE_TEL], size_t taille_tableau);

// void suppression_contact(char contact[][TAILLE_NOM], char tel[][TAILLE_TEL], size_t taille_tableau, int numero_contact);
// int rechercher_contact(char contacts[][TAILLE_NOM], size_t taille_tableau, const char *nom);

//***** */ version avec structure *******
// Fonction pour le contrôle de la saisie et de l'affichage des contact et numero de tel

char* saisir_contact(Contact *c, size_t taille_chaine);// avec struct

char* saisir_numero_tel(Contact *c, size_t taille_chaine);// avec struct

void affichage_repertoire(Contact contacts[], size_t taille_tableau);// avec struct

void suppression_repertoire(Contact contacts[], size_t taille_tableau, int numero_contact); // avec struct

int rechercher_repertoire(Contact contacts[], size_t taille_tableau, const char *nom);// avec struct
void afficher_menu(void);
#endif  // Fin de la protection contre l'inclusion multiple

