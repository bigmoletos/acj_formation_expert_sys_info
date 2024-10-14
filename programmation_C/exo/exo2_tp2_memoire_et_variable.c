#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SPOIL
1- Type nom_variable = valeur_init;
2- Attention aux signes. Les nombres à virgule s’écrivent avec un point. Les caractères
doivent être délimités par des simple cotes ‘ ‘.
3- Short et int: %d, long: %ld, float et double: %f et char: %c
A- Utilisez la fonction sizeof(type)
V - SPOIL! (aide)
*/
// Déclaration des variables globales avec des valeurs appropriées
int int_var = 50;              // Valeur entière
long long_var = 1000000000L;    // Long pour les grandes valeurs
short short_var = 100;           // Short pour les petites valeurs entières
float float_var = 3.14f;        // Nombre à virgule flottante
double double_var = 3.1415956548984941;    // Double pour plus de précision sur les flottants
char char_var = 'F';            // Caractère simple
char string_var[] = "Desmedt, Franck";  // Chaîne de caractères

int main()
{
    // Affiche le titre du programme
    printf("TP2: Mémoire et Variables \n\n");

    // Affiche les valeurs et tailles des différentes variables en mémoire
    printf("Mon int = %d fait %zu octets\n", int_var, sizeof(int_var));
    printf("Mon long = %ld fait %zu octets\n", long_var, sizeof(long_var));
    printf("Mon short = %d fait %zu octets\n", short_var, sizeof(short_var));
    printf("Mon float = %f fait %zu octets\n", float_var, sizeof(float_var));
    printf("Mon double = %f fait %zu octets\n", double_var, sizeof(double_var));
    printf("Mon char = %c fait %zu octets\n", char_var, sizeof(char_var));

    // Affiche la chaîne de caractères et sa taille en mémoire
    printf("Mon string = \"%s\" fait %zu octets\n", string_var, sizeof(string_var));


}
