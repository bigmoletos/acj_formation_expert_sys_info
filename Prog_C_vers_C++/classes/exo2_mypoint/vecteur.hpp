#ifndef MYVECTEUR_HPP
#define MYVECTEUR_HPP

#include "mypoint.hpp"
#include <cmath>
#include <iostream>

class MyVecteur {
private:
    MyPoint mOrigine;
    MyPoint mDestination;

public:
    // Constructeur par défaut
    MyVecteur();

    // Constructeur avec paramètres
    MyVecteur(const MyPoint& origine, const MyPoint& destination);

    // Destructeur
    ~MyVecteur();

    // Méthode pour afficher les détails du vecteur
    void afficher() const;

    // Méthode pour calculer la longueur du vecteur
    double longueur() const;

    // Méthode pour calculer l'angle du vecteur (en radians)
    double angle() const;
};

#endif // MYVECTEUR_HPP
