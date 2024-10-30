#include "header.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h> // Pour vérifier l'existence du fichier

// Constructeur
ChargeFichierTxt::ChargeFichierTxt(const std::string &chemin)
    : cheminFichier(chemin) {}

// Méthode pour vérifier l'existence et l'accessibilité du fichier
bool ChargeFichierTxt::verifierFichier()
{
    struct stat buffer;
    return (stat(cheminFichier.c_str(), &buffer) == 0);
}

// Méthode pour vérifier si le fichier est un .txt ou .csv
bool ChargeFichierTxt::estFichierTexteOuCSV() const
{
    return cheminFichier.size() > 4 &&
           (cheminFichier.substr(cheminFichier.size() - 4) == ".txt" ||
            cheminFichier.substr(cheminFichier.size() - 4) == ".csv");
}

// Méthode pour charger le fichier
bool ChargeFichierTxt::charger()
{
    // Vérification du fichier
    if (!verifierFichier())
    {
        std::cerr << "Erreur : Le fichier " << cheminFichier << " n'existe pas ou n'est pas accessible." << std::endl;
        return false;
    }

    // Vérification du type de fichier
    if (!estFichierTexteOuCSV())
    {
        std::cerr << "Erreur : Le fichier doit être au format .txt ou .csv." << std::endl;
        return false;
    }

    // Chargement du fichier
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open())
    {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << std::endl;
        return false;
    }

    // Lecture ligne par ligne
    std::string ligne;
    while (std::getline(fichier, ligne))
    {
        lignes.push_back(ligne);
    }

    fichier.close();
    return true;
}

// Getter pour obtenir les lignes du fichier chargé
const std::vector<std::string> &ChargeFichierTxt::getLignes() const
{
    return lignes;
}
