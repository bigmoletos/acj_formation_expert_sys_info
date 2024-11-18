#include <vector>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <algorithm> // pour std::sort
#include <iterator>
#include <cstdio> // pour printf
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

// Fonction pour afficher les éléments d'un std::vector avec une boucle range-based
void afficher_vector(const vector<int> &vec)
{
    cout << "Contenu du vector : ";
    for (int x : vec)
    {
        cout << x << " ";
    }
    cout << endl;
}

// Fonction pour afficher les éléments d'un std::vector avec des itérateurs explicites
void afficher_vector_avec_iterateurs(const vector<int> &vec)
{
    cout << "Contenu du vector avec itérateurs explicites : ";
    vector<int>::const_iterator itVec; // Déclaration explicite de l'itérateur
    for (itVec = vec.begin(); itVec != vec.end(); ++itVec)
    {
        cout << *itVec << " ";
    }
    cout << endl;
}

// Fonction pour afficher les éléments d'une std::list avec une boucle range-based
void afficher_list(const list<int> &lst)
{
    cout << "Contenu de la list : ";
    for (int x : lst)
    {
        cout << x << " ";
    }
    cout << endl;
}

// Fonction pour afficher les éléments d'une std::list avec des itérateurs explicites
void afficher_list_avec_iterateurs(const list<int> &lst)
{
    cout << "Contenu de la list avec itérateurs explicites : ";
    list<int>::const_iterator itLst; // Déclaration explicite de l'itérateur
    for (itLst = lst.begin(); itLst != lst.end(); ++itLst)
    {
        cout << *itLst << " ";
    }
    cout << endl;
}

