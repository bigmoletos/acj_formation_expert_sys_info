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
void chrono_start(std::chrono::high_resolution_clock::time_point &t1);

/**
 * @brief Affiche le temps écoulé depuis le point de départ.
 *
 * @param t1 Point de départ du chronomètre.
 * @param message Message à afficher avec le temps écoulé.
 */
void chrono_end(std::chrono::high_resolution_clock::time_point t1, const string &message);

// Définition des fonctions

void chrono_start(std::chrono::high_resolution_clock::time_point &t1)
{
    t1 = std::chrono::high_resolution_clock::now();
}

void chrono_end(std::chrono::high_resolution_clock::time_point t1, const string &message)
{
    auto t2 = std::chrono::high_resolution_clock::now();
    cout << message << " : "
         << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs\n";
}

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
