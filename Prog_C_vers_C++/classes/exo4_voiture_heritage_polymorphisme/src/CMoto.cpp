#include "CMoto.hpp"
#include <iostream>


CMoto::CMoto(const std::string& modele) : modele(modele) {
    // Initialisation du modèle dans le constructeur
}


CMoto::~CMoto() {
    printf("--------------\nDestruction de CMoto:  %s\n",modele.c_str());
}

void CMoto::afficher() const {
    printf("--------------\nJe suis une moto: %s\n", modele.c_str());
}
