#include <iostream>
#include <fstream>
// #include <string>
#include <iomanip>

using namespace std;

/* MISSION FAIRE DES FONCTIONS
Copier le fichier sans le modifier
Mettre tout le texte en majuscules /
minuscules
Capitaliser ce qui commence par une majuscule
Changement de casse des caractères alphabétiques
Justification à droite du contenu sur 85 caractères
Justification à gauche du contenu sur 85 caractères
Alignement au centre
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

void printCentered(const string &text, int width)
{
    int padding = (width - text.size()) / 2; // Calculer combien d'espaces il faut de chaque côté

    if (padding > 0)
    {
        cout << setw(padding + text.size()) << right << text << endl;
    }
    else
    {
        cout << text << endl; // Si la chaîne est plus longue que la largeur spécifiée
    }
}

int main()
{
    string text = "Bonjour";
    int width = 20; // Spécifier la largeur totale pour centrer

    printCentered(text, width); // Appeler la fonction pour centrer le texte

    return 0;
}
int main()
{

    string fichier_initial = "fichier_initial.txt";     // Nom du fichier d'entrée
    string fichier_corrected = "fichier_corrected.txt"; // Fichier de sortie selon l'opération
    // string ligne;
    int taille_ligne{0};
    // Menu avec les choix
    int menu_choix{0};
    cout << "Choisissez votre option:\n"
         << "1. Copier le fichier sans le modifier\n"
         << "2. Mettre tout le texte en majuscules\n"
         << "3. Mettre tout le texte en minuscules\n"
         << "4. Capitaliser les premières lettres\n"
         << "5. Inverser la casse des caractères\n"
         << "6. Justifier à droite sur 85 catractéres\n"
         << "7. Justifier à gauche 85 catractéres\n"
         << "8. Centrer le texte\n"
         << "9. Sortir du programme O/N \n";
    cin >> menu_choix;

    switch (menu_choix)
    {
    case 1:
        cout << "Vous avez choisi de copier le texte sans le modifier" << menu_choix;
        copier_fichier(fichier_initial, fichier_corrected);
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
        while (getline(fichier_initial, ligne))
        {
            /* code */
            size_t first = ligne.find_first_not_of(" \t\n\r\v");
            if (first != string::npos)
                ligne = ligne.substr(first);
            cout << "first =  " << first << endl;
            if (taille_ligne < 85)
            {
                ligne += (string(85 - taille_ligne, ' '));
            }
            fichier_corrected << ligne << end;
        }

        break;
    case 8:
        cout << "Au revoir à Bientot" << menu_choix;
        return 0;

        break;
    case 9:
        break;

    default:
        break;
    }
    return 0;
}