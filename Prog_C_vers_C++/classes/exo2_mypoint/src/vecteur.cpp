#include "vecteur.hpp"
#include <cmath>
#include <iostream>

// Constructeur par défaut
MyVecteur::MyVecteur() : mOrigine(MyPoint()), mDestination(MyPoint()) {}

// Constructeur avec paramètres
MyVecteur::MyVecteur(const MyPoint& origine, const MyPoint& destination)
    : mOrigine(origine), mDestination(destination) {}

// Destructeur
MyVecteur::~MyVecteur() {}

// Méthode pour afficher les détails du vecteur
void MyVecteur::afficher() const {
    std::cout << "Vecteur : Origine ";
    mOrigine.afficher();
    std::cout << "           Destination ";
    mDestination.afficher();
}

// Méthode pour calculer la longueur du vecteur
double MyVecteur::longueur() const {
    double dx = mDestination.getX() - mOrigine.getX();
    double dy = mDestination.getY() - mOrigine.getY();
    return std::sqrt(dx * dx + dy * dy);
}

// Méthode pour calculer l'angle du vecteur (en radians)
double MyVecteur::angle() const {
    double dx = mDestination.getX() - mOrigine.getX();
    double dy = mDestination.getY() - mOrigine.getY();
    return std::atan2(dy, dx); // Angle en radians par rapport à l'axe horizontal
}

inline void MyPoint::setX(double newX) {
    mX = newX;
}
inline void MyPoint::setY(double newY) {
    mY = newY;
}
inline void MyPoint::setXY(double newX, double newY) {
    mX = newX;

    mY = newY;
}