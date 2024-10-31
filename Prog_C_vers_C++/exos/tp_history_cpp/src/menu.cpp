#include "menu.hpp"
#include <iostream>
#include <limits>
#include <algorithm> // Pour std::transform
#include <cctype>    // Pour std::tolower

Menu::Menu()
    : optionsMessages{
          "Creer le fichier historique des commandes shell",
          "Lecture du fichier des commandes shell usuelles",
          "Affichage du nombre d'occurrences des commandes shell",
          "Prise en compte des commandes sudo",
          "Inverser la casse des caractères",
          "Traitement sans affichage console",
          "Mise à jour du fichier des commandes shell",
          "Sortir du programme"}
{
}

void Menu::afficherMenu() const
{
    std::cout << "Choisissez votre option:\n";
    for (size_t i = 0; i < optionsMessages.size(); ++i)
    {
        std::cout << i + 1 << ". " << optionsMessages[i] << "\n";
    }
}

int Menu::obtenirChoix() const
{
    int choix;
    while (true)
    {
        std::cout << "Votre choix : ";
        std::cin >> choix;

        if (std::cin.fail() || choix < 1 || choix > static_cast<int>(optionsMessages.size()))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Erreur : veuillez entrer un nombre entre 1 et " << optionsMessages.size() << "." << std::endl;
        }
        else
        {
            return choix;
        }
    }
}

void Menu::afficherMessageChoix(int choix) const
{
    if (choix >= 1 && choix <= static_cast<int>(optionsMessages.size()))
    {
        // Copie du message en minuscule
        std::string message = optionsMessages[choix - 1];
        std::transform(message.begin(), message.end(), message.begin(), [](unsigned char c)
                       { return std::tolower(c); });

        std::cout << "Vous avez choisi l'option " << choix << " \"" << message << "\" " << std::endl;
    }
    else
    {
        std::cerr << "Option inconnue." << std::endl;
    }
}
