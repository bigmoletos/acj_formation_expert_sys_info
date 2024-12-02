import ctypes
import numpy as np
import time

# Charger la bibliothèque compilée (adaptez selon le système d'exploitation)
#lib = ctypes.CDLL("./matmul.so")  # Sous Linux/MacOS
lib = ctypes.CDLL("./matmul.dll")  # Sous Windows

# Définir les types des arguments et du retour de la fonction
# argtypes spécifie les types des arguments attendus par la fonction C (int et pointeurs).
# restype est None car la fonction ne retourne pas de valeur explicite.
lib.matmul.argtypes = (ctypes.c_int, ctypes.POINTER(ctypes.c_int),
                       ctypes.POINTER(ctypes.c_int),
                       ctypes.POINTER(ctypes.c_int))
lib.matmul.restype = None


# Fonction helper pour convertir une matrice NumPy en pointeur C
# numpy_to_c_pointer convertit une matrice NumPy en un pointeur compatible avec le type ctypes.POINTER(ctypes.c_int).
def numpy_to_c_pointer(matrix):
    return matrix.ctypes.data_as(ctypes.POINTER(ctypes.c_int))


# Paramètres
n = 100  # Taille de la matrice
A = np.random.randint(1, 101, size=(n, n), dtype=np.int32)
B = np.random.randint(1, 101, size=(n, n), dtype=np.int32)
C = np.zeros((n, n), dtype=np.int32)

# Appeler la fonction C pour la multiplication
# lib.matmul(n, numpy_to_c_pointer(A), numpy_to_c_pointer(B), numpy_to_c_pointer(C)) appelle la fonction C pour effectuer la multiplication.
start_c = time.time()
lib.matmul(n, numpy_to_c_pointer(A), numpy_to_c_pointer(B),
           numpy_to_c_pointer(C))
end_c = time.time()


def matmulpyt(n, A, B):
    # Initialisation de la matrice résultat C avec des zéros
    C = [[0] * n for _ in range(n)]

    # Itérations pour chaque élément de la matrice résultat
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]

    return C


# Vérification avec NumPy pour le même calcul
start_np = time.time()
C_python = matmulpyt(n, A, B)
end_np = time.time()

# Comparaison des résultats : np.array_equal(C, C_numpy) vérifie que les résultats du calcul en C et en NumPy sont identiques.
assert np.array_equal(C, C_python), "Les résultats ne correspondent pas !"

# Affichage des temps
print(f"Temps de calcul en C : {end_c - start_c:.2f} secondes")
print(f"Temps de calcul en NumPy : {end_np - start_np:.2f} secondes")
