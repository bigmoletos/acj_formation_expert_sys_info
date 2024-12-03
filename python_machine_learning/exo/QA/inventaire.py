"""
Exercice de QA
classe python réalisée pour la gestion de l'inventaire d'un magasin.

Les fonctionnalités incluent :

- Ajout d'un produit avec des vérifications (nom unique, stock positif).
- Suppression d'un produit en vérifiant son existence.
- Consultation d'un produit avec affichage des détails.
- Mise à jour du stock avec des vérifications (quantité non négative).
- Calcul du stock total et affichage des produits en dessous d'un certain seuil.
"""

from typing import Dict, List
import logging

# Configuration du logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class ProductNotFoundError(Exception):
    """Exception levée lorsque le produit n'est pas trouvé dans l'inventaire."""
    pass


class InvalidStockError(Exception):
    """Exception levée lorsque le stock fourni est invalide."""
    pass


class Inventory:
    """
    Classe Inventory pour gérer les produits d'un magasin.
    """

    def __init__(self) -> None:
        """
        Initialise l'inventaire avec un dictionnaire vide.
        """
        self.products: Dict[str, int] = {}

    def add_product(self, name: str, stock: int) -> None:
        """
        Ajoute un produit à l'inventaire.
        Lève une InvalidStockError si le stock est négatif.

        :param name: Nom du produit (str)
        :param stock: Quantité initiale en stock (int)
        :raises InvalidStockError: Si le stock est négatif
        """
        if stock < 0:
            raise InvalidStockError("Le stock ne peut pas être négatif")

        if name not in self.products:
            self.products[name] = stock
            logger.info(f"Produit '{name}' ajouté avec un stock de {stock}")

    def remove_product(self, name: str) -> None:
        """
        Supprime un produit de l'inventaire.

        :param name: Nom du produit à supprimer (str)
        :raises ProductNotFoundError: Si le produit n'existe pas
        """
        if name not in self.products:
            raise ProductNotFoundError(
                f"Produit '{name}' non trouvé dans l'inventaire")

        del self.products[name]
        logger.info(f"Produit '{name}' supprimé de l'inventaire")

    def update_stock(self, product_name: str, new_stock: int) -> None:
        """
        Met à jour le stock d'un produit.

        :param product_name: Nom du produit (str)
        :param new_stock: Nouvelle quantité en stock (int)
        :raises ProductNotFoundError: Si le produit n'existe pas
        :raises InvalidStockError: Si le nouveau stock est négatif
        """
        if product_name not in self.products:
            raise ProductNotFoundError(
                f"Produit '{product_name}' non trouvé dans l'inventaire")

        if new_stock < 0:
            raise InvalidStockError("Le stock ne peut pas être négatif")

        self.products[product_name] = new_stock
        logger.info(
            f"Stock du produit '{product_name}' mis à jour à {new_stock}")

    def get_product(self, name: str) -> int:
        """
        Retourne le stock d'un produit.

        :param name: Nom du produit (str)
        :return: Stock du produit (int)
        :raises ProductNotFoundError: Si le produit n'existe pas
        """
        if name not in self.products:
            raise ProductNotFoundError(
                f"Produit '{name}' non trouvé dans l'inventaire")

        return self.products[name]

    def low_stock_products(self, threshold: int) -> List[str]:
        """
        Retourne la liste des produits ayant un stock inférieur au seuil.

        :param threshold: Seuil de stock (int)
        :return: Liste des noms de produits en stock faible
        :raises InvalidStockError: Si le seuil est négatif
        """
        if threshold < 0:
            raise InvalidStockError("Le seuil ne peut pas être négatif")

        return [
            product for product, stock in self.products.items()
            if stock < threshold
        ]

    def total_stock(self) -> int:
        """
        Calcule le stock total de l'inventaire.

        :return: Stock total (int)
        """
        return sum(self.products.values())
