#include "CVehicule.hpp"

// Implémentation du destructeur
CVehicule::~CVehicule() {
    printf("Destruction de CVehicule\n");
}

// Implémentation de la méthode afficher()
void CVehicule::afficher() const {
    printf("Je suis un véhicule.\n");
}
