#ifndef __CHRONO__
#define __CHRONO__

#include <string>
#include <iostream>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronomÃ©trage
#include <unordered_map>


// -------Fonctions pour mesurer le temps-----------------
// DÃ©claration des fonctions pour mesurer le temps
/**
 * @brief [Description de chrono_start]
 *
 * @param &t1 [Description du paramètre]
 * @return void [Description du retour]
 */
void chrono_start(std::chrono::high_resolution_clock::time_point &t1);
/**
 * @brief [Description de chrono_end]
 *
 * @param &t1 [Description du paramètre]
 * @param &message [Description du paramètre]
 * @return void [Description du retour]
 */
void chrono_end(const std::chrono::high_resolution_clock::time_point &t1, const std::string &message);

// -------Fonctions pour charger les fichiers
/**
 * @brief [Description de charger_donnees_fichier]
 *
 * @param &nom_fichier [Description du paramètre]
 * @param &tableau [Description du paramètre]
 * @return void [Description du retour]
 */
void charger_donnees_fichier(const std::string &nom_fichier, std::vector<int> &tableau);

// -------Fonctions pour construire un tableau vector
/**
 * @brief [Description de generer_valeurs_aleatoires]
 *
 * @param std::array<int [Description du paramètre]
 * @param &tableau [Description du paramètre]
 * @return void [Description du retour]
 */
void generer_valeurs_aleatoires(std::array<int, 100> &tableau);

#endif // __CHRONO__
