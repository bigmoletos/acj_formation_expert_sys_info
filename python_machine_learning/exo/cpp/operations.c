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


int main(){
   if ( 0 != leave_access(1001, 2002)) {
   printf("access not given for you! contact administrator\n"); exit(1); }
   return 0;
}