#ifndef __OCCURRENCE__
#define __OCCURRENCE__

#include <string>
#include <iostream>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage
#include <unordered_map>



// -------Fonctions nombre d'occurences-------------
class NombreOccurrence
{
public:
    // Constructeur qui prend les lignes d'un fichier d'historique en entrée
    NombreOccurrence(const std::vector<std::string> &lignes);

    // Méthode pour calculer les occurrences des commandes
    void calculerOccurrences();

    // Méthode pour afficher les commandes et leur nombre d'occurrences, triées par ordre décroissant
    void afficherOccurrences() const;

private:
    std::unordered_map<std::string, int> occurrences; // Map pour stocker le nombre d'occurrences de chaque commande
    std::vector<std::string> lignesFichier;           // Contenu du fichier d'historique
};


#endif // __OCCURRENCE__
