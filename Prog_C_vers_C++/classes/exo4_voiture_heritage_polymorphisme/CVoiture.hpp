#ifndef CVOITURE_HPP
#define CVOITURE_HPP

#include "CVehicule.hpp"

class CVoiture :
public CVehicule {
public:
    ~CVoiture();
    void afficher() const override; // Redéfinition de la méthode afficher()
};

#endif

