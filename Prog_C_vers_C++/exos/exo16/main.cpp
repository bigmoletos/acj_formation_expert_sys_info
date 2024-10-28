#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage
#include "header.hpp"
// using namespace std;

/*
1 - Lecture d'un fichier et enregistrement du contenu dans un tableau
2 - Trouver l'indice de chacune des occurrences d'une valeur dans un tableau
3 - Trouver l'indice de la première occurrence d'une valeur dans un tableau
4 - Trouver l'indice de chaque occurrence d'une valeur dans un tableau trié
5 - Trouver l'indice de la première occurrence d'une valeur dans un tableau trié
6 - Peut-on être plus efficace dans chacun des cas évoqués dans cet exercice ?
*/

int main()
{
    // Création d'un objet ConstruireTableau
    ConstruireTableau monTableau("MonTableau", 100);

    // Création d'un objet ConstruireTableau
    genererValeursAleatoires monTableau("MonTableau", 100);

    // Générer des valeurs aléatoires dans le tableau
    monTableau.genererValeursAleatoires();

    // Mesurer le temps d'une recherche de valeur
    std::chrono::high_resolution_clock::time_point t1;
    chrono_start(t1);

    // Rechercher les indices d'une valeur spécifique
    int valeurRecherchee = 42;
    auto indices = monTableau.trouverIndices(valeurRecherchee);

    chrono_end(t1, "Recherche des indices de la valeur");

    // Afficher les indices trouvés
    if (!indices.empty())
    {
        std::cout << "Indices trouvés pour la valeur " << valeurRecherchee << " : ";
        for (const auto &indice : indices)
        {
            std::cout << indice << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Valeur " << valeurRecherchee << " non trouvée dans le tableau." << std::endl;
    }
    // Charger des données à partir d'un fichier
    monTableau.chargerDonneesFichier("data.txt");

    return 0;
}
