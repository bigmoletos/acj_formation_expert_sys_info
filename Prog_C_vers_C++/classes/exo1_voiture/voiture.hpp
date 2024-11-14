#ifndef VOITURE_H
#define VOITURE_H

#include <string>
#include "first_classe.hpp"


class Voiture
{
private:
    std::string marque;
    std::string modele;
    int annee;
    CompteBancaire *cb;

public:
    // Constructeur par défaut sans parametres mais avec initialisation des attributs avec des valeurs par défaut
    Voiture():marque("immonde"), modele("impensable"), annee(007){}

    // Constructeur avec paramètres
    Voiture(const std::string& marque, const std::string& modele, int annee);
//  destructeur
    ~Voiture();

    void obtenirParameter(const std::string& marque, const std::string& modele, int annee);


        // Setters
    void setMarque(const std::string& marque);
    void setModele(const std::string& modele);
    void setAnnee(int annee);

    // Getters
    std::string getMarque() const;
    std::string getModele() const;
    int getAnnee() const;
};

#endif