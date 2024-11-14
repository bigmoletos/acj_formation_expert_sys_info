#include <iostream>
#include "voiture.hpp"
#include "first_classe.hpp"


// Définissez une classe Voiture en C++ qui a trois attributs
// privés : marque, modele et annee.
// Ajoutez des méthodes publiques pour définir et obtenir la valeur de ces attributs.


int main()
{
    // Utilisation du constructeur par défaut
    Voiture toyota;
    std::cout << "toyota - Marque: " << toyota.getMarque()
              << ", Modele: " << toyota.getModele()
              << ", Annee: " << toyota.getAnnee() << std::endl;

    // Utilisation du constructeur avec paramètres
    Voiture volvo("Volvo", "Corolla", 2020);
    std::cout << "Volvo  - Marque: " << volvo.getMarque()
              << ", Modele: " << volvo.getModele()
              << ", Annee: " << volvo.getAnnee() << std::endl;

    // Modification des attributs de voiture1
    toyota.setMarque("Renault");
    volvo.setModele("Clio");
    toyota.setAnnee(2015);

    std::cout << "Voiture 1 (apres modification) - Marque: " << toyota.getMarque()
              << ", Modele: " << toyota.getModele()
              << ", Annee: " << toyota.getAnnee() << std::endl;

    return 0;
}