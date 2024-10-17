#include <stdio.h>
#include <stdlib.h>
#include "proto.h"
#define TAILLE_NOM 20
#define TAILLE_TEL 10


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
int saisir_chaine(size_t taille_chaine);

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
int taille = 0;
char quitter = 'n';


int main()
{

// Déclaration et intialisation des variables avec des valeurs
    char contacts[TAILLE_NOM] ;
    char telephones[TAILLE_TEL] ;
    size_t taille_chaine = 0;
    size_t taille_chaine2 = 0;

    // Affiche le titre du programme
    printf("\n\n================================\n");
    printf("Projet Tableaux - String\n");
    printf("----Gestionnaire de contact------\n");
    printf("================================\n\n");

//affichage tableau contact
    affichage_liste_contact( contacts, taille_chaine);
    // affichage tableau telephones

    // saisie du contact------
    // saisir_chaine( TAILLE_NOM);

    // quitter=demander_quitter();

    return 0;

}
