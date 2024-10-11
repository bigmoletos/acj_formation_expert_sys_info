import logging
import time
import psutil
import unittest

# Configuration du logger
logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger()


def fibonacci_iteratif(n):
    """
    Renvoie le nième nombre de Fibonacci en utilisant une approche itérative.

    :param n: L'indice du nombre de Fibonacci à calculer.
    :return: Le nième nombre de Fibonacci.

    >>> fibonacci_iteratif(5)
    5
    >>> fibonacci_iteratif(10)
    55
    """
    a = 0
    b = 1
    for _ in range(n):
        a, b = b, a + b
    return a


def fibonacci_recursif(n):
    """
    Renvoie le nième nombre de Fibonacci en utilisant une approche récursive.

    :param n: L'indice du nombre de Fibonacci à calculer.
    :return: Le nième nombre de Fibonacci.

    >>> fibonacci_recursif(5)
    5
    >>> fibonacci_recursif(10)
    55
    """
    if n <= 1:
        return n
    else:
        return fibonacci_recursif(n - 1) + fibonacci_recursif(n - 2)


def fibonacci_memo(n, memo={}):
    """
    Renvoie le nième nombre de Fibonacci en utilisant une approche récursive avec mémoïsation.

    :param n: L'indice du nombre de Fibonacci à calculer.
    :param memo: Dictionnaire utilisé pour mémoriser les résultats intermédiaires.
    :return: Le nième nombre de Fibonacci.

    >>> fibonacci_memo(5)
    5
    >>> fibonacci_memo(10)
    55
    """
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo)
    return memo[n]


def measure_performance(func, *args, **kwargs):
    """
    Mesure les performances en temps et en charge CPU d'une fonction donnée.

    :param func: La fonction à exécuter.
    :param args: Les arguments pour la fonction.
    :param kwargs: Les arguments nommés pour la fonction.
    :return: Le résultat de la fonction.
    """
    logger.info(f"Lancement de {func.__name__} avec les arguments {args}")

    # Mesurer le temps de départ
    start_time = time.time()

    # Mesurer l'utilisation CPU avant l'exécution
    cpu_start = psutil.cpu_percent(interval=None)

    # Exécuter la fonction
    result = func(*args, **kwargs)

    # Mesurer l'utilisation CPU après l'exécution
    cpu_end = psutil.cpu_percent(interval=None)

    # Calculer la différence de CPU et de temps
    cpu_usage = cpu_end - cpu_start
    execution_time = time.time() - start_time

    logger.info(
        f"Temps d'exécution de {func.__name__}: {execution_time:.4f} secondes")
    logger.info(
        f"Utilisation de la CPU pendant {func.__name__}: {cpu_usage:.2f}%")

    return result


# Test des performances pour différentes fonctions Fibonacci
if __name__ == "__main__":
    n = 50  # Un exemple pour tester la performance avec une valeur élevée de Fibonacci

    # Test avec la fonction itérative
    result_iteratif = measure_performance(fibonacci_iteratif, n)
    logger.debug(
        f"Résultat (Itératif) pour Fibonacci({n}) = {result_iteratif}")

    # Test avec la fonction récursive
    result_recursif = measure_performance(fibonacci_recursif, n)
    logger.debug(
        f"Résultat (Récursif) pour Fibonacci({n}) = {result_recursif}")

    # Test avec la fonction avec mémoïsation
    result_memo = measure_performance(fibonacci_memo, n, memo={})
    logger.debug(f"Résultat (Mémoïsation) pour Fibonacci({n}) = {result_memo}")


# Classe de tests unitaires pour s'assurer du bon fonctionnement des algorithmes
class TestFibonacci(unittest.TestCase):

    def test_fibonacci_iteratif(self):
        self.assertEqual(fibonacci_iteratif(5), 5)
        self.assertEqual(fibonacci_iteratif(10), 55)

    def test_fibonacci_recursif(self):
        self.assertEqual(fibonacci_recursif(5), 5)
        self.assertEqual(fibonacci_recursif(10), 55)

    def test_fibonacci_memo(self):
        self.assertEqual(fibonacci_memo(5), 5)
        self.assertEqual(fibonacci_memo(10), 55)


# if __name__ == "__main__":
#     # unittest.main()

#     fibonacci_memo(6, memo={})
