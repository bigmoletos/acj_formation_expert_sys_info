#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype> // Pour isalpha, toupper, tolower

using namespace std;

// Fonction pour copier le fichier sans le modifier
/**
 * @brief [Description de copier_fichier]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void copier_fichier(const string &inputFile, const string &outputFile)
{
/**
 * @brief [Description de inFile]
 *
 * @param inputFile [Description du paramètre]
 * @return ifstream [Description du retour]
 */
    ifstream inFile(inputFile);
/**
 * @brief [Description de outFile]
 *
 * @param outputFile [Description du paramètre]
 * @return ofstream [Description du retour]
 */
    ofstream outFile(outputFile);

    if (inFile && outFile)
    {
        string line;
        while (getline(inFile, line))
        {
            outFile << line << endl;
        }
        cout << "Fichier copiÃ© sans modification.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

// Fonction pour mettre le texte en majuscules
/**
 * @brief [Description de mettre_majuscule]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void mettre_majuscule(const string &inputFile, const string &outputFile)
{
/**
 * @brief [Description de inFile]
 *
 * @param inputFile [Description du paramètre]
 * @return ifstream [Description du retour]
 */
    ifstream inFile(inputFile);
/**
 * @brief [Description de outFile]
 *
 * @param outputFile [Description du paramètre]
 * @return ofstream [Description du retour]
 */
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
/**
 * @brief [Description de mettre_minuscules]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void mettre_minuscules(const string &inputFile, const string &outputFile)
{
/**
 * @brief [Description de inFile]
 *
 * @param inputFile [Description du paramètre]
 * @return ifstream [Description du retour]
 */
    ifstream inFile(inputFile);
/**
 * @brief [Description de outFile]
 *
 * @param outputFile [Description du paramètre]
 * @return ofstream [Description du retour]
 */
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

// Fonction pour capitaliser les premiÃ¨res lettres de chaque mot
/**
 * @brief [Description de capitaliser_premieres_lettres]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void capitaliser_premieres_lettres(const string &inputFile, const string &outputFile)
{
/**
 * @brief [Description de inFile]
 *
 * @param inputFile [Description du paramètre]
 * @return ifstream [Description du retour]
 */
    ifstream inFile(inputFile);
/**
 * @brief [Description de outFile]
 *
 * @param outputFile [Description du paramètre]
 * @return ofstream [Description du retour]
 */
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
        cout << "Les premiÃ¨res lettres ont Ã©tÃ© capitalisÃ©es.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}
/**
 * @brief [Description de inverser_casse]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void inverser_casse(const string &inputFile, const string &outputFile)
{
/**
 * @brief [Description de inFile]
 *
 * @param inputFile [Description du paramètre]
 * @return ifstream [Description du retour]
 */
    ifstream inFile(inputFile);
/**
 * @brief [Description de outFile]
 *
 * @param outputFile [Description du paramètre]
 * @return ofstream [Description du retour]
 */
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
        cout << "Casse des caractÃ¨res inversÃ©e.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

// Fonction pour justifier le texte Ã  droite
/**
 * @brief [Description de justifier_droite_85car]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void justifier_droite_85car(const string &inputFile, const string &outputFile)
{
/**
 * @brief [Description de inFile]
 *
 * @param inputFile [Description du paramètre]
 * @return ifstream [Description du retour]
 */
    ifstream inFile(inputFile);
/**
 * @brief [Description de outFile]
 *
 * @param outputFile [Description du paramètre]
 * @return ofstream [Description du retour]
 */
    ofstream outFile(outputFile);

    if (inFile && outFile)
    {
        string line;
        while (getline(inFile, line))
        {
            outFile << setw(85) << right << line << endl;
        }
        cout << "Texte justifiÃ© Ã  droite.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

/**
 * @brief [Description de main]
 *
 * @param Aucun [Cette fonction n'a pas de paramètres]
 * @return int [Description du retour]
 */
int main()
{
    string fichier_initial = "fichier_initial.txt";     // Nom du fichier d'entrÃ©e
    string fichier_corrected = "fichier_corrected.txt"; // Fichier de sortie selon l'opÃ©ration
    int menu_choix{0};

    // Menu avec les choix
    cout << "Choisissez votre option:\n"
         << "1. Copier le fichier sans le modifier\n"
         << "2. Mettre tout le texte en majuscules\n"
         << "3. Mettre tout le texte en minuscules\n"
         << "4. Capitaliser les premiÃ¨res lettres\n"
         << "5. Inverser la casse des caractÃ¨res\n"
         << "6. Justifier Ã  droite sur 85 caractÃ¨res\n"
         << "7. Justifier Ã  gauche sur 85 caractÃ¨res\n"
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
        cout << "Capitaliser les premiÃ¨res lettres de chaque mot\n";
        capitaliser_premieres_lettres(fichier_initial, fichier_corrected);
        break;
    case 5:
        cout << "Inverser la casse\n";
        inverser_casse(fichier_initial, fichier_corrected);
        break;
    case 6:
        cout << "Justifer Ã  droite de 85 caractÃ©res\n";
        justifier_droite_85car(fichier_initial, fichier_corrected);
        break;
    case 7:
    {
/**
 * @brief [Description de inFile]
 *
 * @param fichier_initial [Description du paramètre]
 * @return ifstream [Description du retour]
 */
        ifstream inFile(fichier_initial);
/**
 * @brief [Description de outFile]
 *
 * @param fichier_corrected [Description du paramètre]
 * @return ofstream [Description du retour]
 */
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
            cout << "Texte justifiÃ© Ã  gauche sur 85 caractÃ¨res.\n";
        }
        else
        {
            cerr << "Erreur: impossible d'ouvrir le fichier.\n";
        }
        break;
    }
    case 9:
        cout << "Au revoir, Ã  bientÃ´t.\n";
        return 0;
    default:
        cerr << "Choix invalide.\n";
        break;
    }

    return 0;
}
