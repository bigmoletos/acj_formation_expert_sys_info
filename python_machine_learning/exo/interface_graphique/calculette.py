import customtkinter as ctk

# Configuration de l'apparence de customtkinter
ctk.set_appearance_mode("System")  # Modes : "System", "Dark", "Light"
ctk.set_default_color_theme("blue")  # Thème par défaut


# Classe de la calculatrice
class Calculatrice(ctk.CTk):

    def __init__(self):
        super().__init__()
        self.title("Calculatrice")
        self.geometry("300x400")

        # Variables
        self.equation = ""

        # Champ d'affichage
        self.display = ctk.CTkEntry(self,
                                    width=250,
                                    height=50,
                                    justify="right",
                                    font=("Arial", 24))
        self.display.grid(row=0, column=0, columnspan=4, padx=10, pady=10)

        # Boutons
        self.creer_boutons()

    def creer_boutons(self):
        # Configuration des boutons (valeurs et positions)
        boutons = [("7", 1, 0), ("8", 1, 1), ("9", 1, 2), ("/", 1, 3),
                   ("4", 2, 0), ("5", 2, 1), ("6", 2, 2), ("*", 2, 3),
                   ("1", 3, 0), ("2", 3, 1), ("3", 3, 2), ("-", 3, 3),
                   ("0", 4, 0), (".", 4, 1), ("=", 4, 2), ("+", 4, 3),
                   ("C", 5, 0)]

        # Création des boutons dynamiquement
        for (text, row, col) in boutons:
            bouton = ctk.CTkButton(
                self,
                text=text,
                width=50,
                height=50,
                command=lambda t=text: self.appuyer_bouton(t))
            bouton.grid(row=row, column=col, padx=5, pady=5)

    def appuyer_bouton(self, caractere):
        if caractere == "C":
            # Effacer l'affichage
            self.equation = ""
            self.display.delete(0, ctk.END)
        elif caractere == "=":
            try:
                # Évaluer l'expression mathématique
                resultat = eval(self.equation)
                self.display.delete(0, ctk.END)
                self.display.insert(0, str(resultat))
                self.equation = str(
                    resultat
                )  # Mettre à jour l'équation pour continuer les calculs
            except Exception as e:
                self.display.delete(0, ctk.END)
                self.display.insert(0, "Erreur")
                self.equation = ""
        else:
            # Ajouter le caractère à l'équation
            self.equation += caractere
            self.display.delete(0, ctk.END)
            self.display.insert(0, self.equation)


# Lancer l'application
if __name__ == "__main__":
    app = Calculatrice()
    app.mainloop()
