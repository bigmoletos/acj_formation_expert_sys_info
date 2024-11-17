#include <iostream>
// #include "librairies/librairie_dynamique/MyFirstDll/exported_function.h"
#include "exported_function.h"

int main() {
    std::cout << "Appel de la fonction exportée depuis la DLL..." << std::endl;
    PrintMessage();  // Appel de la fonction exportée
    return 0;
}