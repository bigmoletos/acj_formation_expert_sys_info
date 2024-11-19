#include "nombre_occurence.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include "logger.hpp" 


NombreOccurrence::NombreOccurrence(const std::vector<std::string> &lignes)
    : lignesFichier(lignes)
{
    logger.info("Initialisation des lignes du fichier.");
}

void NombreOccurrence::calculerOccurrences()
{
    for (const auto &ligne : lignesFichier)
    {
        // Vérifie si la ligne commence par "sudo"
        if (ligne.rfind("sudo", 0) == 0)
        {
            occurrences[ligne]++;
            logger.info("Commande lue (sudo) : " + ligne + " (" + std::to_string(occurrences[ligne]) + " occurrences)");
        }
        else
        {
/**
 * @brief [Description de iss]
 *
 * @param ligne [Description du param�tre]
 * @return std::istringstream [Description du retour]
 */
/**
 * @brief [Description de iss]
 *
 * @param ligne [Description du param�tre]
 * @return std::istringstream [Description du retour]
 */
            std::istringstream iss(ligne);
            std::string commande;
            iss >> commande;

            if (!commande.empty())
            {
                occurrences[commande]++;
                logger.info("Commande lue : " + commande + " (" + std::to_string(occurrences[commande]) + " occurrences)");
            }
            else
            {
                logger.warning("Ligne vide ou commande non trouvée dans : " + ligne);
            }
        }
    }
}

void NombreOccurrence::afficherOccurrences() const
{
    // Log avant l'affichage
    logger.info("Affichage des occurrences triées");

    std::vector<std::pair<std::string, int>> occurrencesTriees(occurrences.begin(), occurrences.end());
    std::sort(occurrencesTriees.begin(), occurrencesTriees.end(),
              [](const auto &a, const auto &b)
              {
                  return a.second > b.second; // Trie en fonction du nombre d'occurrences
              });

    // Affiche les résultats triés
    std::cout << "Nombre d'occurrences de chaque commande :" << std::endl;
    for (const auto &pair : occurrencesTriees)
    {
        // std::cout << pair.first << " : " << pair.second << std::endl;
        logger.info(pair.first + ": " + std::to_string(pair.second));
    }
}

std::vector<std::string> NombreOccurrence::getCommandesAvecSudo() const
{
    std::vector<std::string> commandesAvecSudo;

    for (const auto &pair : occurrences)
    {
        // Vérifie si la commande commence par "sudo"
        if (pair.first.rfind("sudo", 0) == 0)
        {
            commandesAvecSudo.push_back(pair.first);
            logger.info("Ajout de la commande avec sudo : " + pair.first);
        }
    }

    if (commandesAvecSudo.empty())
    {
        logger.warning("Aucune commande avec 'sudo' trouvée.");
    }

    return commandesAvecSudo;
}
// #include "nombre_occurence.hpp"
// #include <iostream>
// #include <algorithm>
// #include <sstream>

// /**
//  * @class NombreOccurrence
//  * @brief Classe qui calcule et affiche le nombre d'occurrences de commandes
//  *        dans un ensemble de lignes de texte.
//  *
//  * La classe `NombreOccurrence` prend un vecteur de chaînes de caractères,
//  * interprète chaque chaîne comme une ligne contenant une commande shell,
//  * et compte le nombre de fois que chaque commande apparaît.
//  */

// /**
//  * @brief Constructeur qui initialise les lignes du fichier.
//  * @param lignes Vecteur de chaînes de caractères représentant chaque ligne du fichier.
//  */
// NombreOccurrence::NombreOccurrence(const std::vector<std::string> &lignes)
//     : lignesFichier(lignes) {} // Initialise lignesFichier avec les lignes fournies.

// /**
//  * @brief Calcule le nombre d'occurrences de chaque commande dans les lignes fournies.
//  *
//  * Cette méthode parcourt chaque ligne de `lignesFichier`, extrait la première
//  * "commande" de la ligne, et incrémente un compteur dans la map `occurrences`
//  * pour chaque commande rencontrée.
//  */
// void NombreOccurrence::calculerOccurrences()
// {
//     for (const auto &ligne : lignesFichier)
//     {
//         // Vérifie si la ligne commence par "sudo"
//         if (ligne.rfind("sudo", 0) == 0)
//         {
//             occurrences[ligne]++; // Stocke la ligne entière en tant que clé
//             std::cout << "Commande lue (sudo) : " << ligne << " (" << occurrences[ligne] << " occurrences)" << std::endl;
//         }
//         else
//         {
//             // Traite normalement les autres lignes pour extraire la commande
//             std::istringstream iss(ligne);
//             std::string commande;
//             iss >> commande;

//             if (!commande.empty())
//             {
//                 occurrences[commande]++;
//                 std::cout << "Commande lue : " << commande << " (" << occurrences[commande] << " occurrences)" << std::endl;
//             }
//         }
//     }
// }

// /**
//  * @brief Affiche les commandes et leur nombre d'occurrences, triées par ordre décroissant.
//  *
//  * Cette méthode copie la map `occurrences` dans un vecteur pour permettre le tri
//  * en fonction du nombre d'occurrences. Elle affiche ensuite chaque commande
//  * et son nombre d'occurrences par ordre décroissant.
//  */
// void NombreOccurrence::afficherOccurrences() const
// {
//     // Convertir la map en vecteur pour permettre le tri
//     std::vector<std::pair<std::string, int>> occurrencesTriees(occurrences.begin(), occurrences.end());

//     // Tri par ordre décroissant du nombre d'occurrences
//     std::sort(occurrencesTriees.begin(), occurrencesTriees.end(),
//               [](const auto &a, const auto &b)
//               {
//                   return a.second > b.second; // Trie en fonction du nombre d'occurrences
//               });

//     // Affiche les résultats triés
//     std::cout << "Nombre d'occurrences de chaque commande :" << std::endl;
//     for (const auto &pair : occurrencesTriees)
//     {
//         std::cout << pair.first << " : " << pair.second << std::endl;
//     }
// }

// /**
//  * @brief Renvoie la liste des commandes qui commencent par "sudo".
//  *
//  * Cette méthode parcourt toutes les commandes stockées dans `occurrences`
//  * et collecte celles dont le nom commence par "sudo".
//  *
//  * @return Vecteur de chaînes de caractères contenant les commandes qui commencent par "sudo".
//  */
// std::vector<std::string> NombreOccurrence::getCommandesAvecSudo() const
// {
//     std::vector<std::string> commandesAvecSudo;

//     for (const auto &pair : occurrences)
//     {
//         // Vérifie si la commande commence par "sudo"
//         if (pair.first.rfind("sudo", 0) == 0)
//         {
//             commandesAvecSudo.push_back(pair.first);
//             // std::cout << "Ajout de la commande avec sudo : " << pair.first << std::endl;
//             logger.info("Ajout de la commande avec sudo : " + pair.first);
//         }
//     }

//     return commandesAvecSudo;
// }

