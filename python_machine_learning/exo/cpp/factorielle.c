#include <stdio.h>

// Fonction récursive pour calculer la factorielle
unsigned long long factorielle(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorielle(n - 1);
    }
}