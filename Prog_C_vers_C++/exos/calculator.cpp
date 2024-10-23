#include <iostream>

void calculatrice() {
    char operation;
    double num1, num2;

    // Demander l'opération à effectuer
    std::cout << "Entrez l'opération (+, -, *, /): ";
    std::cin >> operation;

    // Demander les deux nombres
    std::cout << "Entrez deux nombres: ";
    std::cin >> num1 >> num2;

    // Exécuter l'opération en fonction de l'entrée
    switch (operation) {
        case '+':
            std::cout << "Résultat: " << num1 + num2 << std::endl;
            break;
        case '-':
            std::cout << "Résultat: " << num1 - num2 << std::endl;
            break;
        case '*':
            std::cout << "Résultat: " << num1 * num2 << std::endl;
            break;
        case '/':
            if (num2 != 0)
                std::cout << "Résultat: " << num1 / num2 << std::endl;
            else
                std::cout << "Erreur: division par zéro!" << std::endl;
            break;
        default:
            std::cout << "Opération invalide" << std::endl;
    }
}

int main() {
    calculatrice();  // Appel de la fonction calculatrice
    return 0;
}
