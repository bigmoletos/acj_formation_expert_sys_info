#ifndef __UPLOAD__
#define __UPLOAD__

#include <string>
#include <iostream>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage
#include <unordered_map>

// -------Fonctions pour charger fichier texte dans tableau-----------------
class ChargeFichierTxt
{
public:
    // Constructeur qui prend le chemin du fichier à charger
    ChargeFichierTxt(const std::string &chemin);

    // Méthode pour charger le fichier
/**
 * @brief [Description de charger]
 *
 * @param Aucun [Cette fonction n'a pas de param�tres]
 * @return bool [Description du retour]
 */
/**
 * @brief [Description de charger]
 *
 * @param Aucun [Cette fonction n'a pas de param�tres]
 * @return bool [Description du retour]
 */
    bool charger();

    // Obtenir les lignes du fichier chargé
    const std::vector<std::string> &getLignes() const;

private:
    std::string cheminFichier;         // Chemin du fichier
    std::vector<std::string> lignes;   // Contenu du fichier
    bool verifierFichier();            // Vérifie si le fichier existe et est accessible
    bool estFichierTexteOuCSV() const; // Vérifie si le fichier est de type .txt ou .csv
};



#endif // __UPLOAD__
