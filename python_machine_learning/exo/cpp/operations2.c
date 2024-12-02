#include <stdio.h>

int addition(int a, int b) {
    return a + b;
}

int soustraction(int a, int b) {
    return a - b;
}

float multiplication(float a, float b) {
    return a * b;
}

float division(float a, float b) {
    if (b != 0)
        return a / b;
    else
        return 0;  // Gestion simplifiée de la division par zéro
}