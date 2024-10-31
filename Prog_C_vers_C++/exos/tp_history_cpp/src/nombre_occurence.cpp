#include "nombre_occurence.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

/**
 * @class NombreOccurrence
 * @brief Classe qui calcule et affiche le nombre d'occurrences de commandes
 *        dans un ensemble de lignes de texte.
 *
 * La classe `NombreOccurrence` prend un vecteur de chaînes de caractères,
 * interprète chaque chaîne comme une ligne contenant une commande shell,
 * et compte le nombre de fois que chaque commande apparaît.
 */

/**
 * @brief Constructeur qui initialise les lignes du fichier.
 * @param lignes Vecteur de chaînes de caractères représentant chaque ligne du fichier.
 */
NombreOccurrence::NombreOccurrence(const std::vector<std::string> &lignes)
    : lignesFichier(lignes) {} // Initialise lignesFichier avec les lignes fournies.

/**
 * @brief Calcule le nombre d'occurrences de chaque commande dans les lignes fournies.
 *
 * Cette méthode parcourt chaque ligne de `lignesFichier`, extrait la première
 * "commande" de la ligne, et incrémente un compteur dans la map `occurrences`
 * pour chaque commande rencontrée.
 */
void NombreOccurrence::calculerOccurrences()
{
    for (const auto &ligne : lignesFichier)
    {
        // Crée un flux de chaîne pour analyser la ligne
        std::istringstream iss(ligne);
        std::string commande;

        // Extrait la première "commande" de la ligne
        iss >> commande;

        // Si la commande n'est pas vide, incrémente son compteur dans la map
        if (!commande.empty())
        {
            occurrences[commande]++; // Enregistre ou incrémente l'occurrence de la commande
        }
    }
}

/**
 * @brief Affiche les commandes et leur nombre d'occurrences, triées par ordre décroissant.
 *
 * Cette méthode copie la map `occurrences` dans un vecteur pour permettre le tri
 * en fonction du nombre d'occurrences. Elle affiche ensuite chaque commande
 * et son nombre d'occurrences par ordre décroissant.
 */
void NombreOccurrence::afficherOccurrences() const
{
    // Convertir la map en vecteur pour permettre le tri
    std::vector<std::pair<std::string, int>> occurrencesTriees(occurrences.begin(), occurrences.end());

    // Tri par ordre décroissant du nombre d'occurrences
    std::sort(occurrencesTriees.begin(), occurrencesTriees.end(),
              [](const auto &a, const auto &b)
              {
                  return a.second > b.second; // Trie en fonction du nombre d'occurrences
              });

    // Affiche les résultats triés
    std::cout << "Nombre d'occurrences de chaque commande :" << std::endl;
    for (const auto &pair : occurrencesTriees)
    {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}
