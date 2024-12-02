import ctypes
# import platform

# print(platform.architecture())

# Charger la bibliothèque (adapter le nom selon votre système)
# lib = ctypes.CDLL("./addition.dll")  # Sous Windows
# Sous Windows
lib = ctypes.CDLL("./addition.dll")
# lib = ctypes.CDLL("./addition.so")  # Sous Linux/MacOS

# Définir les types des arguments et du retour de la fonction C
lib.addition.argtypes = (ctypes.c_int, ctypes.c_int)
lib.addition.restype = ctypes.c_int

# Appeler la fonction
resultat = lib.addition(10, 20)
print("Résultat de l'addition en C :", resultat)
