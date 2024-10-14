#include <stdio.h>

int main() {
    // Déclarations de variables de différents types
    int int_var = 42;
    long long_var = 1234567890L;
    unsigned int uint_var = 300;
    unsigned long ulong_var = 4000000000UL;
    float float_var = 3.14159f;
    double double_var = 2.718281828459;
    long double ldouble_var = 1.61803398875L;
    char char_var = 'A';
    char string_var[] = "Hello, World!";

    // Impression des différentes variables avec les formats appropriés
    printf("Int: %d\n", int_var);
    printf("Long Int: %ld\n", long_var);
    printf("Unsigned Int: %u\n", uint_var);
    printf("Unsigned Long Int: %lu\n", ulong_var);

    // Représentation en octal et hexadécimal
    printf("Unsigned Int (octal): %o\n", uint_var);
    printf("Unsigned Int (hexadécimal): %x\n", uint_var);
    printf("Unsigned Long Int (hexadécimal): %lx\n", ulong_var);

    // Valeurs flottantes et doubles
    printf("Float: %f\n", float_var);
    printf("Double: %f\n", double_var);
    printf("Long Double: %Lf\n", ldouble_var);

    // Notation exponentielle
    printf("Double (exponentielle): %e\n", double_var);
    printf("Long Double (exponentielle): %Le\n", ldouble_var);

    // Notation courte entre %f et %e
    printf("Double (notation courte): %g\n", double_var);
    printf("Long Double (notation courte): %Lg\n", ldouble_var);

    // Caractère et chaîne de caractères
    printf("Char: %c\n", char_var);
    printf("String: %s\n", string_var);

    return 0;
}
