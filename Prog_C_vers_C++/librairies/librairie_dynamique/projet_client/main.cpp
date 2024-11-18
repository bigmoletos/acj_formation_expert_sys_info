#include <iostream>
// #include "librairies/librairie_dynamique/MyFirstDll/exported_function.h"
#include "exported_function.h"

int main() {
    // PrintMessage();  // Appel de la fonction exportée
 try {
        PrintMessage();
    } catch (...) {
        std::cerr << "Failed to call PrintMessage!" << std::endl;
    }
    std::cout << "Appel de la fonction exportée exported_function depuis la DLL..." << std::endl;
    // std::cout << "Execution completed." << std::endl;
    //
    std::cout << "Veuillez entrer une valeur : " << std::endl;
    std::cin.get();  // Attente d'une entrée utilisateur
    return 0;
}