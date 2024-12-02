#include <iostream>
#include <cctype>  // Pour utiliser isdigit()

using namespace std;

/**
 * @brief [Description de main]
 *
 * @param Aucun [Cette fonction n'a pas de paramètres]
 * @return int [Description du retour]
 */
int main() {
    char c = '5';

    if (isdigit(c)) {
        cout << c << " est un chiffre." << endl;
    } else {
        cout << c << " n'est pas un chiffre." << endl;
    }

    return 0;
}