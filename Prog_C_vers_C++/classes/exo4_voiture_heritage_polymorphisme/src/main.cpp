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

    // Partie 3 : Tableau de CVehicule avec un
    std::vector<CVehicule*> tableauVehicules; //declaration d'un vecteur de pointeurs stockant les objets de type Vehicule
    //ajout dse elelments
    tableauVehicules.push_back(new CVehicule());
    tableauVehicules.push_back(new CMoto());
    tableauVehicules.push_back(new CVoiture());
// affichage des elements
    for (auto vehicule : tableauVehicules) {
        vehicule->afficher();
    }
//pour eviter la fuite memoire il faut supprimer chaque new
    // Partie 4 : Gestion de la Mémoire et Destructeurs
    for (auto vehicule : tableauVehicules) {
        printf(" destruction des pointeurs crées : %p\n", (void*)vehicule);
        delete vehicule; // Libération de la mémoire
    }

    return 0;
}
