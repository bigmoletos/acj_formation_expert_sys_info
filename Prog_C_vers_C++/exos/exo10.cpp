#include <iostream>
#include <cctype>  // Pour utiliser isdigit()

using namespace std;

int main() {
    char c = '5';

    if (isdigit(c)) {
        cout << c << " est un chiffre." << endl;
    } else {
        cout << c << " n'est pas un chiffre." << endl;
    }

    return 0;
}