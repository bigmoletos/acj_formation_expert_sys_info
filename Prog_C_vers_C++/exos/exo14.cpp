#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype> // Pour isalpha, toupper, tolower

using namespace std;

// Fonction pour copier le fichier sans le modifier
void copier_fichier(const string &inputFile, const string &outputFile)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

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

// Fonction pour mettre le texte en majuscules
void mettre_majuscule(const string &inputFile, const string &outputFile)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (inFile && outFile)
    {
        string line;
        while (getline(inFile, line))
        {
            transform(line.begin(), line.end(), line.begin(), ::toupper);
            outFile << line << endl;
        }
        cout << "Texte converti en majuscules.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}
// Fonction pour mettre le texte en minuscules
void mettre_minuscules(const string &inputFile, const string &outputFile)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (inFile && outFile)
    {
        string line;
        while (getline(inFile, line))
        {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            outFile << line << endl;
        }
        cout << "Texte converti en majuscules.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

// Fonction pour capitaliser les premières lettres de chaque mot
void capitaliser_premieres_lettres(const string &inputFile, const string &outputFile)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (inFile && outFile)
    {
        string line;
        while (getline(inFile, line))
        {
            bool capitalizeNext = true;
            for (char &ch : line)
            {
                if (capitalizeNext && isalpha(ch))
                {
                    ch = toupper(ch);
                    capitalizeNext = false;
                }
                else if (isspace(ch))
                {
                    capitalizeNext = true;
                }
            }
            outFile << line << endl;
        }
        cout << "Les premières lettres ont été capitalisées.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}
void inverser_casse(const string &inputFile, const string &outputFile)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (inFile && outFile)
    {
        string line;
        while (getline(inFile, line))
        {
            for (char &ch : line)
            {
                if (islower(ch))
                {
                    ch = toupper(ch);
                }
                else if (isupper(ch))
                {
                    ch = tolower(ch);
                }
            }
            outFile << line << endl;
        }
        cout << "Casse des caractères inversée.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

// Fonction pour justifier le texte à droite
void justifier_droite_85car(const string &inputFile, const string &outputFile)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (inFile && outFile)
    {
        string line;
        while (getline(inFile, line))
        {
            outFile << setw(85) << right << line << endl;
        }
        cout << "Texte justifié à droite.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

int main()
{
    string fichier_initial = "fichier_initial.txt";     // Nom du fichier d'entrée
    string fichier_corrected = "fichier_corrected.txt"; // Fichier de sortie selon l'opération
    int menu_choix{0};

    // Menu avec les choix
    cout << "Choisissez votre option:\n"
         << "1. Copier le fichier sans le modifier\n"
         << "2. Mettre tout le texte en majuscules\n"
         << "3. Mettre tout le texte en minuscules\n"
         << "4. Capitaliser les premières lettres\n"
         << "5. Inverser la casse des caractères\n"
         << "6. Justifier à droite sur 85 caractères\n"
         << "7. Justifier à gauche sur 85 caractères\n"
         << "8. Centrer le texte\n"
         << "9. Sortir du programme\n";

    cin >> menu_choix;

    switch (menu_choix)
    {
    case 1:
        cout << "Vous avez choisi de copier le fichier sans le modifier\n";
        copier_fichier(fichier_initial, fichier_corrected);
        break;
    case 2:
        cout << "Mettre tout le texte en majuscules\n";
        mettre_majuscule(fichier_initial, fichier_corrected);
        break;
    case 3:
        cout << "Mettre tout le texte en minuscules\n";
        mettre_minuscules(fichier_initial, fichier_corrected);
        break;
    case 4:
        cout << "Capitaliser les premières lettres de chaque mot\n";
        capitaliser_premieres_lettres(fichier_initial, fichier_corrected);
        break;
    case 5:
        cout << "Inverser la casse\n";
        inverser_casse(fichier_initial, fichier_corrected);
        break;
    case 6:
        cout << "Justifer à droite de 85 caractéres\n";
        justifier_droite_85car(fichier_initial, fichier_corrected);
        break;
    case 7:
    {
        ifstream inFile(fichier_initial);
        ofstream outFile(fichier_corrected);
        string ligne;
        if (inFile && outFile)
        {
            while (getline(inFile, ligne))
            {
                size_t first = ligne.find_first_not_of(" \t\n\r\v");
                if (first != string::npos)
                {
                    ligne = ligne.substr(first);
                }
                if (ligne.length() < 85)
                {
                    ligne += string(85 - ligne.length(), ' '); // Remplir avec des espaces
                }
                outFile << ligne << endl;
            }
            cout << "Texte justifié à gauche sur 85 caractères.\n";
        }
        else
        {
            cerr << "Erreur: impossible d'ouvrir le fichier.\n";
        }
        break;
    }
    case 9:
        cout << "Au revoir, à bientôt.\n";
        return 0;
    default:
        cerr << "Choix invalide.\n";
        break;
    }

    return 0;
}
