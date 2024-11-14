
#include "mypoint.hpp"
#include "vecteur.hpp"
#include <iostream>

// La composition : Création et Utilisation des Classes MyPoint et Vecteur


// Partie 1 : Classe MyPoint
// Créer une classe MyPoint avec :

// Un constructeur par défaut et un destructeur.
// Deux membres privés : mX et mY de type double.
// Une méthode afficher() pour afficher les coordonnées du point.
// Une méthode saisie() pour saisir les coordonnées du point depuis la console.
// Un constructeur avec paramètres pour initialiser mX et mY.
// Partie 2 : Classe Vecteur
// Créer une classe MyVecteur pour démontrer la composition. Cette classe contiendra :

// Deux membres de type MyPoint : mOrigine et mDestination.
// Une méthode afficher() pour afficher les détails du vecteur.
// Une méthode longueur() pour calculer la longueur du vecteur.
// Une méthode angle() pour calculer l'angle du vecteur (optionnellement en degrés ou radians).
// Partie 3 : Utilisation dans le main
// Dans la fonction main, créez des instances de MyPoint et de MyVecteur et utilisez les méthodes définies pour manipuler ces objets.

// Note : Pour la méthode angle(), vous pouvez choisir de calculer l'angle par rapport à l'axe horizontal ou tout autre axe pertinent.




int main()
{
    /// Création de deux points
    MyPoint origineX;
    MyPoint destinationY;

    printf("Veuillez saisir le poitn X :");
    origineX.saisie();
    printf("Veuillez saisir le poitn Y :");
    destinationY.saisie();


    // Création d'un vecteur avec les points d'origine et de destination
    MyVecteur vecteur(origineX, destinationY);

    // Affichage des détails du vecteur
    printf("\nDétails du vecteur :\n");
    printf("Origine : (%.2f, %.2f)\n", origineX.getX(), origineX.getY());
    printf("Destination : (%.2f, %.2f)\n", destinationY.getX(), destinationY.getY());

    // Calcul et affichage de la longueur du vecteur
    printf("Longueur du vecteur : %.2f\n", vecteur.longueur());

    // Calcul et affichage de l'angle du vecteur en radians
    printf("Angle du vecteur (en radians) : %.2f\n", vecteur.angle());



    return 0;
}
