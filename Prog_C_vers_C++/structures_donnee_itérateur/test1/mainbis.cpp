#include <iostream>
// #include "comptebancaire.h"
// #include "voiture.h"
// #include "mypoint.h"
//#include "myvecteur.h"
// #include "tableaudynamique.h"
// #incl:ude "intarray.h"
#include "containers.h"

#include <vector>
using namespace std;

template <typename T>
class Boite
{
private:
    T contenu;
public:
    Boite(T c)
    {
        contenu = c;
    }
    T obtenir()
    {
        return contenu;
    }
};

// void fctIntArray()
// {
//     IntArray arr1;
//     std::cout << "arr1 (constructeur par défaut): " << arr1 << std::endl;

//     // Création d'un tableau avec le constructeur paramétré
//     IntArray arr2(5);
//     std::cout << "arr2 (constructeur paramétré): " << arr2 << std::endl;
// }

int main()
{
    // Utilisation d'un std::vector
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    //std::vector<int>
    auto it = v1.begin();
    for (auto it = v1.begin(); it != v1.end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << std::endl;

    // Utilisation de CoordsGPS
    CoordsGPS p1(3.6, 4.7), p2;
    std::cout << "p1 vaut : ";
    p1.afficher();
    std::cout << "p2 vaut : ";
    p2.afficher();

    std::cout << "saisi p1 : ";
    p1.saisie();
    std::cout << "p1 vaut : ";
    p1.afficher();

    return 0;
}