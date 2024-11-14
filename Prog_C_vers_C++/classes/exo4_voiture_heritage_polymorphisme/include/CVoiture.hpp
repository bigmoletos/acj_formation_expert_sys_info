#ifndef CVOITURE_HPP
#define CVOITURE_HPP

#include "CVehicule.hpp"
#include <string>

class CVoiture : public CVehicule {
public:
    CVoiture(const std::string& modele); // Constructeur avec modèle
    virtual ~CVoiture();
    void afficher() const override;

private:
    std::string modele;
};

#endif
