#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <string>
#include <vector>

class Menu
{
public:
    // Constructeur prenant un reference constante vers les messages d'options
    Menu(const std::vector<std::string>& optionsMessages);

    // Méthode pour afficher le menu des options
    void afficherMenu() const;

    // Méthode pour capturer et valider la saisie de l'utilisateur
    int obtenirChoix() const;

    // Méthode pour afficher un message détaillé en fonction du choix
    void afficherMessageChoix(int choix) const;

private:
    const std::vector<std::string> &optionsMessages; // reference constante vers les messages d'options
};

#endif // __MENU_HPP__
