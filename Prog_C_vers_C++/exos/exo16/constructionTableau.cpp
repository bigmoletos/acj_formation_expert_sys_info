#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage
#include "header.hpp"

// Fonction pour générer un tableau de 100 valeurs aléatoires
void generer_valeurs_aleatoires(array<int, 100> &tableau)
{
    srand(static_cast<unsigned int>(time(0))); // Initialiser le générateur aléatoire avec l'heure actuelle

    for (int i = 0; i < 100; ++i)
    {
        tableau[i] = rand() % 100; // Générer un nombre aléatoire entre 0 et 99
    }
}

// trouver tous les indices d'une valeur dans un tableau
vector<int> trouver_indices(const vector<int> &tableau, int valeur_recherchee)
{
    vector<int> indices; // Stocker les indices des occurrences trouvées

    // Parcourir le tableau
    for (int i = 0; i < tableau.size(); ++i)
    {
        if (tableau[i] == valeur_recherchee)
        {
            indices.push_back(i); // Ajouter l'indice à la liste des résultats
        }
    }
    return indices; // Retourner tous les indices trouvés
}