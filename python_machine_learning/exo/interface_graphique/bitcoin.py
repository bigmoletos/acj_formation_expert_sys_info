import requests
import customtkinter as ctk
from datetime import datetime


class BitcoinTracker(ctk.CTk):

    def __init__(self):
        super().__init__()
        self.title("Bitcoin Price Tracker")
        self.geometry("400x200")

        # Titre
        self.label_title = ctk.CTkLabel(self,
                                        text="Bitcoin Price Tracker",
                                        font=("Arial", 20, "bold"))
        self.label_title.pack(pady=10)

        # Zone pour afficher le prix
        self.label_price = ctk.CTkLabel(self,
                                        text="Fetching...",
                                        font=("Arial", 30))
        self.label_price.pack(pady=20)

        # Bouton pour rafraîchir le prix
        self.refresh_button = ctk.CTkButton(self,
                                            text="Refresh",
                                            command=self.update_price)
        self.refresh_button.pack(pady=10)

        # Zone pour afficher l'heure de mise à jour
        self.label_update_time = ctk.CTkLabel(self,
                                              text="",
                                              font=("Arial", 12))
        self.label_update_time.pack()

        # Mise à jour initiale
        self.update_price()

    def get_bitcoin_price(self):
        """
        Récupère le prix actuel du Bitcoin en USD en utilisant l'API CoinGecko.
        """
        try:
            url = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd"
            response = requests.get(url, timeout=10)
            response.raise_for_status()
            data = response.json()
            return data["bitcoin"]["usd"]
        except Exception as e:
            return f"Error: {e}"

    def update_price(self):
        """
        Met à jour l'affichage du prix du Bitcoin et l'heure de mise à jour.
        """
        price = self.get_bitcoin_price()
        if isinstance(price, str) and price.startswith("Error"):
            self.label_price.configure(text=price)
        else:
            self.label_price.configure(
                text=f"${price:,}")  # Formater le prix avec des virgules
            now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            self.label_update_time.configure(text=f"Last updated: {now}")


if __name__ == "__main__":
    app = BitcoinTracker()
    app.mainloop()
