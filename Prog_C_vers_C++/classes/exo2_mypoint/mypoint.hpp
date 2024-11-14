#ifndef MYPOINT_H
#define MYPOINT_H
#include <string>
#include <iostream>

class MyPoint
{
private:
    double mX;
    double mY;

public:
//constructeur par defaut
    MyPoint():mX(0), mY(0) {}
    //  constructeur avec parametres
    MyPoint(double x, double y):mX(0), mY(0) {}

    //destructeur
    ~MyPoint(){}

// methode pour afficher les coordonnées
    void afficher() const;

    // méthode pour saisir les coordonnées
    void saisie();
//getter
    double getX();
    double getY();
       // Setters (optionnel, si nécessaire)
    void setX(double x);
    void setY(double y);

    void setXY(double newX, double newY);
};

#endif // MYPOINT_H