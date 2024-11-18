#include <vector>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <algorithm> // pour std::sort
#include <iterator>
using namespace std;



// # Exo sur les Lambdas
// A. Vérifier si un nombre est négatif dans une liste
// B. Tri par valeur absolue
// ## Étape 1 : Définition et Utilisation Simple
// 1. Déclarez une lambda qui affiche `"Bonjour tout le monde !"`.
// 2. Déclarez une lambda qui prend deux entiers en paramètres et retourne leur produit.
// 3. Testez les deux lambdas en les appelant depuis votre fonction `main`.
// ## Étape 2 : Utilisation avec les Conteneurs
// 1. Créez un `std::vector` contenant les entiers de 1 à 10.
// 2. Utilisez `std::for_each` et une lambda pour afficher chaque élément du vector.
// 3. Modifiez chaque élément du vector en le multipliant par 3 à l’aide d’une lambda.
// ## Étape 3 : Captures dans une Lambda
// 1. Déclarez une variable `factor` et affectez-lui la valeur `4`.
// 2. Créez une lambda qui capture `factor` par **valeur** et retourne le produit d’un entier donné avec `factor`.
// 3. Modifiez la valeur de `factor` après la déclaration de la lambda et vérifiez si la valeur utilisée par la lambda change.
// ## Étape 4 : Captures par Référence
// 1. Déclarez une variable `factor` et affectez-lui la valeur `4`.
// 2. Créez une lambda qui capture `factor` par **référence** et retourne le produit d’un entier donné avec `factor`.
// 3. Modifiez la valeur de `factor` après la déclaration de la lambda et observez si la valeur utilisée par la lambda change.
// ## Étape 5 : Captures Générales
// 1. Déclarez deux variables `x` et `y` initialisées à 3 et 5 respectivement.
// 2. Créez une lambda qui capture **toutes les variables** par valeur et retourne leur somme.
// 3. Créez une autre lambda qui capture **toutes les variables** par référence et modifie leur valeur.
// ## Étape 6 : Utilisation Avancée avec la STL
// 1. Créez un `std::vector` contenant les entiers de 1 à 10.
// 2. Utilisez une lambda avec `std::find_if` pour trouver le premier élément supérieur à 5.
// 3. Utilisez une lambda avec `std::count_if` pour compter les éléments pairs.
// ## Étape 7 : Lambdas avec `std::function`
// 1. Déclarez une `std::function` qui encapsule une lambda pour calculer la différence entre deux entiers.
// 2. Changez dynamiquement la fonction pour encapsuler une lambda qui calcule le produit.
// ## Étape 8 : Lambdas Génériques
// 1. Créez une lambda générique qui retourne le maximum entre deux valeurs.
// 2. Testez votre lambda avec des types différents (`int`, `double`, etc.).

void splitSentence(const int& sentence, const char splitCar){

}

int main()
{
// A. Vérifier si un nombre est négatif dans une liste
list<int> lst{2,5,-9, -2,80,4};

auto isNegatif = [](const int &x) -> void{ if (x < 0){printf("\nLe chiffre %d est negatif\n", x); } };

for_each(begin(lst), end(lst), isNegatif);


// B. Tri par valeur absolue
std::vector<int> v2 = {-1, -2, 3, -4, 5};
std::vector<int> abs_values(v2.size());

// Appliquer std::abs à chaque élément de v
std::transform(v2.begin(), v2.end(), abs_values.begin(), [](auto x) { return std::abs(x); });

for (auto n : abs_values) {
    std::cout << n << " "; // 1 2 3 4 5
}

// ## Étape 1 : Définition et Utilisation Simple
// 1. Déclarez une lambda qui affiche `"Bonjour tout le monde !"`.
auto bonjour = []{return printf("\nHello les nouilles !\n"); };
// 2. Déclarez une lambda qui prend deux entiers en paramètres et retourne leur produit.
auto produitInt = [](const int a, const int b) -> int { return a * b; };
// 3. Testez les deux lambdas en les appelant depuis votre fonction `main`.
bonjour();
printf("resultat: %d", produitInt(50,63));

// ## Étape 2 : Utilisation avec les Conteneurs
// 1. Créez un `std::vector` contenant les entiers de 1 à 10.
std::vector<int> v3 = {1, 2, 3, 4, 5,6,7,8,9,10};
// 2. Utilisez `std::for_each` et une lambda pour afficher chaque élément du vector.
std::for_each
// 3. Modifiez chaque élément du vector en le multipliant par 3 à l’aide d’une lambda.

// ## Étape 3 : Captures dans une Lambda
// 1. Déclarez une variable `factor` et affectez-lui la valeur `4`.

// 2. Créez une lambda qui capture `factor` par **valeur** et retourne le produit d’un entier donné avec `factor`.

// 3. Modifiez la valeur de `factor` après la déclaration de la lambda et vérifiez si la valeur utilisée par la lambda change.

// ## Étape 4 : Captures par Référence
// 1. Déclarez une variable `factor` et affectez-lui la valeur `4`.

// 2. Créez une lambda qui capture `factor` par **référence** et retourne le produit d’un entier donné avec `factor`.

// 3. Modifiez la valeur de `factor` après la déclaration de la lambda et observez si la valeur utilisée par la lambda change.

// ## Étape 5 : Captures Générales
// 1. Déclarez deux variables `x` et `y` initialisées à 3 et 5 respectivement.

// 2. Créez une lambda qui capture **toutes les variables** par valeur et retourne leur somme.

// 3. Créez une autre lambda qui capture **toutes les variables** par référence et modifie leur valeur.

// ## Étape 6 : Utilisation Avancée avec la STL
// 1. Créez un `std::vector` contenant les entiers de 1 à 10.

// 2. Utilisez une lambda avec `std::find_if` pour trouver le premier élément supérieur à 5.

// 3. Utilisez une lambda avec `std::count_if` pour compter les éléments pairs.

// ## Étape 7 : Lambdas avec `std::function`
// 1. Déclarez une `std::function` qui encapsule une lambda pour calculer la différence entre deux entiers.

// 2. Changez dynamiquement la fonction pour encapsuler une lambda qui calcule le produit.

// ## Étape 8 : Lambdas Génériques
// 1. Créez une lambda générique qui retourne le maximum entre deux valeurs.

// 2. Testez votre lambda avec des types différents (`int`, `double`, etc.).

return 0;
}
