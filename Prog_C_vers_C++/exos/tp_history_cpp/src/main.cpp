#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage
// #include "header.hpp"
#include "menu.hpp"
#include "chrono.hpp"
#include "charge_fichier_txt.hpp"
#include "nombre_occurence.hpp"
#include "tableau_depuis_fichier.hpp"
#include "fichier_historique.hpp"

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
    //----------INIT VARIABLES--------------
    int menu_choix{0};
    // bool affichage_choix{true};
    // Chemin du fichier à charger
    std::string cheminFichier = "data/fichier_historique.txt";
    // Chemin des scripts SH
    std::string cheminScriptSh = "./script_perso/histo.sh";
    // Initialisation des messages d'options
    std::vector<std::string> optionsMenuMessages{
        "Creer le fichier historique des commandes shell",
        "Lecture du fichier des commandes shell usuelles",
        "Affichage du nombre d'occurrences des commandes shell",
        "Prise en compte des commandes sudo",
        "Inverser la casse des caractères",
        "Traitement sans affichage console",
        "Mise à jour du fichier des commandes shell",
        "Sortir du programme"};

    //----------DEPART CHRONO--------------
    //------ Point de départ pour le chronométrage
    std::chrono::high_resolution_clock::time_point start_time;
    // Démarrage du chronométrage
    chrono_start(start_time);

    //----------CHARGEMENT FICHIER--------------
    // Création de l'objet ChargeFichierTxt
    ChargeFichierTxt chargeur(cheminFichier);

    // Charger le fichier avant d'utiliser son contenu
    if (!chargeur.charger())
    {
        std::cerr << "Le chargement du fichier a échoué." << std::endl;
        exit (1); // Quitter si le chargement échoue
    }

    //----------OCCURRENCES--------------
    // Compter les occurrences des commandes
    NombreOccurrence nombreOccur(chargeur.getLignes());

    //-------MENU-------------
    // Affichage et gestion du menu

    Menu menu(optionsMenuMessages);
    menu.afficherMenu();
    menu_choix = menu.obtenirChoix();
    menu.afficherMessageChoix(menu_choix);

    switch (menu_choix)
    {
    case 1:
        // Appeler la méthode pour créer le fichier historique
        creerFichierHistorique(cheminScriptSh);
        break;

    case 2:
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
        break;

    case 3:

        // Compter les occurrences des commandes
        nombreOccur.calculerOccurrences();
        nombreOccur.afficherOccurrences();
        break;

    case 4:

        break;

    case 5:
        break;

    case 6:
        break;

    case 7:
        break;

    case 8:
        return 0;

    default:
        break;
        }

        //----------FIN CHRONO--------------
        // Fin du chronométrage et affichage du temps écoulé
        chrono_end(start_time, "Temps d'exécution de la tâche simulée");

        return 0;
    }
