#include <stdio.h>
#include <ctype.h>  // Pour la fonction tolower()
#include <string.h>
#include  "proto.h"

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

// Fonction pour le contrôle de la saisie d'un entier avec une limite
int saisir_entier(int ma_valeur) {
    int valeur;
    while (1) {
        printf("Veuillez entrer un entier positif inférieur à %d : ", ma_valeur);

        // Vérifier la saisie et les conditions
        if (scanf("%d", &valeur) == 1 && valeur > 0 && valeur < ma_valeur) {
            return valeur;  // Saisie correcte, renvoyer la valeur
        } else {
            printf("Saisie incorrecte. Veuillez entrer un entier positif inférieur à %d.\n", ma_valeur);
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }
}


// Fonction pour le contrôle de la saisie d'un caractere
int saisir_char() {
    char lettre;
    while (1) {
        printf("Veuillez entrer un seul caractére : ");

        // Vérifier la saisie et les conditions
        if (scanf(" %c", &lettre) == 1 && isalpha(lettre) ) {
            return lettre;  //  renvoyer la lettre sasie
        } else {
            printf("Saisie incorrecte. Veuillez entrer un seul charactere .\n");
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }
    return 0;
}


void affichage_tableau(int *tab, size_t taille_tableau){

    printf("Tableau: ");
    for (size_t i = 0; i < taille_tableau; i++)
    {
        printf("%d", *(tab +i));
        if (i < taille_tableau - 1) {
            printf(", ");
        }

    }
    printf("\n\n");
}



void copie_tableau(int *tab1, int *tab2,size_t taille_tableau){

    for (size_t i = 0; i < taille_tableau; i++)
    {
        *(tab2 + i) =*(tab1 + i);
    }
}

void double_valeur_tableau(int *tab, size_t taille_tableau){

    for (size_t i = 0; i < taille_tableau; i++)
    {
        *(tab + i) *=2;
    }
}


// Fonction pour convertir une chaîne en majuscules
void convertir_en_majuscules(char tableau[]) {
    int i = 0;
    while (tableau[i] != '\0') {
        tableau[i] = toupper(tableau[i]);
        i++;
    }
}

// Fonction pour convertir une chaîne en minuscules
void convertir_en_minuscules(char tableau[]) {
    int i = 0;
    while (tableau[i] != '\0') {
        tableau[i] = tolower(tableau[i]);
        i++;
    }
}

// Fonction pour compter le nombre de majuscules dans une chaîne
int compter_majuscule(const char tableau[]) {
    int compteur = 0;
    int i = 0;
    while (tableau[i] != '\0') {
        if (isupper(tableau[i])) {
            compteur++;
        }
        i++;
    }
    return compteur;
}

// Fonction pour compter le nombre de minuscules dans une chaîne
int compter_minuscule(const char tableau[]) {
    int compteur = 0;
    int i = 0;
    while (tableau[i] != '\0') {
        if (islower(tableau[i])) {
            compteur++;
        }
        i++;
    }
    return compteur;
}

//***************GESTIONNNAIRE CONTACT************** */
// Fonction pour le contrôle de la saisie d'une chaine de caracteres
char* saisir_contact(char* tab, size_t taille_chaine) {
    // char chaine[20];
    while (1) {
        printf("Veuillez entrer le nom et prenom du contact (%zu caracteres max ): \n", taille_chaine-1);

        // Vérifier la saisie et les conditions
           if (scanf(" %19[^\n]", tab) == 1 && strlen(tab) >  4 && strlen(tab) <  taille_chaine) {
            while (getchar() != '\n'); //vide le buffer
            return tab;  //  renvoyer la chaine sasie
        } else {
            printf("Saisie incorrecte. Veuillez entrer une chaine  de %zu characteres max et 4 mini .\n", taille_chaine);
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }

}
// Fonction pour le contrôle de la saisie d'un numero de tel
char* saisir_numero_tel(char* tab, size_t taille_chaine) {
    // char chaine[20];
    while (1) {
        printf("Veuillez entrer le numero de telephone du contact sans les espaces (%zu caracteres max) : \n", taille_chaine-1);

        // Vérifier la saisie et les conditions
           if (scanf(" %9[^\n]", tab) == 1  && strlen(tab) == taille_chaine) {
            while (getchar() != '\n'); //vide le buffer
            return tab;  //  renvoyer la chaine sasie
        } else {
            printf("Saisie incorrecte. Veuillez entrer un numero de  %zu characteres .\n", taille_chaine);
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
        }
    }

}
// fonction pour afficher la liste des contacs
void affichage_liste_contact(char tab[][20], size_t taille_tableau) {
    printf("Liste des contacts :\n");
    for (size_t i = 0; i < taille_tableau; i++) {
        printf("Contact %zu : %s\n", i + 1, tab[i]);
    }
}
// fonction pour afficher  la liste des numeros de telephones
void affichage_liste_telephone(char tab[][10], size_t taille_tableau) {
    printf("Liste des telephones :\n");
    for (size_t i = 0; i < taille_tableau; i++) {
        printf("Contact %zu : %s\n", i + 1, tab[i]);
    }
}


// Fonction pour supprimer un contact dans un tableau de contacts
void suppression_contact(char tab[][20], size_t taille_tableau, int numero_contact) {
    if (numero_contact < 1 || numero_contact > taille_tableau) {
        printf("Numéro de contact invalide.\n");
        return;
    }

    printf("Suppression du contact numéro %d :\n", numero_contact);

    // Décaler les contacts après le contact à supprimer
    for (size_t i = numero_contact - 1; i < taille_tableau - 1; i++) {
        strcpy(tab[i], tab[i + 1]);
    }

    // Mettre la dernière position à vide (car le contact a été décalé)
    tab[taille_tableau - 1][0] = '\0';  // Remplace la dernière chaîne par une chaîne vide
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