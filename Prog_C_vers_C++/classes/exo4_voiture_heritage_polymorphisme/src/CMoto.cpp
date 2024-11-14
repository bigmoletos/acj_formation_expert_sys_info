#include "CMoto.hpp"

CMoto::~CMoto() {
    printf("Destruction de CMoto\n");
}

void CMoto::afficher() const {
    printf("Je suis une moto.\n");
}
