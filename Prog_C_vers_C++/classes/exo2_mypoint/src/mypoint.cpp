#include "mypoint.hpp"
#include <iostream>

// Constructeur par défaut
// MyPoint::MyPoint() : mX(0), mY(0) {}

// constructeur avec parametres
// MyPoint::MyPoint(double x, double y):mX(x),mY(y){}

//destructeur par defaut
MyPoint::~MyPoint(){}



// methode pour afficher les coordonnées
void MyPoint::afficher() const
{
    printf("Coordonnées de x: %f, y: %f",mX,mY);
}

// méthode pour saisir les coordonnées
void MyPoint::saisie()
{
    printf("Veuillez saisir X :");
    std::cin >> mX;
    printf("Veuillez saisir Y :");
    std::cin >> mY;

}

// Getters
double MyPoint::getX()  {
    return mX;
}

double MyPoint::getY()  {
    return mY;
}

// Setters (optionnel, si nécessaire)
void MyPoint::setX(double x) {
    mX = x;
}

void MyPoint::setY(double y) {
    mY = y;
}