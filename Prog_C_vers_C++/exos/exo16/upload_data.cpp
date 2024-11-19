#include <iostream>
#include <fstream>
#include <string>
#include "header.hpp"

// Fonction pour charger des données à partir d'un fichier dans un tableau

void charger_donnees_fichier(const std::string &nom_fichier, std::vector<int> &tableau)
{
    std::ifstream fichier(nom_fichier);

    if (!fichier.is_open())
    {
        std::cerr << "Erreur: impossible d'ouvrir le fichier." << std::endl;
        return;
    }

    int valeur;
    while (fichier >> valeur)
    {
        tableau.push_back(valeur); // Ajout de chaque valeur dans le tableau
    }

    fichier.close();
}