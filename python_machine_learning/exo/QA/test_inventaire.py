import logging
import unittest
from inventaire import Inventory, ProductNotFoundError, InvalidStockError

# Configuration du logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


# Tests unitaires
class TestInventory(unittest.TestCase):

    def setUp(self):
        """
        Méthode exécutée avant chaque test.
        Initialise l'inventaire avec des produits de base pour les tests.
        """
        try:
            self.inventory: Inventory = Inventory()
            self.inventory.add_product("Seidge", 50)
            self.inventory.add_product("Peutes", 30)
            self.inventory.add_product("Pheasanttail", 20)
        except InvalidStockError as e:
            logger.error(
                f"Erreur lors de l'initialisation de l'inventaire: {str(e)}")
            raise

    def test_add_product(self):
        """
        Test de l'ajout d'un produit.
        Vérifie les cas valides et invalides.
        """
        try:
            self.inventory.add_product("perdigonnes", 15)
            self.assertEqual(self.inventory.get_product("perdigonnes"), 15)

            # Test avec stock négatif
            with self.assertRaises(InvalidStockError):
                self.inventory.add_product("test_negatif", -5)

        except Exception as e:
            logger.error(f"Erreur lors du test d'ajout de produit: {str(e)}")
            raise

    def test_update_stock(self):
        """
        Test de la mise à jour de la quantité en stock d'un produit.
        Vérifie les cas valides et la gestion des erreurs.
        """
        try:
            name = "Pheasanttail"
            new_stock = 25
            self.inventory.update_stock(name, new_stock)
            self.assertEqual(self.inventory.get_product(name), new_stock)

            # Test avec un produit inexistant
            with self.assertRaises(ProductNotFoundError):
                self.inventory.update_stock("produit_inexistant", 10)

        except Exception as e:
            logger.error(
                f"Erreur lors du test de mise à jour du stock: {str(e)}")
            raise

    def test_get_product(self):
        """
        Test de la récupération du stock d'un produit.
        Vérifie la gestion des produits existants et inexistants.
        """
        try:
            name = "Pheasanttail"
            stock = self.inventory.get_product(name)
            self.assertEqual(stock, 20)

            # Test avec un produit inexistant
            with self.assertRaises(ProductNotFoundError):
                self.inventory.get_product("produit_inexistant")

        except Exception as e:
            logger.error(
                f"Erreur lors du test de récupération de produit: {str(e)}")
            raise

    def test_low_stock_products(self):
        """
        Teste la détection des produits ayant un stock faible.
        Vérifie que la liste des produits en dessous d'un seuil est correcte.
        """
        try:
            self.inventory.update_stock("Peutes", 10)
            self.inventory.update_stock("Seidge", 40)

            threshold = 15
            low_stock: list[str] = self.inventory.low_stock_products(threshold)
            self.assertIn("Peutes", low_stock)
            self.assertNotIn("Seidge", low_stock)

            # Test avec seuil négatif
            with self.assertRaises(InvalidStockError):
                self.inventory.low_stock_products(-5)

        except Exception as e:
            logger.error(
                f"Erreur lors du test des produits en stock faible: {str(e)}")
            raise

    def test_total_stock(self):
        """
        Teste le calcul du stock total de l'inventaire.
        Vérifie que le total des stocks est calculé correctement.
        """
        try:
            expected_total = 50 + 30 + 20  # Seidge + Peutes + Pheasanttail
            total = self.inventory.total_stock()
            self.assertEqual(total, expected_total)

        except Exception as e:
            logger.error(
                f"Erreur lors du test du calcul du stock total: {str(e)}")
            raise


if __name__ == "__main__":
    try:
        unittest.main(argv=['first-arg-is-ignored'], exit=False)
    except Exception as e:
        logger.error(f"Erreur lors de l'exécution des tests: {str(e)}")
