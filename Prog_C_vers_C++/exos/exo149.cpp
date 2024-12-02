#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

// Fonction pour copier le fichier sans le modifier
/**
 * @brief [Description de copyFile]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void copyFile(const string &inputFile, const string &outputFile)
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

// Fonction pour mettre tout le texte en majuscules
/**
 * @brief [Description de toUpperCase]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void toUpperCase(const string &inputFile, const string &outputFile)
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

// Fonction pour mettre tout le texte en minuscules
/**
 * @brief [Description de toLowerCase]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void toLowerCase(const string &inputFile, const string &outputFile)
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
        cout << "Texte converti en minuscules.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

// Fonction pour capitaliser les premiÃ¨res lettres des mots
/**
 * @brief [Description de capitalize]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void capitalize(const string &inputFile, const string &outputFile)
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
        cout << "Texte capitalisÃ©.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

// Fonction pour inverser la casse des caractÃ¨res
/**
 * @brief [Description de swapCase]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void swapCase(const string &inputFile, const string &outputFile)
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
 * @brief [Description de justifyRight]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void justifyRight(const string &inputFile, const string &outputFile)
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

// Fonction pour justifier le texte Ã  gauche
/**
 * @brief [Description de justifyLeft]
 *
 * @param &inputFile [Description du paramètre]
 * @param &outputFile [Description du paramètre]
 * @return void [Description du retour]
 */
void justifyLeft(const string &inputFile, const string &outputFile)
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
            outFile << setw(85) << left << line << endl;
        }
        cout << "Texte justifiÃ© Ã  gauche.\n";
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
    string inputFile = "input.txt"; // Nom du fichier d'entrÃ©e
    string outputFile;              // Fichier de sortie selon l'opÃ©ration

    // Appel des fonctions selon l'opÃ©ration Ã  effectuer
    int choice;
    cout << "Choisissez une opÃ©ration:\n"
         << "1. Copier le fichier sans le modifier\n"
         << "2. Mettre tout le texte en majuscules\n"
         << "3. Mettre tout le texte en minuscules\n"
         << "4. Capitaliser les premiÃ¨res lettres\n"
         << "5. Inverser la casse des caractÃ¨res\n"
         << "6. Justifier Ã  droite\n"
         << "7. Justifier Ã  gauche\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        outputFile = "output_copy.txt";
        copyFile(inputFile, outputFile);
        break;
    case 2:
        outputFile = "output_uppercase.txt";
        toUpperCase(inputFile, outputFile);
        break;
    case 3:
        outputFile = "output_lowercase.txt";
        toLowerCase(inputFile, outputFile);
        break;
    case 4:
        outputFile = "output_capitalized.txt";
        capitalize(inputFile, outputFile);
        break;
    case 5:
        outputFile = "output_swapcase.txt";
        swapCase(inputFile, outputFile);
        break;
    case 6:
        outputFile = "output_justify_right.txt";
        justifyRight(inputFile, outputFile);
        break;
    case 7:
        outputFile = "output_justify_left.txt";
        justifyLeft(inputFile, outputFile);
        break;
    default:
        cerr << "Choix invalide.\n";
    }

    return 0;
}
