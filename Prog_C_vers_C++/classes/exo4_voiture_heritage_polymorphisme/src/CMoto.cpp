#include "CMoto.hpp"
#include <iostream>


CMoto::CMoto(const std::string& modele) : modele(modele) {
    // Initialisation du modèle dans le constructeur
}


CMoto::~CMoto() {
    printf("Destruction de CMoto %s\n",modele.c_str());
}

void CMoto::afficher() const {
    printf("Je suis une moto.%s\n", modele.c_str());
}
