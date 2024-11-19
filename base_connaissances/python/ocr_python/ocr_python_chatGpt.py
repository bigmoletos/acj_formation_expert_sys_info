from PIL import Image
import pytesseract
import os

# Configuration de Tesseract
pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"

# Chemin de l'image
image_path = r"prog_C_vers_C++\copie_ecran\image.jpg"

# Charger l'image pour extraire le texte
if os.path.exists(image_path):
    image = Image.open(image_path)

    # Extraire le texte de l'image
    extracted_text = pytesseract.image_to_string(image, lang="eng")

    # Afficher le texte extrait dans le terminal
    print("Texte extrait de l'image :")
    print(extracted_text)

    # Sauvegarder le texte dans un fichier
    output_path = r"prog_C_vers_C++\copie_ecran\texte_extrait.txt"
    with open(output_path, "w", encoding="utf-8") as output_file:
        output_file.write(extracted_text)

    print(f"Texte extrait sauvegardé dans : {output_path}")
else:
    print(f"Erreur : Le fichier image '{image_path}' est introuvable.")
