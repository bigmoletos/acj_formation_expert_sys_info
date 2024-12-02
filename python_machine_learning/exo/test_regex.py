import re

# Recherche de tous les mots commençant par "Py"
texte = "Python est génial. PyPI et PyTorch sont basés sur Python."
motif = r"\bPy\w*"
resultats = re.findall(motif, texte)
print(resultats)  # Affiche : ['Python', 'PyPI', 'PyTorch']
