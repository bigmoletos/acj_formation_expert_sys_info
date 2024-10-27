#include <iostream>
#include <string>
#include "header.hpp"
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage

// déclaration des fonctions
void chrono_start(std::chrono::high_resolution_clock::time_point &t1) void chrono_end(chrono::high_resolution_clock::time_point t1, const string &message)

    // Fonction pour mesurer le temps d'exécution
    void chrono_start(chrono::high_resolution_clock::time_point &t1)
{
    t1 = chrono::high_resolution_clock::now();
}

void chrono_end(chrono::high_resolution_clock::time_point t1, const string &message)
{
    auto t2 = chrono::high_resolution_clock::now();
    cout << message << " : "
         << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << " μs\n";
}
