#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tableau_depuis_fichier.hpp"
#include "logger.hpp" // Inclusion du fichier logger

// Fonction pour charger des donnÃ©es Ã  partir d'un fichier dans un tableau
/**
 * @brief [Description de charger_donnees_fichier]
 *
 * @param &nom_fichier [Description du paramètre]
 * @param tableau [Description du paramètre]
 * @return void [Description du retour]
 */
/**
 * @brief [Description de charger_donnees_fichier]
 *
 * @param &nom_fichier [Description du paramètre]
 * @param tableau [Description du paramètre]
 * @return void [Description du retour]
 */
void charger_donnees_fichier(const std::string &nom_fichier, std::vector<int>& tableau)
{
/**
 * @brief [Description de fichier]
 *
 * @param nom_fichier [Description du paramètre]
 * @return std::ifstream [Description du retour]
 */
/**
 * @brief [Description de fichier]
 *
 * @param nom_fichier [Description du paramètre]
 * @return std::ifstream [Description du retour]
 */
    std::ifstream fichier(nom_fichier);

    if (!fichier.is_open())
    {
        // std::cerr << "Erreur: impossible d'ouvrir le fichier." << std::endl;
        logger.error("Erreur: impossible d'ouvrir le fichier. " );
        return;
    }

    int valeur;
    while (fichier >> valeur)
    {
        tableau.push_back(valeur); // Ajout de chaque valeur dans le tableau
    }

    fichier.close();
}