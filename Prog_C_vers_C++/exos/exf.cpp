// fichier Marwa
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Fonction pour lire les secteurs √† partir d'un fichier
/**
 * @brief [Description de lireSecteurs]
 *
 * @param &nomFichier [Description du paramËtre]
 * @return vector<string> [Description du retour]
 */
vector<string> lireSecteurs(const string &nomFichier)
{
    vector<string> secteurs;
/**
 * @brief [Description de fichier]
 *
 * @param nomFichier [Description du paramËtre]
 * @return ifstream [Description du retour]
 */
    ifstream fichier(nomFichier);
    string ligne;

    if (fichier.is_open())
    {
        while (getline(fichier, ligne))
        {
            secteurs.push_back(ligne);
        }
        fichier.close();
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier " << nomFichier << endl;
    }
    return secteurs;
}

// Fonction pour afficher les informations des employ√©s
/**
 * @brief [Description de afficherEmployes]
 *
 * @param &employes [Description du paramËtre]
 * @param &adresses [Description du paramËtre]
 * @param &telephones [Description du paramËtre]
 * @param &secteurs [Description du paramËtre]
 * @return void [Description du retour]
 */
void afficherEmployes(const vector<string> &employes, const vector<string> &adresses, const vector<vector<string>> &telephones, const vector<string> &secteurs)
{
    int taille = employes.size();
    for (int i = 0; i < taille; i++)
    {
        cout << "Nom: " << employes[i] << endl;
        cout << "Adresse: " << adresses[i] << endl;
        cout << "T√©l√©phones: ";
        for (const auto &tel : telephones[i])
        {
            cout << tel << " ";
        }
        cout << endl;
        cout << "Secteur: " << secteurs[i] << endl;
        cout << endl;
    }
}

// Fonction pour trier les employ√©s par secteur
/**
 * @brief [Description de comparerParSecteur]
 *
 * @param i [Description du paramËtre]
 * @param j [Description du paramËtre]
 * @param &secteurs [Description du paramËtre]
 * @return bool [Description du retour]
 */
bool comparerParSecteur(int i, int j, const vector<string> &secteurs)
{
    return secteurs[i] < secteurs[j];
}

/**
 * @brief [Description de main]
 *
 * @param Aucun [Cette fonction n'a pas de paramËtres]
 * @return int [Description du retour]
 */
int main()
{
    // Liste des employ√©s, adresses et num√©ros de t√©l√©phone
    vector<string> employes = {"Dupont-Adrien", "J√©r√¥me-Marc", "Duroc-Vision", "Balboa-Rocky"};
    vector<string> adresses = {"132 rue de Paris", "12 B2 de Marseille", "31 √† la E de Lyon", "Los Angeles"};
    vector<vector<string>> telephones = {
        {"06 16 16 16 16"},
        {"17 17 17 17"},
        {"04 45 45 45"},
        {"1 1 2 3 4 5 6 7"}};

    // Lecture des secteurs √† partir du fichier
    vector<string> secteurs = lireSecteurs("secteur.txt");

    // Affichage avant tri
    cout << "Liste des employ√©s avant tri:\n";
    afficherEmployes(employes, adresses, telephones, secteurs);

    // Tri par secteur
/**
 * @brief [Description de indices]
 *
 * @param employes.size() [Description du paramËtre]
 * @return vector<int> [Description du retour]
 */
    vector<int> indices(employes.size());
    iota(indices.begin(), indices.end(), 0); // Cr√©er un vecteur d'indices (0, 1, 2, ...)

    sort(indices.begin(), indices.end(), [&](int i, int j)
         { return comparerParSecteur(i, j, secteurs); });

    // Affichage apr√®s tri
    cout << "Liste des employ√©s apr√®s tri par secteur:\n";
    for (int i : indices)
    {
        cout << "Nom: " << employes[i] << endl;
        cout << "Adresse: " << adresses[i] << endl;
        cout << "T√©l√©phones: ";
        for (const auto &tel : telephones[i])
        {
            cout << tel << " ";
        }
        cout << endl;
        cout << "Secteur: " << secteurs[i] << endl;
        cout << endl;
    }

    return 0;
}