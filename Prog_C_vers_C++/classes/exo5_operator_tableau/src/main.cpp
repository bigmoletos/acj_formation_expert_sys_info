#include <iostream>
#include "IntArray.h" // Inclure l'en-tête de la classe IntArray


int main()
{
    // Création d'un tableau avec le constructeur par défaut
    IntArray arr1;
    std::cout << "arr1 (constructeur par défaut): " << arr1 << std::endl;

    // Création d'un tableau avec le constructeur paramétré
    IntArray arr2(5);
    std::cout << "arr2 (constructeur paramétré): " << arr2 << std::endl;

    // Remplissage de arr2 via l'opérateur >>
    std::cin >> arr2;
    std::cout << "arr2 après saisie: " << arr2 << std::endl;

    // Modification des éléments via l'opérateur []
    for (int i = 0; i < arr2.getSize(); ++i)
    {
        arr2[i] += i;
    }
    std::cout << "arr2 après modification: " << arr2 << std::endl;

    // Utilisation du constructeur de copie
    IntArray arr3 = arr2;
    std::cout << "arr3 (copie de arr2): " << arr3 << std::endl;

    // Modification de arr3 pour vérifier l'indépendance des instances
    arr3[0] = 100;
    std::cout << "arr3 après modification: " << arr3 << std::endl;
    std::cout << "arr2 pour vérifier qu'elle n'est pas affectée: " << arr2 << std::endl;

    // Test de l'opérateur d'assignation
    IntArray arr4;
    arr4 = arr2;
    std::cout << "arr4 (assignée à arr2): " << arr4 << std::endl;

    // Test de l'opérateur +
    IntArray arr5 = arr2 + arr4;
    std::cout << "arr5 (arr2 + arr4): " << arr5 << std::endl;

    // Test des opérateurs de comparaison
    std::cout << "arr2 == arr4: " << (arr2 == arr4 ? "Vrai" : "Faux") << std::endl;
    std::cout << "arr2 != arr3: " << (arr2 != arr3 ? "Vrai" : "Faux") << std::endl;

    // Test de l'accès à un indice invalide
    std::cout << "Accès à arr2[10]: " << arr2[10] << std::endl;

    // Test de l'addition de tableaux de tailles différentes
    IntArray arr6(3);
    IntArray arr7 = arr2 + arr6; // Affiche une erreur et retourne une copie de arr2
    std::cout << "arr7 (arr2 + arr6): " << arr7 << std::endl;

    return 0;
}