#include "fichier_historique.hpp"
#include <iostream>
#include <cstdlib> // Pour la fonction system
#include "logger.hpp" // Inclusion du fichier logger


/**
 * @brief [Description de creerFichierHistorique]
 *
 * @param &cheminScriptSh [Description du param�tre]
 * @return void [Description du retour]
 */
void creerFichierHistorique(const std::string &cheminScriptSh)
{
    // std::cout << "Exécution de la création du fichier historique avec le script " << cheminScriptSh << std::endl;
    logger.info("Exécution de la création du fichier historique avec le script " + cheminScriptSh);
    //  cast de du chemin vers le script SH en const char* car c'est ce qui est attendu par la fonction system
    const char* pathSCriptSh = cheminScriptSh.c_str();
    // execution  du script shell et stockage du code retour de la fonction du script dans une variable retour
    int retour = system(pathSCriptSh);

    if (retour == -1)
    {
        // std::cerr << "Erreur : échec de l'exécution du script." << std::endl;
        logger.error("Erreur : échec de l'exécution du script.");
    }
    else
    {
        // std::cout << "Script exécuté avec succès." << std::endl;
        logger.info("Script exécuté avec succès.");
    }
}
