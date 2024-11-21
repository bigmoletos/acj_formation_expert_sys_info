# import sys
import sys
import logging
# Objectif :
# Créer un script Python qui accepte des arguments depuis la ligne de commande pour effectuer une opération mathématique (somme ou produit) sur deux nombres.

# Consignes :
# - Nom du script : calculateur.py
# Le script doit être capable de :
# - Accepter 3 arguments depuis la ligne de commande :
# - Une opération à effectuer : "somme" ou "produit".
# - Deux nombres (par exemple : 5 et 10).
# - Vérifier que l'utilisateur fournit bien les arguments nécessaires.
# - Vérifier que les deux nombres sont valides (convertibles en nombres).
# - Effectuer l'opération demandée et afficher le résultat.
# - Afficher un message d'aide si les arguments sont incorrects ou incomplets.
# Instructions détaillées :
# - Commencez par importer le module sys.
# - Vérifiez que l'utilisateur fournit exactement 3 arguments (en plus du nom du script).
# - Récupérez les arguments :
# - Le premier argument doit être l'opération (somme ou produit).
# - Les deux suivants doivent être des nombres.

# Si les arguments sont incorrects :
# - Affichez un message d'erreur indiquant le bon format d'utilisation du script.
# Exemple de message :
# ```Usage : python calculateur.py <operation> <nombre1> <nombre2>
# Exemple : python calculateur.py somme 5 10
# ```

# Vérifier le nombre d'arguments

# Configurer le logger
logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s - %(levelname)s - %(message)s",
    handlers=[logging.FileHandler("script.log"),
              logging.StreamHandler()])
logger = logging.getLogger(__name__)


# Définir les fonctions
## @brief Affiche un message d'aide pour l'utilisation correcte du script.
def afficher_aide():
    """
    Affiche un message d'aide expliquant comment utiliser le script.
    """
    aide = """
    Usage :
        python calculateur.py <operation> <nombre1> <nombre2>

    Description :
        Ce script permet d'effectuer une opération mathématique sur deux nombres.

    Arguments :
        <operation>    L'opération à effectuer : 'somme' ou 'produit'.
        <nombre1>      Le premier nombre entier.
        <nombre2>      Le deuxième nombre entier.

    Exemple :
        python calculateur.py somme 5 10
        python calculateur.py produit 3 4
    """
    print(aide)
    logger.info("Aide affichée à l'utilisateur.")


## @brief Calcule la somme de deux entiers.
#  @param a Un entier.
#  @param b Un entier.
#  @return La somme de a et b.
def somme(a: int, b: int) -> int:
    return a + b


## @brief Calcule le produit de deux entiers.
#  @param a Un entier.
#  @param b Un entier.
#  @return Le produit de a et b.
def produit(a: int, b: int) -> int:
    return a * b


## @brief Effectue une opération sur deux entiers.
#  @param a Un entier.
#  @param b Un entier.
#  @param operation Une chaîne de caractères représentant l'opération ("SOMME" ou "PRODUIT").
#  @return Le résultat de l'opération.
#  @throws ValueError Si l'opération n'est pas reconnue.
def calculateur(a: int, b: int, operation: str) -> int:
    try:
        operation = operation.upper()  # Mettre l'opération en majuscule
        if operation == "SOMME":
            resultat = somme(a, b)
            logger.debug(f"Calcul de la somme : {a} + {b} = {resultat}")
        elif operation == "PRODUIT":
            resultat = produit(a, b)
            logger.debug(f"Calcul du produit : {a} * {b} = {resultat}")
        else:
            raise ValueError(
                "Opération non reconnue. Utilisez 'SOMME' ou 'PRODUIT'.")
        return resultat
    except Exception as e:
        logger.error(f"Erreur dans calculateur : {e}")
        raise


# Lecture des arguments et exécution
try:
    ## @brief Point d'entrée principal du script.
    #  Vérifie les arguments passés et effectue une opération mathématique.
    #
    #  @throws ValueError Si le nombre d'arguments est insuffisant ou si les types sont incorrects.
    # Vérifier si l'utilisateur demande l'aide
    if len(sys.argv) > 1 and sys.argv[1] in ["-h", "--help"]:
        afficher_aide()
        sys.exit(0)
    if len(sys.argv) <= 3:
        raise ValueError(
            "Il manque des arguments. Usage : script.py <entier1> <entier2> <operation>"
        )
    elif len(sys.argv) == 4:
        logger.info("Nombre d'arguments valides.")

    print("\nTous les arguments :")
    for i, arg in enumerate(sys.argv):
        print(f"Argument {i}: {arg}")

    try:
        ## @var a
        #  Premier entier passé en argument.
        a = int(sys.argv[1])

        ## @var b
        #  Deuxième entier passé en argument.
        b = int(sys.argv[2])

        ## @var operation
        #  L'opération à effectuer ("SOMME" ou "PRODUIT").
        operation = sys.argv[3]
    except ValueError as e:
        logger.error(
            f"Les arguments doivent être des entiers pour a et b. Erreur : {e}"
        )
        raise

    # Appel de la fonction calculateur
    try:
        resultat = calculateur(a, b, operation)
        print(f"Résultat : {resultat}")
    except Exception as e:
        logger.error(f"Erreur lors du calcul : {e}")

except ValueError as e:
    logger.error(f"Erreur de validation des arguments : {e}")
except IndexError as e:
    logger.error(f"Erreur : Arguments insuffisants. {e}")
except Exception as e:
    logger.critical(f"Erreur inattendue : {e}")
