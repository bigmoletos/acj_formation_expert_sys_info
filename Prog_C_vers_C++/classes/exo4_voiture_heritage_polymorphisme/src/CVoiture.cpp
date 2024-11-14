#include "CVoiture.hpp"
#include <iostream>


CVoiture::CVoiture(const std::string& modele) : modele(modele) {
    // Initialisation du modèle dans le constructeur
}
CVoiture::~CVoiture() {
    printf("--------------\nDestruction de CVoiture:  %s\n",modele.c_str());
}

void CVoiture::afficher() const {
    printf("--------------\nJe suis une voiture: %s\n",modele.c_str());
}

