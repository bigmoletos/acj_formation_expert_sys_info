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
#include <chrono>  // Pour les fonctions de chronométrage
#include <unordered_map>


// -------Fonctions pour mesurer le temps-----------------
// Déclaration des fonctions pour mesurer le temps
void chrono_start(std::chrono::high_resolution_clock::time_point &t1);
void chrono_end(const std::chrono::high_resolution_clock::time_point &t1, const std::string &message);

// -------Fonctions pour charger les fichiers
void charger_donnees_fichier(const std::string &nom_fichier, std::vector<int> &tableau);

// -------Fonctions pour construire un tableau vector
void generer_valeurs_aleatoires(std::array<int, 100> &tableau);

#endif // __CHRONO__
