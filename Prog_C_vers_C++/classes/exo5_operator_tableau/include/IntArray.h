#ifndef INTARRAY_H
#define INTARRAY_H

#include <iostream>
#include <stdexcept>

class IntArray {
private:
    int* data;         // Pointeur vers le tableau dynamique
    int size;          // Taille du tableau

public:
    // Constructeur par défaut
    IntArray();

    // Constructeur paramétré
    explicit IntArray(int size);

    // Constructeur de copie
    IntArray(const IntArray& other);

    // Destructeur
    virtual ~IntArray();

    // --------------------------SURCHARGE DES OPERATEURS---------------------

    // Permet d'assigner un IntArray à un autre (par exemple, arr1 = arr2;). Il vérifie que l'instance assignée n'est pas la même que l'instance courante (vérification this != &other). Il effectue également une copie en profondeur.
    // IntArray& operator=(const IntArray& other);

    // // Accès aux éléments avec gestion des limites
    // int& operator[](int index);

    // -------------------------- OPERATEURS + ---------------------
    // // Surcharge de l'opérateur +
    IntArray operator+(const IntArray& other) const;

    // -------------------------- OPERATEURS ++ ET §+ ---------------------
    // Opérateurs de comparaison
    bool operator==(const IntArray& other) const;
    bool operator!=(const IntArray& other) const;

    // -------------------------- OPERATEURS DE FLUX    ---------------------
    // Opérateur de flux pour la sortie
    // Fonction afficherTableau : Une fonction amie qui n'est pas membre de la classe mais qui a accès à ses membres privés. Elle est utilisée pour afficher les éléments d'un IntArray avec printf.
    friend std::ostream& operator<<(std::ostream& os, const IntArray& array);

    // Opérateur de flux pour l'entrée
    friend std::istream& operator>>(std::istream& is, IntArray& array);

    // -------------------------- fFIN SURCHARGE DES OPERATEURS    ---------------------

    // Méthode pour obtenir la taille du tableau
    int getSize() const;

    // Fonction amie pour afficher le tableau
    friend void afficherTableau(const char* nom, const IntArray& array);
};

#endif // INTARRAY_H
