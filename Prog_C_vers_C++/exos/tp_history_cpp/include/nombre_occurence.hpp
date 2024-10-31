#ifndef __OCCURRENCE__
#define __OCCURRENCE__

#include <string>
#include <vector>
#include <unordered_map>

class NombreOccurrence
{
public:
    // Constructeur qui initialise les lignes du fichier
    NombreOccurrence(const std::vector<std::string> &lignes);

    // Méthode pour calculer les occurrences des commandes
    void calculerOccurrences();

    // Méthode pour afficher les commandes et leur nombre d'occurrences, triées par ordre décroissant
    void afficherOccurrences() const;

    // Méthode pour obtenir la liste des commandes qui commencent par "sudo"
    std::vector<std::string> getCommandesAvecSudo() const;

private:
    std::vector<std::string> lignesFichier;           // Contient les lignes du fichier
    std::unordered_map<std::string, int> occurrences; // Map pour stocker les occurrences des commandes
};

#endif // __OCCURRENCE__
