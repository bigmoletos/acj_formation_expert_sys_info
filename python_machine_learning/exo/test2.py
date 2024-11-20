import numpy as np
import matplotlib.pyplot as plt
import logging

# Configurer le logger
logger = logging.getLogger("notebook_logger")
logger.setLevel(logging.DEBUG)

console_handler = logging.StreamHandler()
formatter = logging.Formatter(
    '%(asctime)s - %(name)s - %(levelname)s - %(message)s')
console_handler.setFormatter(formatter)
logger.addHandler(console_handler)


def generate_random_array(size: int,
                          min_value: int = 0,
                          max_value: int = 1000) -> np.ndarray:
    """
    @brief Génère un tableau aléatoire d'entiers dans une plage donnée.

    @param size Le nombre d'éléments dans le tableau.
    @param min_value La valeur minimale des éléments du tableau (par défaut : 0).
    @param max_value La valeur maximale des éléments du tableau (par défaut : 1000).
    @return Un tableau numpy contenant des valeurs aléatoires entières.

    @example
    >>> array = generate_random_array(5, 0, 10)
    >>> len(array) == 5
    True
    """
    try:
        # Générer un tableau d'entiers aléatoires
        random_array = np.random.randint(min_value, max_value + 1, size)
        return random_array
    except Exception as e:
        raise ValueError(f"Erreur lors de la génération du tableau : {e}")


def plot_array(data: np.ndarray):
    """
    @brief Trace un graphique de la liste ou du tableau donné.

    @param data Le tableau ou la liste à tracer.

    @details Ce graphique montre les valeurs de la liste en fonction de leur indice.
    """
    try:
        plt.figure(figsize=(10, 6))
        plt.plot(data, marker='o', linestyle='-', label="Valeurs aléatoires")
        plt.title("Visualisation des valeurs aléatoires")
        plt.xlabel("Index")
        plt.ylabel("Valeurs")
        plt.legend()
        plt.grid(True)
        plt.show()
    except Exception as e:
        raise ValueError(f"Erreur lors de la création du graphique : {e}")


if __name__ == "__main__":
    """
    @brief Programme principal pour générer et tracer un tableau aléatoire.
    """
    # Taille du tableau
    size = 50  # Modifier cette valeur pour un tableau plus grand ou plus petit

    # Génération du tableau aléatoire
    random_array = generate_random_array(size)

    # Afficher les 10 premières valeurs pour vérification
    print("Tableau généré (10 premières valeurs) :", random_array[:10])

    # Tracer le tableau
    plot_array(random_array)
