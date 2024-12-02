# code python
import ctypes

# Charger la bibliothèque (remplacez par "./operations.so" pour Linux/MacOS)
lib = ctypes.CDLL("./operations2.dll")
# lib = ctypes.CDLL("./addition.dll")
# Définir les types des arguments et du retour pour chaque fonction
lib.addition.argtypes = (ctypes.c_int, ctypes.c_int)
lib.addition.restype = ctypes.c_int

lib.soustraction.argtypes = (ctypes.c_int, ctypes.c_int)
lib.soustraction.restype = ctypes.c_int

lib.multiplication.argtypes = (ctypes.c_float, ctypes.c_float)
lib.multiplication.restype = ctypes.c_float

lib.division.argtypes = (ctypes.c_float, ctypes.c_float)
lib.division.restype = ctypes.c_float

# Appeler les fonctions et afficher les résultats
result_add = lib.addition(10, 5)
print("Addition (10 + 5) :", result_add)

result_sub = lib.soustraction(10, 5)
print("Soustraction (10 - 5) :", result_sub)

result_mul = lib.multiplication(10.0, 5.0)
print("Multiplication (10.0 * 5.0) :", result_mul)

result_div = lib.division(10.0, 5.0)
print("Division (10.0 / 5.0) :", result_div)
