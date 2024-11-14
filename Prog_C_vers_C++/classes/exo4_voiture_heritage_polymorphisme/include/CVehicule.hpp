#ifndef CVEHICULE_HPP
#define CVEHICULE_HPP

#include <iostream>
#include <string>

class CVehicule {
public:
    CVehicule(const std::string& type = "Inconnu"); // Constructeur avec paramètre
    virtual ~CVehicule(); // Destructeur virtuel pour assurer la bonne destruction
    virtual void afficher() const; // Méthode virtuelle pour affichage

protected:
std::string type;
};

#endif

