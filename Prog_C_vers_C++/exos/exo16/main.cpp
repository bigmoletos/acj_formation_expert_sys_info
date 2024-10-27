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

// // Fonction pour mesurer le temps d'exécution
// void chrono_start(chrono::high_resolution_clock::time_point &t1)
// {
//     t1 = chrono::high_resolution_clock::now();
// }

// void chrono_end(chrono::high_resolution_clock::time_point t1, const string &message)
// {
//     auto t2 = chrono::high_resolution_clock::now();
//     cout << message << " : "
//          << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << " μs\n";
// }

// // Fonction pour charger des données à partir d'un fichier dans un tableau
// void charger_donnees_fichier(const string &nom_fichier, vector<int> &tableau)
// {
//     ifstream fichier(nom_fichier);

//     if (!fichier.is_open())
//     {
//         cerr << "Erreur: impossible d'ouvrir le fichier." << endl;
//         return;
//     }

//     int valeur;
//     while (fichier >> valeur)
//     {
//         tableau.push_back(valeur); // Ajout de chaque valeur dans le tableau
//     }

//     fichier.close();
// }

// // Fonction pour générer un tableau de 100 valeurs aléatoires
// void generer_valeurs_aleatoires(array<int, 100> &tableau)
// {
//     srand(static_cast<unsigned int>(time(0))); // Initialiser le générateur aléatoire avec l'heure actuelle

//     for (int i = 0; i < 100; ++i)
//     {
//         tableau[i] = rand() % 100; // Générer un nombre aléatoire entre 0 et 99
//     }
// }

// // trouver tous les indices d'une valeur dans un tableau
// vector<int> trouver_indices(const vector<int> &tableau, int valeur_recherchee)
// {
//     vector<int> indices; // Stocker les indices des occurrences trouvées

//     // Parcourir le tableau
//     for (int i = 0; i < tableau.size(); ++i)
//     {
//         if (tableau[i] == valeur_recherchee)
//         {
//             indices.push_back(i); // Ajouter l'indice à la liste des résultats
//         }
//     }
//     return indices; // Retourner tous les indices trouvés
// }




    // int main()
    // {

    //         // Création d'un objet ConstruireTableau
    // ConstruireTableau monTableau("MonTableau", 100);

    // // Générer des valeurs aléatoires dans le tableau
    // monTableau.genererValeursAleatoires();

    // // Mesurer le temps d'une recherche de valeur
    // std::chrono::high_resolution_clock::time_point t1;
    // chrono_start(t1);
    //     std::add_pointer::high_resolution_clock::time_point t1; // Point pour stocker l'heure de début

    //     // Partie 1 : Charger des données depuis un fichier
    //     vector<int> tableau_donnees;
    //     string nom_fichier = "randIntegers_random.txt";
    //     string nom_fichier2 = "randIntegers_sorted.txt";

    //     // Chronométrage du chargement des données du fichier
    //     chrono_start(t1);
    //     charger_donnees_fichier(nom_fichier, tableau_donnees);

    //     // Afficher les données chargées
    //     cout << "Données chargées depuis le fichier :\n";
    //     for (const int &valeur : tableau_donnees)
    //     {
    //         cout << valeur << " ";
    //     }
    //     cout << endl;
    //     chrono_end(t1, "Temps de chargement des données depuis le fichier");

    //     //----------------------------------------------------
    //     // Partie 2 : Générer un tableau de 100 valeurs aléatoires
    //     array<int, 100> tableau_aleatoire;

    //     // Chronométrage de la génération des valeurs aléatoires
    //     chrono_start(t1);
    //     generer_valeurs_aleatoires(tableau_aleatoire);

    //     // Afficher les valeurs aléatoires générées
    //     cout << "\nTableau de 100 valeurs aléatoires :\n";
    //     for (int i = 0; i < 100; ++i)
    //     {
    //         cout << tableau_aleatoire[i] << " ";
    //     }
    //     cout << endl;
    //     chrono_end(t1, "Temps de génération des valeurs aléatoires");

    //     // Question 2
    //     //  Valeur à rechercher
    //     int valeur_recherchee = 5;

    //     // Trouver les indices où la valeur  apparaît dans le tableau
    //     vector<int> indices = trouver_indices(tableau_aleatoire, valeur_recherchee);

    //     // Afficher les indices trouvés
    //     if (!indices.empty())
    //     {
    //         cout << "La valeur " << valeur_recherchee << " est trouvée aux indices : ";
    //         for (int indice : indices)
    //         {
    //             cout << indice << " ";
    //         }
    //         cout << endl;
    //     }
    //     else
    //     {
    //         cout << "La valeur " << valeur_recherchee << " n'a pas été trouvée dans le tableau." << endl;
    //     }

    //     return 0;
    // }

int main()
{
    // Création d'un objet ConstruireTableau
    ConstruireTableau monTableau("MonTableau", 100);

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
