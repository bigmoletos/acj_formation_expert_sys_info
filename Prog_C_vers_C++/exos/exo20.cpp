#include <iostream>
#include <cmath>

// algo de heron ou babylone
// Fonction pour calculer la racine carrée en utilisant une méthode itérative
// Paramètres : nombre (double)
// Retourne : racine carrée approximative du nombre
double racine_carre(double nombre)
{
    double estimation = nombre / 2;          // Initialiser avec la moitié du nombre
    for (int etape = 0; etape < 35; etape++) // Boucle pour améliorer l'estimation
        estimation = (estimation + nombre / estimation) * 0.5;
    return estimation; // Retourner l'estimation finale
}

int main()
{
    std::cout.precision(15);                              // Définir la précision des résultats
    double valeurs[] = {5, 98, 4562 , 999999, 9e122, -10.10}; // Tableau de valeurs pour lesquelles calculer la racine carrée

    for (auto valeur : valeurs)
    {
        // Afficher la valeur pour laquelle on calcule la racine carrée
        std::cout << "racine_carre(" << valeur << "):\n";

        // Calculer la racine carrée avec la fonction personnalisée et la fonction standard
        double res_perso = racine_carre(valeur), res_cpp = sqrt(valeur);

        // Calculer le carré des résultats pour vérifier l'exactitude
        double carre_perso = res_perso * res_perso, carre_cpp = res_cpp * res_cpp;

        // Afficher les résultats de la fonction personnalisée
        std::cout << " res_perso: " << res_perso << " => " << carre_perso << " => " << abs(valeur - carre_perso) << "\n";

        // Afficher les résultats de la fonction C++ standard
        std::cout << " res_cpp: " << res_cpp << " => " << carre_cpp << " => " << abs(valeur - carre_cpp) << "\n\n";
    }
}
