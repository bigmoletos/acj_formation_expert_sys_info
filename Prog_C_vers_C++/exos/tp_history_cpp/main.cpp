#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage
#include "header.hpp"
// using namespace std;

/*
1- coder une commande shell nommée hist_stats
2 -celle-ci calcule la répartition des commandes shell utilisées
3 - ajouter cette commande hist_stats à votre PATH

Arguments de la ligne de commande :

hstF : fichier texte contenant l'historique des commandes shell
vldF : fichier texte contenant les commandes shell à considérer
genF : fichier texte généré enregistrant la répartition
sudo : prise en considération des commandes exécutées en tant qu’administrateur
verb : affichage de toutes les informations au cours du traitement
updt : mise à jour éventuelle du fichier de commandes
Résultats :

affichage des messages d’erreurs éventuels et des informations à l’écran
enregistrement de la répartition dans un fichier texte
mise à jour éventuelle du fichier de commandes
*/

int main()
{
    int menu_choix{0};
    bool affichage_choix{true};
    //----------DEPART CHRONO--------------
    //------ Point de départ pour le chronométrage
    std::chrono::high_resolution_clock::time_point start_time;
    // Démarrage du chronométrage
    chrono_start(start_time);

    //-------MENU-------------

    // Menu avec les choix
    std::cout << "Choisissez votre option:\n"
              << "1. Creer le fichier historique des commandes shell\n"
              << "2. Lecture du fichier des commandes shell usuelles\n"
              << "3. Affichaage du nombres d'occurences des commandes shell\n"
              << "4. Prise en compte des commandes sudo\n"
              << "5. Inverser la casse des caractères\n"
              << "6. Traitement sans affichage console\n"
              << "7. Mise à jour du fichier des commandes shell\n"
              << "8. Sortir du programme\n";
    std::cin >> menu_choix;

    //----------CHARGEMENT FICHIER--------------
    // Chemin du fichier à charger
    // std::string cheminFichier ="C:/AJC_formation/prog_C_vers_C++/exos/tp_history_cpp/data/fichier_historique.txt";
    std::string cheminFichier ="fichier_historique.txt";

    // Création de l'objet ChargeFichierTxt
    ChargeFichierTxt chargeur(cheminFichier);

    // Chargement du fichier
    if (chargeur.charger())
    {
        // Affichage du contenu si le chargement est réussi
        std::cout << "Contenu du fichier " << cheminFichier << " :" << std::endl;
        for (const auto &ligne : chargeur.getLignes())
        {
            std::cout << ligne << std::endl;
        }
    }
    else
    {
        std::cerr << "Le chargement du fichier a échoué." << std::endl;
    }
    //----------NOMBRE OCCURENCES--------------

    // Compter les occurrences des commandes
    NombreOccurrence nombreOccur(chargeur.getLignes());
    nombreOccur.calculerOccurrences();
    nombreOccur.afficherOccurrences();

    //----------FIN CHRONO--------------
    // Fin du chronométrage et affichage du temps écoulé
    chrono_end(start_time, "Temps d'exécution de la tâche simulée");

    return 0;
}
