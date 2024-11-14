#include "CVoiture.hpp"

CVoiture::~CVoiture() {
    printf("Destruction de CVoiture\n");
}

void CVoiture::afficher() const {
    printf("Je suis une voiture.\n");
}
