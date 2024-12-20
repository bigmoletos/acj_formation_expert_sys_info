#include <iostream>
#include <fstream>
#include <string>
#include "header.hpp"

// Fonction pour charger des données à partir d'un fichier dans un tableau

/**
 * @brief [Description de charger_donnees_fichier]
 *
 * @param &nom_fichier [Description du param�tre]
 * @param &tableau [Description du param�tre]
 * @return void [Description du retour]
 */
void charger_donnees_fichier(const std::string &nom_fichier, std::vector<int> &tableau)
{
/**
 * @brief [Description de fichier]
 *
 * @param nom_fichier [Description du param�tre]
 * @return std::ifstream [Description du retour]
 */
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