// fichier Marwa
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Fonction pour lire les secteurs à partir d'un fichier
vector<string> lireSecteurs(const string &nomFichier)
{
    vector<string> secteurs;
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

// Fonction pour afficher les informations des employés
void afficherEmployes(const vector<string> &employes, const vector<string> &adresses, const vector<vector<string>> &telephones, const vector<string> &secteurs)
{
    int taille = employes.size();
    for (int i = 0; i < taille; i++)
    {
        cout << "Nom: " << employes[i] << endl;
        cout << "Adresse: " << adresses[i] << endl;
        cout << "Téléphones: ";
        for (const auto &tel : telephones[i])
        {
            cout << tel << " ";
        }
        cout << endl;
        cout << "Secteur: " << secteurs[i] << endl;
        cout << endl;
    }
}

// Fonction pour trier les employés par secteur
bool comparerParSecteur(int i, int j, const vector<string> &secteurs)
{
    return secteurs[i] < secteurs[j];
}

int main()
{
    // Liste des employés, adresses et numéros de téléphone
    vector<string> employes = {"Dupont-Adrien", "Jérôme-Marc", "Duroc-Vision", "Balboa-Rocky"};
    vector<string> adresses = {"132 rue de Paris", "12 B2 de Marseille", "31 à la E de Lyon", "Los Angeles"};
    vector<vector<string>> telephones = {
        {"06 16 16 16 16"},
        {"17 17 17 17"},
        {"04 45 45 45"},
        {"1 1 2 3 4 5 6 7"}};

    // Lecture des secteurs à partir du fichier
    vector<string> secteurs = lireSecteurs("secteur.txt");

    // Affichage avant tri
    cout << "Liste des employés avant tri:\n";
    afficherEmployes(employes, adresses, telephones, secteurs);

    // Tri par secteur
    vector<int> indices(employes.size());
    iota(indices.begin(), indices.end(), 0); // Créer un vecteur d'indices (0, 1, 2, ...)

    sort(indices.begin(), indices.end(), [&](int i, int j)
         { return comparerParSecteur(i, j, secteurs); });

    // Affichage après tri
    cout << "Liste des employés après tri par secteur:\n";
    for (int i : indices)
    {
        cout << "Nom: " << employes[i] << endl;
        cout << "Adresse: " << adresses[i] << endl;
        cout << "Téléphones: ";
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