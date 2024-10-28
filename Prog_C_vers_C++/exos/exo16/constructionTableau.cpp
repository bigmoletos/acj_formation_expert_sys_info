#include <iostream>
// #include <fstream>
// #include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
// #include <chrono>  // Pour les fonctions de chronométrage
#include "random"
#include "header.hpp"

// Fonction pour générer un tableau de 100 valeurs aléatoires
void generer_valeurs_aleatoires(std::vector<int> &tableau, int taille = 100)
{

    // Initailiser les generateurs de nombres aléatoires
    std::mt19937 generateur(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<int> distribution(0, 90);

    // redmimensionner le tableau
    tableau.resize(taille);

    // srand(static_cast<unsigned int>(time(0))); // Initialiser le générateur aléatoire avec l'heure actuelle

    // generer des valeurs aloéatoires
    for (int i = 0; i < 100; ++i)
    {
        tableau[i] = distribution(generateur) // Générer un nombre aléatoire entre 0 et 99
    }
}

// Fonction pour trouver tous les indices d'une valeur dans un tableau
std::vector<int> trouver_indices(const std::vector<int> &tableau, int valeur_recherchee)
{
    std::vector<int> indices; // Stocker les indices des occurrences trouvées

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
