#include "header.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

// Constructeur qui initialise les lignes du fichier
NombreOccurrence::NombreOccurrence(const std::vector<std::string> &lignes)
    : lignesFichier(lignes) {}

// Méthode pour calculer les occurrences des commandes
void NombreOccurrence::calculerOccurrences()
{
    for (const auto &ligne : lignesFichier)
    {
        std::istringstream iss(ligne);
        std::string commande;
        iss >> commande; // Récupère la première commande de la ligne

        if (!commande.empty())
        {
            occurrences[commande]++; // Incrémente le compteur pour cette commande
        }
    }
}

// Méthode pour afficher les commandes et leur nombre d'occurrences, triées par ordre décroissant
void NombreOccurrence::afficherOccurrences() const
{
    // Convertir la map en vecteur pour pouvoir trier
    std::vector<std::pair<std::string, int>> occurrencesTriees(occurrences.begin(), occurrences.end());

    // Trier les commandes par nombre d'occurrences (ordre décroissant)
    std::sort(occurrencesTriees.begin(), occurrencesTriees.end(),
              [](const auto &a, const auto &b)
              {
                  return a.second > b.second;
              });

    // Afficher les résultats
    std::cout << "Nombre d'occurrences de chaque commande :" << std::endl;
    for (const auto &pair : occurrencesTriees)
    {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}