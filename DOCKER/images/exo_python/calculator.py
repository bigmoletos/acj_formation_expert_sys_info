"""
Calculator library containing basic math operations.
"""


def addition(first_term: float = 5, second_term: float = 10) -> float:
    """
    Adds two numbers.

    Args:
        first_term (float): The first number.
        second_term (float): The second number.

    Returns:
        float: The sum of the two numbers.
    """
    result = first_term + second_term
    print(f"\nresultat addition :\n{result} \n")
    return result


def soustraction(first_term: float = 80, second_term: float = 5) -> float:
    """
    Subtracts the second number from the first.

    Args:
        first_term (float): The number to subtract from.
        second_term (float): The number to subtract.

    Returns:
        float: The result of the subtraction.
    """
    result = first_term - second_term
    print(f"\nresultat soustraction :\n{result} \n")
    return result


def main():
    """
    Main function to execute calculator operations.
    """
    addition()
    soustraction()


if __name__ == "__main__":
    main()
