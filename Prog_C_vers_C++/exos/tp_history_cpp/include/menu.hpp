#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <string>
#include <vector>

class Menu
{
public:
    // Constructeur
    Menu();

    // Méthode pour afficher le menu des options
    void afficherMenu() const;

    // Méthode pour capturer et valider la saisie de l'utilisateur
    int obtenirChoix() const;

    // Méthode pour afficher un message détaillé en fonction du choix
    void afficherMessageChoix(int choix) const;

private:
    // Vector pour stocker les messages de chaque option
    std::vector<std::string> optionsMessages;
};

#endif // __MENU_HPP__
