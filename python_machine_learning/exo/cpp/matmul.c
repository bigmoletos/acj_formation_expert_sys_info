#include <stdio.h>
#include <stdlib.h>

// Fonction pour effectuer la multiplication matricielle
void matmul(int n, int* A, int* B, int* C) {
    // Itérations pour chaque élément de la matrice résultat
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = 0;  // Initialisation
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}