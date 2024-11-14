
#ifndef CMOTO_HPP
#define CMOTO_HPP

#include "CVehicule.hpp"

class CMoto :
public CVehicule {
public:
    ~CMoto();
    void afficher() const override; // Redéfinition de la méthode afficher()
};

#endif
