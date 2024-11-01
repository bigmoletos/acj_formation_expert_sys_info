#include "menu.hpp"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <cstdio> // pour printf
#include "logger.hpp" // Inclusion du fichier logger

/**
 * @class Menu
 * @brief Classe qui gère l'affichage du menu et les interactions utilisateur.
 *
 * La classe `Menu` permet d'afficher un menu avec des options, de récupérer le choix
 * de l'utilisateur, et d'afficher des messages en fonction du choix effectué.
 *
 * depuis le main il faut donner un tablea par exemple:
 * int main(){
 *     std::vector<std::string> optionsMenuMessages{
        "Creer le fichier historique des commandes shell",
        "Lecture du fichier des commandes shell usuelles",
        "Affichage du nombre d'occurrences des commandes shell",
        "Prise en compte des commandes sudo",
        "Inverser la casse des caractères",
        "Traitement sans affichage console",
        "Mise à jour du fichier des commandes shell",
        "Sortir du programme"};

     // Affichage et gestion du menu
    Menu menu(optionsMenuMessages);
    menu.afficherMenu();
    menu_choix = menu.obtenirChoix();
    menu.afficherMessageChoix(menu_choix);
 * }
 */

/**
 * @brief Constructeur qui initialise les options du menu.
 * @param optionsMessages Un vecteur de chaînes de caractères contenant les messages des options.
 */
Menu::Menu(const std::vector<std::string> &optionsMessages) : optionsMessages(optionsMessages)
{
}

/**
 * @brief Affiche les options du menu en vert, avec les numéros en rouge.
 *
 * Cette méthode utilise `printf` et des codes ANSI pour afficher le texte coloré.
 * Les numéros des options sont en rouge et les descriptions en vert.
 */
void Menu::afficherMenu() const
{
    // Affichage en vert du titre "Choisissez votre option"
    printf("\033[32mChoisissez votre option:\033[0m\n");

    // Boucle pour afficher chaque option avec son numéro en rouge et son texte en vert
    for (size_t i = 0; i < optionsMessages.size(); ++i)
    {
        printf("\033[31m%zu.\033[32m %s\033[0m\n", i + 1, optionsMessages[i].c_str());
    }
}

/**
 * @brief Récupère et valide le choix de l'utilisateur.
 *
 * Cette méthode affiche une invite de saisie et vérifie que l'utilisateur entre un
 * entier valide correspondant à une option du menu. En cas d'erreur, un message
 * d'erreur en rouge est affiché et l'utilisateur est invité à réessayer.
 *
 * @return Un entier représentant le choix de l'utilisateur.
 */
int Menu::obtenirChoix() const
{
    int choix;
    while (true)
    {
        std::cout << "Votre choix : ";
        std::cin >> choix;

        // Vérifie si l'entrée est invalide ou hors limites
        if (std::cin.fail() || choix < 1 || choix > static_cast<int>(optionsMessages.size()))
        {
            std::cin.clear();                                                   // Réinitialise le flux pour gérer les erreurs de saisie
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore la ligne erronée

            // Affiche un message d'erreur en rouge si le choix est invalide
            printf("\033[31mErreur : veuillez entrer un nombre entre 1 et %d.\033[0m\n", static_cast<int>(optionsMessages.size()));
        }
        else
        {
            return choix; // Retourne le choix valide
        }
    }
}

/**
 * @brief Affiche un message confirmant l'option choisie par l'utilisateur en vert.
 *
 * Cette méthode affiche un message personnalisé en fonction du choix de l'utilisateur.
 * Si le choix est invalide, un message d'erreur en rouge est affiché.
 *
 * @param choix L'entier représentant le choix de l'utilisateur.
 */
void Menu::afficherMessageChoix(int choix) const
{
    if (choix >= 1 && choix <= static_cast<int>(optionsMessages.size()))
    {
        // Récupère le message associé au choix et le transforme en minuscules
        std::string message = optionsMessages[choix - 1];
        std::transform(message.begin(), message.end(), message.begin(), [](unsigned char c)
                       { return std::tolower(c); });

        // Affiche le message en vert pour confirmer l'option choisie
        printf("\033[32mVous avez choisi l'option %d \"%s\"\033[0m\n", choix, message.c_str());
    }
    else
    {
        // Affiche un message d'erreur en rouge si l'option est inconnue
        printf("\033[31mOption inconnue.\033[0m\n");
    }
}

// si on mettre en couleur le texte
// printf ('%-6s' "This is text";
// pour revenir à la couleur par defaut
// printf("\033[1;33m");