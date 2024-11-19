#ifndef __TAB__
#define __TAB__

#include <string>
#include <iostream>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage

class ConstruireTableau
{
public:
    // constructeur
    ConstruireTableau(std::string name, int taille);
    // getter
    std::string getName() const;
    // setter
    void setName(std::string name);
    // getter
    int getTaille() const;
    // setter
    void setTaille(int taille);

private:
    std::string name;
    int taille;
};

// Implementation des methodes de la classe ConstruireTableau
ConstruireTableau::ConstruireTableau(std::string name, int taille) : name(name), taille(taille) {}

// getter
std::string ConstruireTableau::getName() const
{
    return name;
}

// setter
void ConstruireTableau::setName(std::string name)
{
    this->name = name;
}

// getter
int ConstruireTableau::getTaille() const
{
    return taille;
}

// setter
void ConstruireTableau::setTaille(int taille)
{
    this->taille = taille;
}

// -------Fonctions pour mesurer le temps
void chrono_start(std::chrono::high_resolution_clock::time_point &t1)
{
    t1 = std::chrono::high_resolution_clock::now();
}

void chrono_end(const std::chrono::high_resolution_clock::time_point &t1, const std::string &message)
{
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << message << ": " << duration << " ms" << std::endl;
}

// -------Fonctions pour charger les fichiers
void charger_donnees_fichier(const std::string &nom_fichier, std::vector<int> &tableau);

// -------Fonctions pour construire un tableau vector
void generer_valeurs_aleatoires(std::array<int, 100> &tableau);

#endif // __TAB__
