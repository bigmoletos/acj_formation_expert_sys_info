#include <iostream>
#include <string>
#include "header.hpp"
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage

using namespace std;

// Déclaration des fonctions

/**
 * @brief Démarre un chronomètre en enregistrant le point de départ.
 *
 * @param t1 Référence vers le point de départ du chronomètre.
 */
/**
 * @brief [Description de chrono_start]
 *
 * @param &t1 [Description du param�tre]
 * @return void [Description du retour]
 */
void chrono_start(std::chrono::high_resolution_clock::time_point &t1);

/**
 * @brief Affiche le temps écoulé depuis le point de départ.
 *
 * @param t1 Point de départ du chronomètre.
 * @param message Message à afficher avec le temps écoulé.
 */
/**
 * @brief [Description de chrono_end]
 *
 * @param t1 [Description du param�tre]
 * @param &message [Description du param�tre]
 * @return void [Description du retour]
 */
void chrono_end(std::chrono::high_resolution_clock::time_point t1, const string &message);

// Définition des fonctions

/**
 * @brief [Description de chrono_start]
 *
 * @param &t1 [Description du param�tre]
 * @return void [Description du retour]
 */
void chrono_start(std::chrono::high_resolution_clock::time_point &t1)
{
    t1 = std::chrono::high_resolution_clock::now();
}

/**
 * @brief [Description de chrono_end]
 *
 * @param t1 [Description du param�tre]
 * @param &message [Description du param�tre]
 * @return void [Description du retour]
 */
void chrono_end(std::chrono::high_resolution_clock::time_point t1, const string &message)
{
    auto t2 = std::chrono::high_resolution_clock::now();
    cout << message << " : "
         << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs\n";
}

/**
 * @brief [Description de main]
 *
 * @param Aucun [Cette fonction n'a pas de param�tres]
 * @return int [Description du retour]
 */
int main()
{
    // Exemple d'utilisation
    std::chrono::high_resolution_clock::time_point t1;

    chrono_start(t1); // Démarre le chronomètre

    // Simule une tâche
    for (volatile int i = 0; i < 1000000; ++i)
        ;

    chrono_end(t1, "Temps écoulé"); // Affiche le temps écoulé

    return 0;
}
