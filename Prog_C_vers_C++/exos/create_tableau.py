import random

valeurbasse = 1
valeurHaute = 25

# Génération de 100 nombres entiers aléatoires entre 1 et 25
tab1 = [random.randint(valeurbasse,valeurHaute) for i in range(100)]

# Ouverture des fichiers pour écrire les nombres aléatoires et triés
with open('randIntegers_random.txt', 'w') as f, open('randIntegers_sorted.txt',
                                                     'w') as g:
    # Écriture des nombres aléatoires dans le premier fichier
    for i in tab1:
        f.write(str(i) + '\n')

    # Tri des nombres
    tab1.sort()

    # Écriture des nombres triés dans le second fichier
    for i in tab1:
        g.write(str(i) + '\n')
