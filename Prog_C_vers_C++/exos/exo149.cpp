#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

// Fonction pour copier le fichier sans le modifier
void copyFile(const string &inputFile, const string &outputFile)
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

// Fonction pour mettre tout le texte en majuscules
void toUpperCase(const string &inputFile, const string &outputFile)
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

// Fonction pour mettre tout le texte en minuscules
void toLowerCase(const string &inputFile, const string &outputFile)
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
        cout << "Texte converti en minuscules.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

// Fonction pour capitaliser les premières lettres des mots
void capitalize(const string &inputFile, const string &outputFile)
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
        cout << "Texte capitalisé.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

// Fonction pour inverser la casse des caractères
void swapCase(const string &inputFile, const string &outputFile)
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
void justifyRight(const string &inputFile, const string &outputFile)
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

// Fonction pour justifier le texte à gauche
void justifyLeft(const string &inputFile, const string &outputFile)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (inFile && outFile)
    {
        string line;
        while (getline(inFile, line))
        {
            outFile << setw(85) << left << line << endl;
        }
        cout << "Texte justifié à gauche.\n";
    }
    else
    {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
    }
}

int main()
{
    string inputFile = "input.txt"; // Nom du fichier d'entrée
    string outputFile;              // Fichier de sortie selon l'opération

    // Appel des fonctions selon l'opération à effectuer
    int choice;
    cout << "Choisissez une opération:\n"
         << "1. Copier le fichier sans le modifier\n"
         << "2. Mettre tout le texte en majuscules\n"
         << "3. Mettre tout le texte en minuscules\n"
         << "4. Capitaliser les premières lettres\n"
         << "5. Inverser la casse des caractères\n"
         << "6. Justifier à droite\n"
         << "7. Justifier à gauche\n";
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
