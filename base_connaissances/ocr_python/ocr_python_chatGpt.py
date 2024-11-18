from PIL import Image
import pytesseract

# Charger l'image pour extraire le texte
image_path = "image.png"
image = Image.open(image_path)

# Extraire le texte de l'image
extracted_text = pytesseract.image_to_string(image, lang="eng")

extracted_text
