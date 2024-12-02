#include <iostream>
#include <array>  // Pour std::array
#include <vector> // Pour std::vector

using namespace std;

/**
 * @brief Programme de comparaison entre un tableau classique, un std::array et un std::vector.
 *
 * Le programme montre la déclaration, l'accès et l'utilisation des trois types de conteneurs en C++ :
 * - Tableau classique : taille fixe, déclaration statique, pas de vérification des limites.
 * - std::array : taille fixe, partie de la bibliothèque standard, avec des méthodes utilitaires.
 * - std::vector : tableau dynamique, peut changer de taille, fourni par la bibliothèque standard.
 */

/**
 * @brief [Description de main]
 *
 * @param Aucun [Cette fonction n'a pas de param�tres]
 * @return int [Description du retour]
 */
int main()
{
    // 1. Tableau classique (tableau statique en C++)
    /**
     * @brief Déclaration d'un tableau classique avec une taille fixe de 5 éléments.
     *
     * - Les éléments sont stockés de manière statique.
     * - L'accès se fait via des indices.
     * - Il n'y a pas de vérification des limites.
     */
    int tableau[5] = {1, 2, 3, 4, 5}; // Déclaration d'un tableau classique
    cout << "Tableau classique (tableau C++):\n";
    for (int i = 0; i < 5; i++)
    {
        cout << tableau[i] << " "; // Accès aux éléments du tableau classique
    }
    cout << "\n\n"; // Saut de ligne pour séparer les résultats

    // 2. std::array (tableau fixe en C++ avec bibliothèque standard)
    /**
     * @brief Utilisation de std::array pour déclarer un tableau avec une taille fixe.
     *
     * - std::array fait partie de la bibliothèque standard C++.
     * - Il offre des méthodes supplémentaires comme .size() et .at() pour plus de sécurité.
     */
    array<int, 5> arrayFixed = {1, 2, 3, 4, 5}; // Un tableau fixe de taille 5
    cout << "std::array (tableau fixe):\n";
    for (size_t i = 0; i < arrayFixed.size(); i++)
    {
        cout << arrayFixed[i] << " "; // Accès aux éléments de std::array
    }
    cout << "\n\n";

    // 3. std::vector (tableau dynamique en C++)
    /**
     * @brief Utilisation de std::vector pour déclarer un tableau dynamique.
     *
     * - std::vector est un conteneur dynamique, permettant d'ajouter et de retirer des éléments à tout moment.
     * - Il offre des méthodes comme .push_back() et .pop_back() pour manipuler la taille du tableau.
     */
    vector<int> vec = {1, 2, 3, 4, 5}; // Un vecteur dynamique
    vec.push_back(6);                  // On peut ajouter des éléments à un std::vector dynamiquement
    cout << "std::vector (tableau dynamique):\n";
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " "; // Accès aux éléments du std::vector
    }
    cout << "\n";

    return 0;
}
