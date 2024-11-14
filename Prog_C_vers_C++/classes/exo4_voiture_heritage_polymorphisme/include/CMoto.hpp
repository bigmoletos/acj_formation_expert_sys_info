#ifndef CMOTO_HPP
#define CMOTO_HPP

#include "CVehicule.hpp"
#include <string>

class CMoto : public CVehicule {
public:
    CMoto(const std::string& modele); // Constructeur avec modèle
    //destructeur
    ~CMoto();

    void afficher() const override;

private:
    std::string modele;
};

#endif
