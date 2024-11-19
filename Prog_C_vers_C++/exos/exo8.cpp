#include <stdio.h>   // Pour la partie C
#include <stdlib.h>
#include <iostream>  // Pour la partie C++
#include <string.h>  // Pour les manipulations de chaînes en C

using namespace std;

/**
 * @brief [Description de main]
 *
 * @param Aucun [Cette fonction n'a pas de param�tres]
 * @return int [Description du retour]
 */
int main() {
    // Variables pour stocker les données
    char nom[20], prenom[20], pays_naissance[20], profession[20];
    float taille;
    char date_naissance[10];
    int choix;

    // Demander à l'utilisateur de choisir entre la saisie en C ou en C++
    cout << "Choisissez le mode de saisie:\n";
    cout << "1. Saisie en C\n";
    cout << "2. Saisie en C++\n";
    cout << "Votre choix: ";
    cin >> choix;

    if (choix == 1) {
        // ---- Saisie en C ----
        printf("----- Saisie en C -----\n");
        printf("Entrez votre nom: ");
        scanf("%s", nom);

        printf("Entrez votre prénom: ");
        scanf("%s", prenom);

        printf("Entrez votre taille en mètres: ");
        scanf("%f", &taille);

        printf("Entrez votre date de naissance (jj/mm/aaaa): ");
        scanf("%s", date_naissance);

        printf("Entrez votre pays de naissance: ");
        scanf("%s", pays_naissance);

        printf("Entrez votre profession: ");
        scanf("%s", profession);

    } else if (choix == 2) {
        // ---- Saisie en C++ ----
        cout << "----- Saisie en C++ -----" << endl;
        cout << "Entrez votre nom: ";
        cin >> nom;

        cout << "Entrez votre prénom: ";
        cin >> prenom;

        cout << "Entrez votre taille en mètres: ";
        cin >> taille;

        cout << "Entrez votre date de naissance (jj/mm/aaaa): ";
        cin >> date_naissance;

        cout << "Entrez votre pays de naissance: ";
        cin >> pays_naissance;

        cout << "Entrez votre profession: ";
        cin >> profession;
    } else {
        cout << "Choix invalide, programme terminé." << endl;
        return 1;
    }

    // ---- Affichage en C++ ----
    cout << "\n----- Affichage en C++ -----" << endl;
    cout << "Nom: " << nom << endl;
    cout << "Prénom: " << prenom << endl;
    cout << "Taille: " << taille << " mètres" << endl;
    cout << "Date de naissance: " << date_naissance << endl;
    cout << "Pays de naissance: " << pays_naissance << endl;
    cout << "Profession: " << profession << endl;

    return 0;
}
