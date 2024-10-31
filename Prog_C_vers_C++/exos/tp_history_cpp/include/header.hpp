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
    #include <unordered_map>




// // -------Fonctions pour charger fichier texte dans tableau-----------------
// class ChargeFichierTxt
// {
// public:
//     // Constructeur qui prend le chemin du fichier à charger
//     ChargeFichierTxt(const std::string &chemin);

//     // Méthode pour charger le fichier
//     bool charger();

//     // Obtenir les lignes du fichier chargé
//     const std::vector<std::string> &getLignes() const;

// private:
//     std::string cheminFichier;         // Chemin du fichier
//     std::vector<std::string> lignes;   // Contenu du fichier
//     bool verifierFichier();            // Vérifie si le fichier existe et est accessible
//     bool estFichierTexteOuCSV() const; // Vérifie si le fichier est de type .txt ou .csv
//     };

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

    // // -------Fonctions pour mesurer le temps-----------------
    // // Déclaration des fonctions pour mesurer le temps
    // void chrono_start(std::chrono::high_resolution_clock::time_point &t1);
    // void chrono_end(const std::chrono::high_resolution_clock::time_point &t1, const std::string &message);

    // // -------Fonctions pour charger les fichiers
    // void charger_donnees_fichier(const std::string &nom_fichier, std::vector<int> &tableau);

    // // -------Fonctions pour construire un tableau vector
    // void generer_valeurs_aleatoires(std::array<int, 100> &tableau);

#endif // __TAB__
