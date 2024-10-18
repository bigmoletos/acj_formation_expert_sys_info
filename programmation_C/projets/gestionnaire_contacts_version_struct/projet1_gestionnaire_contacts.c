#include <stdio.h>
#include <stdlib.h>
#include "proto.h"



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
int nombre_contacts = 0;




int main()
{

// Déclaration et intialisation des variables locales avec des valeurs
    // char contacts[NBRE_CONTACT][TAILLE_NOM];
    // char telephones[NBRE_CONTACT][TAILLE_TEL] ;

    // Déclaration d'un tableau de structures Contact
    Contact contacts[NBRE_CONTACT];

    int choix_menu = 0;
    int choix_numero_contact = 0; //pour les suppressions
    size_t taille_chaine = 20;
    size_t taille_chaine2 = 10;



    // Affiche le titre du programme
    printf("\n\n=================================\n");
    printf("    Projet Tableaux - String     \n");
    printf("----Gestionnaire de contact------\n");
    printf("=====================================\n\n");

    do
    {
        afficher_menu();
        choix_menu = saisir_entier(6);
        printf("choix_menu: %d\n", choix_menu);

        switch (choix_menu)
        {
            case 1: //ajouter contact et telephone

                printf("Combien de contacts souhaitez-vous ajouter (%d maximum)\n", NBRE_CONTACT);
                // scanf("%d", &nombre_contacts);
                    if (scanf("%d", &nombre_contacts) ==1 && nombre_contacts <= NBRE_CONTACT )
                    {
                        for (size_t i = 0; i < nombre_contacts; i++)
                        {
                            saisir_repertoire(&contacts[i]);
                            // saisir_numero_tel(&contacts[i].telephone, TAILLE_TEL);
                            while (getchar() != '\n');// vide le buffer
                        }
                    } else
                    {
                            printf("Saisie incorrecte. Veuillez entrer un nombre entre 1 et %d qui est la taille maximale de votre repertoire\n", NBRE_CONTACT);
                            while (getchar() != '\n'); // Vider le buffer en cas de mauvaise saisie
                    }

                break;

            case 2: //supprimer contact
                choix_numero_contact = saisir_entier(NBRE_CONTACT);
                suppression_repertoire( contacts, TAILLE_NOM,  choix_numero_contact);

                break;
            case 3: //rechercher contact
                printf("Entrez le nom du contact à rechercher : ");
                char nom[TAILLE_NOM];

                // Utilisation de scanf avec une limite de taille pour éviter les dépassements de mémoire
                scanf("%19s", nom);  // %19s limite l'entrée à 19 caractères (1 caractère pour le '\0')

                int index = rechercher_repertoire(contacts, nombre_contacts, nom);
                if (index != -1) {
                    printf("Contact trouvé : %s, Téléphone : %s\n", contacts[index].nom, contacts[index].telephone);
                } else {
                    printf("Contact non trouvé.\n");
                }

                break;

            case 4: // afficher tous les contacts
                // affichage_liste_contact( contacts, nombre_contacts);
                // affichage_liste_telephone( telephones, nombre_contacts);
                affichage_repertoire(contacts, nombre_contacts);

                break;

            case 5: // quitter le menus
                quitter = demander_quitter();
                break;

            default:
                printf("Choix non valide. Veuillez réessayer.\n");
                break;
    }
        // if (quitter == 'n') {
        //     quitter = demander_quitter();
        // printf("quitter: %c\n", quitter);
        // }

    } while (quitter == 'n');
        // printf("quitter: %c\n", quitter);
        return 0;
}
