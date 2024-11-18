#include <vector>
#include <iostream>
#include <list>
#include <algorithm> // pour std::sort
#include <algorithm> // pour std::count_if
using namespace std;

// ## Question 5 : Algorithmes STL




// Fonction pour afficher les éléments d'un std::vector avec des itérateurs explicites
void afficher_vector_avec_iterateurs(const vector<int>& vec) {
    cout << "Contenu du vector avec itérateurs explicites : ";
    vector<int>::const_iterator itVec; // Déclaration explicite de l'itérateur
    for (itVec = vec.begin(); itVec != vec.end(); ++itVec) {
        cout << *itVec << " ";
    }
    cout << endl;
}

// Fonction pour afficher les éléments d'une std::list avec une boucle range-based
void afficher_list(const list<int>& lst) {
    cout << "Contenu de la list : ";
    for (int x : lst) {
        cout << x << " ";
    }
    cout << endl;
}

// Fonction pour afficher les éléments d'une std::list avec des itérateurs explicites
void afficher_list_avec_iterateurs(const list<int>& lst) {
    cout << "Contenu de la list avec itérateurs explicites : ";
    list<int>::const_iterator itLst; // Déclaration explicite de l'itérateur
    for (itLst = lst.begin(); itLst != lst.end(); ++itLst) {
        cout << *itLst << " ";
    }
    cout << endl;
}


int main()
{

// Vector
    std::vector<int> V1 = {1, 5, 30, 2, 4};
    std::list<int> lst1={0 ,100, 60, 30, 450, 50};

// 1. Triez un std::vector d’entiers dans l’ordre croissant.
    // Tri du vector dans l'ordre croissant
    afficher_vector_avec_iterateurs(V1);
    sort(begin(V1), V1.end());
    afficher_vector_avec_iterateurs(V1);

// 2. Inversez les éléments d’une std::list en utilisant la STL.
    afficher_list(lst1);
    lst1.reverse();
    afficher_list(lst1);
    // ## Question 6 : Algorithmes avec et sans STL
    vector<int>::iterator itV1 = V1.begin();
    for (itV1; itV1 != V1.end(); itV1++)
    {
        *itV1 = *itV1 * 2;
    }



    // 1. Sans STL : Doublez les valeurs d’un std::vector manuellement (parcours classique avec une boucle for ou while).

    // 2. Avec STL : Doublez les valeurs d’un std::vector en utilisant std::for_each et une fonction lambda.+
// lambda avec une fonction
    auto mulitplie = [](int &x) -> int { return x *= 2; };
    for_each(begin(V1), V1.end(), mulitplie);
// lambda avec calcul direct  [](int a, int b) -> int { return a + b; };
// [capture](paramètres) -> type_retour { corps }
    for_each(begin(V1), V1.end(), [](int &x) ->int { return x *= 2; });
    afficher_vector_avec_iterateurs(V1);

    // 3. Sans STL : Comptez les éléments supérieurs à 10 dans une std::list manuellement (parcours classique avec une boucle).

    // 4. Avec STL : Comptez les éléments supérieurs à 10 dans une std::list en utilisant std::count_if avec une fonction lambda.
    auto countSup10 = [](int x) -> bool { return x > 10; };
    int count=count_if(V1.begin(), V1.end(), countSup10);
    return 0;
}
