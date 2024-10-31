#include "menu.hpp"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <cstdio> // pour printf

Menu::Menu(const std::vector<std::string>& optionsMessages) : optionsMessages(optionsMessages)
{
}

// void Menu::afficherMenu() const
// {
//     std::cout << "Choisissez votre option:\n";
//     for (size_t i = 0; i < optionsMessages.size(); ++i)
//     {
//         std::cout << i + 1 << ". " << (optionsMessages)[i] << "\n";
//     }
// }
void Menu::afficherMenu() const
{
    // Affichage en vert avec printf
    printf("\033[32mChoisissez votre option:\033[0m\n");

    for (size_t i = 0; i < optionsMessages.size(); ++i)
    {
        // Affichage de chaque option en vert
        printf("\033[31m%zu.\033[32m %s\033[0m\n", i + 1, optionsMessages[i].c_str());
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
            // std::cerr << "Erreur : veuillez entrer un nombre entre 1 et " << optionsMessages.size() << "." << std::endl;
            printf("\033[31mErreur : veuillez entrer un nombre entre 1 et %d.\033[0m\n", static_cast<int>(optionsMessages.size()));
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
        std::string message = (optionsMessages)[choix - 1];
        std::transform(message.begin(), message.end(), message.begin(), [](unsigned char c)
                       { return std::tolower(c); });

        // std::cout << "Vous avez choisi l'option " << choix << " \"" << message << "\" " << std::endl;
        //impression du message d'erreur en vert
        printf("\033[32mVous avez choisi l'option %d \"%s\"\033[0m\n", choix, message.c_str());
    }
    else
    {
        // std::cerr << "Option inconnue." << std::endl;
        printf("\033[31mOption inconnue.\033[0m\n");
    }
}
// si on mettre en couleur le texte
// printf ('%-6s' "This is text";
// pour revenir à la couleur par defaut
// printf("\033[1;33m");