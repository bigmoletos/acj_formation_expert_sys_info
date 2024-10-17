#include <stdio.h>
#include <stdlib.h>
#include "proto.h"
#define TAILLE_NOM 20 //taille d'un contact
#define TAILLE_TEL 10 //taille d'un num de tel
#define NBRE_CONTACT 5 //nombre de contact possibles


/*mini_projet1
enoncé :

nous allons utiliser deux tableaux :
un tableau pour stocker les noms et un autre pour les numéros de téléphone.
PAS DE "STRUCT"
utilisation de fonctions obligatoire , donc utilisation modulaire
Un projet github obligatoire

Ce projet est un gestionnaire de contacts simple. L'objectif est de créer un programme en C qui permet de gérer une liste de contacts avec les fonctionnalités suivantes :

 - Ajouter un contact (nom, numéro de téléphone). (verification des doublons)
 - Rechercher un contact par nom.
 - Afficher tous les contacts.
 - Supprimer un contact.

interface
--- Gestionnaire de Contacts ---
1. Ajouter un contact
2. Rechercher un contact
3. Afficher tous les contacts
4. Supprimer un contact
5. Quitter

Choisissez une option: 5
Quitter le programme.

*/


/* SPOIL
controle des doublons
utiliser 2 tableaux 1 pour les noms et un pour les telephones
utiliser des fonctionss avec proto
ne pas utiliser struct
*/

/* Liste des fonctions dispo
// Prototypes des fonctions

// Fonction pour demander si l'utilisateur veut continuer ou quitter
char demander_quitter(void);

// Fonction pour le contrôle de la saisie d'un entier avec une limite
int saisir_entier(int ma_valeur);

// Fonction pour le contrôle de la saisie d'un seul caractère
int saisir_char(void);

// Fonction pour le contrôle de la saisie d'une chaîne de caractères
char* saisir_contact(char* tab, size_t taille_chaine);

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
*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées
int i = 0;
// int taille = 0;
char quitter = 'n';


int main()
{

// Déclaration et intialisation des variables locales avec des valeurs
    char contacts[NBRE_CONTACT][TAILLE_NOM];
    char telephones[NBRE_CONTACT][TAILLE_TEL] ;
    // char* telephones[NBRE_CONTACT] ;
    // char* contacts[NBRE_CONTACT] ;
    size_t taille_chaine = 20;
    size_t taille_chaine2 = 10;

    // Affiche le titre du programme
    printf("\n\n================================\n");
    printf("Projet Tableaux - String\n");
    printf("----Gestionnaire de contact------\n");
    printf("================================\n\n");

//affichage tableau contact
    // printf("%d\n", TAILLE_NOM);

    for (size_t i = 0; i < NBRE_CONTACT; i++)
    {
        saisir_contact(contacts[i], TAILLE_NOM);
        saisir_numero_tel(telephones[i], TAILLE_TEL);
}

    affichage_liste_contact( contacts, NBRE_CONTACT);
    affichage_liste_telephone( telephones, NBRE_CONTACT);
    // affichage tableau telephones

    // saisie du contact------
    // saisir_chaine( TAILLE_NOM);

    // quitter=demander_quitter();

    return 0;

}
