#include <stdio.h>

/**
 * @brief Additionne deux entiers et retourne le résultat.
 *
 * Cette fonction prend deux entiers en entrée et retourne leur somme.
 *
 * @param a Le premier entier à additionner.
 * @param b Le deuxième entier à additionner.
 * @return int Le résultat de l'addition des deux entiers.
 *
 * Exemple d'utilisation:
 *
 *      int result = addition(3, 4);  // Retourne 7
 */
int addition(int a, int b) {
    // Retourner la somme des deux entiers a et b
    return a + b;
}

/**
 * @brief Fonction principale du programme.
 *
 * Cette fonction affiche "Hello, World!" et teste la fonction `addition`
 * en calculant la somme de deux nombres, puis affiche le résultat.
 *
 * @return int Le code de sortie du programme (0 signifie succès).
 *
 * Exemple de test manuel :
 *
 *      Le programme devrait afficher :
 *      Hello, World!
 *      La somme de 3 et 4 est: 7
 */
int main() {
    // Afficher "Hello, World!"
    printf("Hello, World!\n");

    // Définir deux entiers à additionner
    int x = 3;
    int y = 4;

    // Calculer la somme à l'aide de la fonction addition
    int somme = addition(x, y);

    // Afficher le résultat de l'addition
    printf("La somme de %d et %d est: %d\n", x, y, somme);

    // Retourner 0 pour indiquer que le programme s'est terminé correctement
    return 0;
}
