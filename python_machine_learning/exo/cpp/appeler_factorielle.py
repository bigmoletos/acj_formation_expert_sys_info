# code Python
import ctypes

# Charger la bibliothèque (remplacez par "./factorielle.so" pour Linux/MacOS)
lib = ctypes.CDLL("./factorielle.dll")

# Définir le type de l'argument et le type de retour
lib.factorielle.argtypes = (ctypes.c_int, )
lib.factorielle.restype = ctypes.c_ulonglong

# Appeler la fonction avec un exemple
nombre = 10
resultat = lib.factorielle(nombre)
print(f"Factorielle de {nombre} (calculée en C) :", resultat)
