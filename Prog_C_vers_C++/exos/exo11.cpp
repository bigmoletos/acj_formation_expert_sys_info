#include <iostream>
#include <cstdlib> // Pour utiliser exit()
using namespace std;

int main() {
    const float pi = 3.141592;
    float small_radius = -1, big_radius = -1, areaBig = -1, areaSmall = -1, area = -1;

    // Demande des valeurs à l'utilisateur
    cout << "Entrez les rayons petit et grand : ";

    // Validation des entrées
    if (!(cin >> small_radius >> big_radius)) {
        cerr << "Erreur: entrées invalides.\n";
        return 1;
    }

    cout << "Petit rayon = " << small_radius << " & Grand rayon = " << big_radius << endl;

    // Vérification des valeurs
    if (!(big_radius > small_radius && small_radius > 0)) {
        cerr << "Valeurs incorrectes pour les rayons interne et externe.\n";
        return 1;
    }

    // Calcul des aires
    areaBig = pi * big_radius * big_radius;
    areaSmall = pi * small_radius * small_radius;
    area = areaBig - areaSmall;

    // Affichage du résultat
    cout << "Pour un grand rayon de " << big_radius << " et un petit rayon de " << small_radius
         << ", la surface de l'anneau est : " << area << endl;

    return 0;
}