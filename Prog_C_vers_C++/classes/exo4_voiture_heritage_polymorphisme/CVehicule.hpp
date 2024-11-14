#ifndef CVEHICULE_HPP
#define CVEHICULE_HPP

#include <iostream>
#include <string>

class CVehicule {
public:
    virtual ~CVehicule(); // Destructeur virtuel pour assurer la bonne destruction
    virtual void afficher() const; // Méthode virtuelle pour affichage
};

#endif

