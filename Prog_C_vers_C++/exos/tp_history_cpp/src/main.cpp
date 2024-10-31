#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand() avec l'heure actuelle
#include <chrono>  // Pour les fonctions de chronométrage
#include "menu.hpp"
#include "chrono.hpp"
#include "charge_fichier_txt.hpp"
#include "nombre_occurence.hpp"
#include "tableau_depuis_fichier.hpp"
#include "fichier_historique.hpp"
#include "logger.hpp"

/**
 * @file main.cpp
 * @brief Programme principal qui gère un menu pour différentes actions sur des fichiers de commandes shell.
 *
 * Ce programme charge et analyse des fichiers de commandes shell, calcule des occurrences de commandes,
 * et affiche les résultats selon le choix de l'utilisateur dans un menu interactif. Il utilise une classe
 * Logger pour gérer les affichages à différents niveaux de log.
 */

/**
 * @brief Fonction principale du programme.
 *
 * Cette fonction :
 * 1. Initialise des variables pour le chargement de fichiers et les messages de menu.
 * 2. Démarre le chronométrage pour mesurer le temps d'exécution.
 * 3. Crée un objet Logger pour gérer les messages d'affichage.
 * 4. Charge un fichier d'historique de commandes shell.
 * 5. Affiche un menu interactif permettant à l'utilisateur de sélectionner une option.
 * 6. Exécute des actions selon le choix de l'utilisateur (par ex., calcul d'occurrences, affichage de commandes).
 * 7. Affiche le temps d'exécution.
 *
 * @return 0 en cas de succès, 1 si le chargement initial du fichier échoue.
 */
int main()
{
    //----------INIT VARIABLES--------------
    int menu_choix{0};                                                               // Choix de l'utilisateur pour le menu
    std::string cheminFichier = "data/fichier_historique.txt";                       // Chemin du fichier d'historique de commandes
    std::string cheminFichierCOmmandesUsuelles = "data/commande_shell_usuelles.txt"; // Chemin du fichier des commandes usuelles
    std::string cheminScriptSh = "./script_perso/histo.sh";                          // Chemin du script shell pour créer un historique

    // Messages à afficher dans le menu
    std::vector<std::string> optionsMenuMessages{
        "Creer le fichier historique des commandes shell",
        "Lecture du fichier des commandes shell usuelles",
        "Affichage du nombre d'occurrences des commandes shell",
        "Prise en compte des commandes sudo",
        "Traitement sans affichage console",
        "Mise à jour du fichier des commandes shell",
        "Sortir du programme"};

    //----------DEPART CHRONO--------------
    // Démarrage du chronométrage pour mesurer le temps d'exécution de tout le programme
    std::chrono::high_resolution_clock::time_point start_time;
    chrono_start(start_time);

    //----------LOGGER-------------
    std::string niveau_logger = "DEBUG";
    Logger logger(LogLevel::niveau_logger); // Initialisation du logger avec un niveau de log à DEBUG

    //----------CHARGEMENT FICHIER--------------
    // Chargement du fichier d'historique de commandes
    ChargeFichierTxt chargeur(cheminFichier);
    ChargeFichierTxt chargeur2(cheminFichierCOmmandesUsuelles);

    // Si le chargement du fichier échoue, affiche un message d'erreur et quitte le programme
    if (!chargeur.charger())
    {
        logger.error("Le chargement du fichier a échoué.");
        exit(1);
    }

    //----------OCCURRENCES--------------
    // Initialisation de l'objet NombreOccurrence pour calculer les occurrences de commandes
    NombreOccurrence nombreOccur(chargeur.getLignes());

    //-------MENU-------------
    // Affichage et gestion du menu interactif
    Menu menu(optionsMenuMessages);
    menu.afficherMenu();
    menu_choix = menu.obtenirChoix();
    menu.afficherMessageChoix(menu_choix);

    //----------SWITCH SUR LE CHOIX--------------
    // Exécution de l'action correspondant au choix de l'utilisateur
    switch (menu_choix)
    {
    case 1:
        // Option 1 : Création du fichier historique via un script shell
        logger.info("Création du fichier historique en cours...");
        creerFichierHistorique(cheminScriptSh);
        break;

    case 2:
        // Option 2 : Chargement et affichage du fichier des commandes usuelles
        if (chargeur2.charger())
        {
            logger.info("Contenu du fichier des commandes usuelles chargé avec succès :");
            for (const auto &ligne : chargeur2.getLignes())
            {
                logger.debug(ligne); // Affichage de chaque ligne pour vérification en mode DEBUG
            }
        }
        else
        {
            logger.error("Le chargement du fichier des commandes usuelles a échoué.");
        }
        break;

    case 3:
        // Option 3 : Calcul et affichage des occurrences de chaque commande
        logger.info("Calcul des occurrences des commandes...");
        nombreOccur.calculerOccurrences();
        nombreOccur.afficherOccurrences();
        break;

    case 4:
    {
        // Option 4 : Affichage des commandes qui commencent par 'sudo'
        nombreOccur.calculerOccurrences();
        std::vector<std::string> sudoCommandes = nombreOccur.getCommandesAvecSudo();
        logger.info("Commandes qui commencent par 'sudo' :");
        for (const auto &cmd : sudoCommandes)
        {
            logger.debug(cmd); // Affiche chaque commande en mode DEBUG
        }
        break;
    }

    case 5:
        // Option 5 : Traitement sans affichage console
        logger.info("Traitement sans affichage console démarré.");
        break;

    case 6:
        // Option 6 : Mise à jour du fichier des commandes shell
        logger.info("Mise à jour du fichier des commandes shell en cours...");
        break;

    case 7:
        // Option 7 : Sortie du programme
        logger.info("Sortie du programme.");
        return 0;

    default:
        // Option non reconnue
        logger.warning("Option non reconnue.");
        break;
    }

    //----------FIN CHRONO--------------
    // Fin du chronométrage et affichage du temps écoulé
    chrono_end(start_time, "Temps d'exécution de la tâche simulée");

    return 0;
}
