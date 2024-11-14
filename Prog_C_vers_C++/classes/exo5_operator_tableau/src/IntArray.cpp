#include "IntArray.h"
#include <cstdio>  // pour printf
// #include <iostream>
#include <stdexcept>

// Fonction auxiliaire pour afficher un tableau
void afficherTableau(const char* nom, const IntArray& array) {
    printf("%s (taille: %d) = [", nom, array.getSize());
    for (int i = 0; i < array.getSize(); ++i) {
        printf("%d", array.data[i]);
        if (i < array.getSize() - 1) printf(", ");
    }
    printf("]\n");
}

// Constructeur par défaut
IntArray::IntArray() : data(nullptr), size(0) {
    printf("Constructeur par défaut appelé pour IntArray\n");
    afficherTableau("IntArray", *this);
}

// Constructeur paramétré
IntArray::IntArray(int size) : size(size) {
    data = new int[size](); // Alloue et initialise à zéro
    printf("Constructeur paramétré appelé pour IntArray de taille %d\n", size);
    afficherTableau("IntArray", *this);
}

// Constructeur de copie
IntArray::IntArray(const IntArray& other) : size(other.size) {
    data = new int[size];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
    printf("Constructeur de copie appelé pour IntArray\n");
    afficherTableau("Copie de IntArray", *this);
}

// Destructeur
IntArray::~IntArray() {
    printf("Destructeur appelé pour IntArray\n");
    afficherTableau("IntArray", *this);
    delete[] data;
}

// Opérateur d'assignation
IntArray& IntArray::operator=(const IntArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    printf("Opérateur d'assignation appelé pour IntArray\n");
    afficherTableau("IntArray", *this);
    return *this;
}

// Accès aux éléments avec vérification de l'indice
int& IntArray::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index hors limites");
    }
    printf("Accès à l'élément %d de IntArray\n", index);
    return data[index];
}

// Opérateur +
IntArray IntArray::operator+(const IntArray& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Les tableaux ont des tailles différentes");
    }
    IntArray result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    printf("Opérateur + appelé pour additionner deux IntArray\n");
    afficherTableau("Résultat de l'addition", result);
    return result;
}

// Opérateur de comparaison ==
bool IntArray::operator==(const IntArray& other) const {
    if (size != other.size) return false;
    for (int i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    printf("Opérateur == appelé : les tableaux sont égaux\n");
    return true;
}

// Opérateur de comparaison !=
bool IntArray::operator!=(const IntArray& other) const {
    printf("Opérateur != appelé : les tableaux sont différents\n");
    return !(*this == other);
}

// Opérateur de flux <<
std::ostream& operator<<(std::ostream& os, const IntArray& array) {
    os << "[";
    for (int i = 0; i < array.size; ++i) {
        os << array.data[i];
        if (i < array.size - 1) os << ", ";
    }
    os << "]";
    return os;
}

// Opérateur de flux >>
std::istream& operator>>(std::istream& is, IntArray& array) {
    printf("Saisie des valeurs pour IntArray (taille %d)\n", array.size);
    for (int i = 0; i < array.size; ++i) {
        is >> array.data[i];
    }
    afficherTableau("IntArray après saisie", array);
    return is;
}

// Méthode pour obtenir la taille
int IntArray::getSize() const {
    return size;
}