int main()
{
    // A. Vérifier si un nombre est négatif dans une liste
    list<int> lst{2, 5, -9, -2, 80, 4};
    cout << "============Vérifier si un nombre est négatif dans une liste====================" << endl;

    auto isNegatif = [](const int &x) -> void
    { if (x < 0){printf("\nLe chiffre %d est negatif\n", x); } };

    for_each(begin(lst), end(lst), isNegatif);
    cout << "" << endl;

    // B. Tri par valeur absolue
    std::vector<int> v2 = {-1, -2, 3, -4, 5};
    std::vector<int> abs_values(v2.size());

    cout << "==========Tri par valeur absolue======================" << endl;
    // Appliquer std::abs à chaque élément de v
    std::transform(v2.begin(), v2.end(), abs_values.begin(), [](auto x)
                   { return std::abs(x); });

    for (auto n : abs_values)
    {
        std::cout << n << " "; // 1 2 3 4 5
    }
    cout << "" << endl;
    cout << "=============Appliquer std::abs à chaque élément de v===================" << endl;

    // ## Étape 1 : Définition et Utilisation Simple
    // 1. Déclarez une lambda qui affiche `"Bonjour tout le monde !"`.
    auto bonjour = []
    { return printf("\nHello les nouilles !\n"); };
    // 2. Déclarez une lambda qui prend deux entiers en paramètres et retourne leur produit.
    auto produitInt = [](const int a, const int b) -> int
    { return a * b; };
    // 3. Testez les deux lambdas en les appelant depuis votre fonction `main`.
    cout << "==========Déclarez une lambda qui affiche  Bonjour tout le monde == " << endl;
    bonjour();
    cout << "=========Déclarez une lambda qui prend deux entiers en paramètres et retourne leur produit========" << endl;
    printf("resultat: %d", produitInt(50, 63));

    cout << "" << endl;
    // ## Étape 2 : Utilisation avec les Conteneurs
    // 1. Créez un `std::vector` contenant les entiers de 1 à 10.
    cout << "============Créez un `std::vector` contenant les entiers de 1 à 10====================" << endl;
    std::vector<int> v3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // 2. Utilisez `std::for_each` et une lambda pour afficher chaque élément du vector.
    std::for_each(v3.begin(), v3.end(), [](const int x)
                  { printf(" %d ", x); });
    cout << "" << endl;
    // 3. Modifiez chaque élément du vector en le multipliant par 3 à l’aide d’une lambda.
    cout << "=======Modifiez chaque élément du vector en le multipliant par 3 à l’aide d’une lambda==" << endl;
    std::for_each(v3.begin(), v3.end(), [](int &x)
                  { x *= 3; });
    std::for_each(v3.begin(), v3.end(), [](const int x)
                  { printf(" %d ", x); });

    cout << "" << endl;
    // ## Étape 3 : Captures dans une Lambda
    // 1. Déclarez une variable `factor` et affectez-lui la valeur `4`.
    cout << "=========Déclarez une variable `factor` et affectez-lui la valeur `4`=======================" << endl;
    int factor{4};
    // 2. Créez une lambda qui capture `factor` par **valeur** et retourne le produit d’un entier donné avec `factor`.
    cout << "=====Créez une lambda qui capture `factor` par **valeur** et retourne le produit d’un entier donné avec `factor`======" << endl;
    auto produitByFactor = [=](const int x) -> int
    { return x * factor; };

    // 3. Modifiez la valeur de `factor` après la déclaration de la lambda et vérifiez si la valeur utilisée par la lambda change.
    cout << "===odifiez la valeur de `factor` après la déclaration de la lambda et \nvérifiez si la valeur utilisée par la lambda change=====" << endl;
    // Appel de la lambda avec différents entiers
    int result1 = produitByFactor(4);
    int result2 = produitByFactor(5);

    std::cout << "factor= " << factor << std::endl;
    cout << "Produit de 4 avec factor : " << result1 << endl; // Affiche 16
    cout << "Produit de 5 avec factor : " << result2 << endl; // Affiche20

    // ## Étape 4 : Captures par Référence
    // 1. Déclarez une variable `factor` et affectez-lui la valeur `4`.
    cout << "=====Déclarez une variable `factor` et affectez-lui la valeur `4`======" << endl;
    int factor2{4};
    std::cout << "factor2= " << factor2 << std::endl;
    // 2. Créez une lambda qui capture `factor` par **référence** et retourne le produit d’un entier donné avec `factor`.
    cout << "====Créez une lambda qui capture `factor` par **référence** et \nretourne le produit d’un entier donné avec `factor`.====" << endl;
    auto produitByFactorRef = [&](const int x) -> int
    { return x * factor2; };

    // Appel de la lambda avec différents entiers
    int result10 = produitByFactorRef(4);
    int result20 = produitByFactorRef(5);

    std::cout << "factor2= " << factor2 << std::endl;
    cout << "Produit de 4 avec factor2 : " << result10 << endl; // Affiche 16
    cout << "Produit de 5 avec factor2 : " << result20 << endl; // Affiche20

    // 3. Modifiez la valeur de `factor` après la déclaration de la lambda et observez si la valeur utilisée par la lambda change.
    cout << "===== Modifiez la valeur de `factor` après la déclaration \nde la lambda et observez si la valeur utilisée par la lambda change=============" << endl;
    factor2 = 20;
    std::cout << "factor2= " << factor2 << std::endl;
    std::cout << "factor2= " << factor2 << std::endl;
    cout << "Produit de 4 avec factor2 : " << result10 << endl; // Affiche 16
    cout << "Produit de 5 avec factor2 : " << result20 << endl; // Affiche20

    // ## Étape 5 : Captures Générales
    // 1. Déclarez deux variables `x` et `y` initialisées à 3 et 5 respectivement.
    cout << "======Déclarez deux variables `x` et `y` initialisées à 3 et 5 respectivement==============" << endl;
    int x{3};
    int y{5};

    // 2. Créez une lambda qui capture **toutes les variables** par valeur et retourne leur somme.
    cout << "=========Créez une lambda qui capture **toutes les variables** par valeur et retourne leur somme.=======" << endl;
    auto sommeByValeur = [=]() -> int
    { return x + y; };
    int res1 = sommeByValeur();
    std::cout << "res1= " << res1 << std::endl;

    // 3. Créez une autre lambda qui capture **toutes les variables** par référence et modifie leur valeur.
    cout
        << "=======Créez une autre lambda qui capture **toutes les variables** par référence et modifie leur valeur.=======" << endl;
    auto sommeByRef = [&]() -> int
    {
        x+=7;
        y += 5;
        return x + y; };
    int res10 = sommeByRef();
    std::cout << "res10= " << res10 << std::endl;
    cout << "Valeurs modifiées : x = " << x << ", y = " << y << endl; // x = 9, y = 15
    // ## Étape 6 : Utilisation Avancée avec la STL
    // 1. Créez un `std::vector` contenant les entiers de 1 à 10.
    cout << "=======Créez un `std::vector` contenant les entiers de 1 à 10.==========" << endl;
    std::vector<int> v4{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // 2. Utilisez une lambda avec `std::find_if` pour trouver le premier élément supérieur à 5.
    cout << "==========Utilisez une lambda avec `std::find_if` pour trouver le premier élément supérieur à 5.======" << endl;
    auto valSup5 = find_if(v4.begin(), v4.end(), [](int x)
                           { return x > 5; });
    if (valSup5 != v4.end())
    {
        cout << "Premier élément supérieur à 5 : " << *valSup5 << endl;
    }
    else
    {
        cout << "Aucun élément supérieur à 5 trouvé." << endl;
    }
    // 3. Utilisez une lambda avec `std::count_if` pour compter les éléments pairs.
    cout
        << "=====Utilisez une lambda avec `std::count_if` pour compter les éléments pairs=======" << endl;

    // ## Étape 7 : Lambdas avec `std::function`
    // 1. Déclarez une `std::function` qui encapsule une lambda pour calculer la différence entre deux entiers.
    cout << "======Déclarez une `std::function` qui encapsule une lambda pour calculer la différence entre deux entiers.=======" << endl;

    // 2. Changez dynamiquement la fonction pour encapsuler une lambda qui calcule le produit.
    cout << "================================" << endl;

    // ## Étape 8 : Lambdas Génériques
    // 1. Créez une lambda générique qui retourne le maximum entre deux valeurs.
    cout << "==========Créez une lambda générique qui retourne le maximum entre deux valeurs.=================" << endl;

    // 2. Testez votre lambda avec des types différents (`int`, `double`, etc.).
    cout << "=======Testez votre lambda avec des types différents (`int`, `double`, etc.).===================" << endl;

    return 0;
}
