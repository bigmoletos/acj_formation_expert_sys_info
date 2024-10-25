#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* MISSION FAIRE DES FONCTIONS
Copier le fichier sans le modifier
Mettre tout le texte en majuscules /
minuscules
Capitaliser ce qui commence par une majuscule
Changement de casse des caractères alphabétiques
Justification à droite du contenu sur 85 caractères
Justification à gauche du contenu sur 85 caractères
*/

// Fonction pour copier le fichier sans le modifier
void copier_fichier(const string &fichier_initial, const string &fichier_corrected)
{
    ifstream inFile(fichier_initial);
    ofstream outFile(fichier_corrected);

    if (inFile && outFile)
    {
        string line;
        while (getline(inFile, line))
        {
            outFile << line << endl;
        }
        cout << "Fichier copié sans modification.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

void main()
{

    string fichier_initial = "fichier_initial.txt"; // Nom du fichier d'entrée
    string fichier_corrected;                       // Fichier de sortie selon l'opération

    // Menu avec les choix
    int menu_choix{0};
    cout << "Choisissez votre option:\n"
         << "1. Copier le fichier sans le modifier\n"
         << "2. Mettre tout le texte en majuscules\n"
         << "3. Mettre tout le texte en minuscules\n"
         << "4. Capitaliser les premières lettres\n"
         << "5. Inverser la casse des caractères\n"
         << "6. Justifier à droite\n"
         << "7. Justifier à gauche\n"
         << "8. Sortir du programme O/N \n";
    cin >> menu_choix;

    switch (menu_choix)
    {
    case 1:
        cout << "Vous avez choisi de copier le texte sans le modifier" << menu_choix;

        break;
    case 2:
        
        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    case 7:

        break;
    case 8:

        break;
    case 9:

        break;

    default:
        break;
    }
}