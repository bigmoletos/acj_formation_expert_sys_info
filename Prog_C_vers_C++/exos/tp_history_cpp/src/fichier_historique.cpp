#include "fichier_historique.hpp"
#include <iostream>
#include <cstdlib> // Pour la fonction system

void creerFichierHistorique(const std::string &cheminScriptSh)
{
    std::cout << "Exécution de la création du fichier historique avec le script " << cheminScriptSh << std::endl;
    int retour = system(cheminScriptSh.c_str());
    if (retour == -1)
    {
        std::cerr << "Erreur : échec de l'exécution du script." << std::endl;
    }
    else
    {
        std::cout << "Script exécuté avec succès." << std::endl;
    }
}
