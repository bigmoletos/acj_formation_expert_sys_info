#include "CVehicule.hpp"
#include "CMoto.hpp"
#include "CVoiture.hpp"
#include <vector>

int main() {
    //Cration du tableau pour y stocker les vehicules
    // Partie 2 : Test dans le Main
    CVehicule* vehicules[] = { new CVehicule(), new CMoto(), new CVoiture() };
    for (auto vehicule : vehicules) {
        vehicule->afficher();
    }

    // Partie 3 : Tableau de CVehicule
    std::vector<CVehicule*> tableauVehicules;
    tableauVehicules.push_back(new CVehicule());
    tableauVehicules.push_back(new CMoto());
    tableauVehicules.push_back(new CVoiture());

    for (auto vehicule : tableauVehicules) {
        vehicule->afficher();
    }

    // Partie 4 : Gestion de la Mémoire et Destructeurs
    for (auto vehicule : tableauVehicules) {
        delete vehicule; // Libération de la mémoire
    }

    return 0;
}
