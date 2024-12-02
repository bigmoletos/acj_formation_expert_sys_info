from numba import njit, prange
import numpy as np
# from numba import njit
import time


# Fonction standard Python
def compute_sum(arr):
    total = 0.0
    for i in range(len(arr)):
        total += arr[i]
    return total


# Fonction optimisée avec Numba
@njit
def compute_sum_numba(arr):
    total = 0.0
    for i in range(len(arr)):
        total += arr[i]
    return total


# Création d'un grand tableau
array = np.random.rand(10**10)

# Temps d'exécution sans Numba
start = time.time()
result = compute_sum(array)
print("Python Time:", time.time() - start)

# Temps d'exécution avec Numba
start = time.time()
result = compute_sum_numba(array)
print("Numba Time:", time.time() - start)
# print("Numba Time:", time.time() - start)

#  autre exemple avec la parallelisation


@njit(parallel=True)
def parallel_sum(arr):
    total = 0.0
    for i in prange(
            len(arr)):  # prange au lieu de range pour la parallélisation
        total += arr[i]
    return total


# # Création d'un grand tableau
# array = np.random.rand(10**6)

# Calcul avec parallélisation
start2 = time.time()
result = parallel_sum(array)
print("Result:", result)
print("Numba Time:", time.time() - start2)
