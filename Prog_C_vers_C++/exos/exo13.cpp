#include <iostream>
using namespace std;

/**
 * @brief [Description de main]
 *
 * @param Aucun [Cette fonction n'a pas de param�tres]
 * @return int [Description du retour]
 */
int main()
{
    int n;
    cout << "Entrez une valeur pour n : ";
    cin >> n;

// calcul d'une somme de n entier de 1 à n
    if (n > 0)
    {
        int somme = n * (n + 1) / 2;

        cout << "La somme des entiers de 1 à " << n << " est : " << somme << endl;
    }
    else
    {
        cout << "Veuillez entrer une valeur positive pour n." << endl;
    }

    return 0;
}