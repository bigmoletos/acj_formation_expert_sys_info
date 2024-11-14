#include "CVehicule.hpp"


CVehicule::CVehicule(const std::string& type) : type(type) {}


// Implémentation du destructeur
CVehicule::~CVehicule() {
    printf("Destruction de CVehicule: %s\n", type.c_str());
}


// Implémentation de la méthode afficher()
void CVehicule::afficher() const {
    printf("==================================\nJe suis un véhicule: %s\n",type.c_str());
}
