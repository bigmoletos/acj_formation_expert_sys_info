#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <string>

/**
 * @brief Effectue un calcul générique entre deux valeurs.
 *
 * Cette fonction additionne deux valeurs de types potentiellement différents
 * et utilise `decltype` pour déduire dynamiquement le type de retour.
 *
 * @tparam T1 Type du premier argument
 * @tparam T2 Type du second argument
 * @param a Première valeur
 * @param b Seconde valeur
 * @return Type résultant déduit dynamiquement par `decltype(a + b)`
 */
template <typename T1, typename T2>
auto calculate(T1 a, T2 b) -> decltype(a + b)
{
    return a + b; // Effectuer l'addition et retourner le résultat
}

/**
 * @brief Affiche un message en fonction du type du résultat.
 *
 * Cette fonction utilise `decltype` pour capturer le type de la valeur et
 * `typeid` pour obtenir des informations sur le type réel. Elle affiche un
 * message selon que le résultat est un `float`, un `double`, ou tout autre type.
 *
 * @tparam T Type du résultat à analyser
 * @param result Résultat de type générique à analyser
 */

template <typename T>
void displayResult(T result)
{
    // Capturer dynamiquement le type du résultat avec decltype
    using ResultType = decltype(result);

    // Vérification du type à la compilation avec if constexpr
    if constexpr (std::is_same_v<ResultType, float>)
    {
        std::cout << "Le résultat est un float." << std::endl;
    }
    else if constexpr (std::is_same_v<ResultType, double>)
    {
        std::cout << "Le résultat est un double." << std::endl;
    }
    else
    {
        // Utiliser typeid pour afficher le type réel dans tous les autres cas
        std::cout << "Le type du résultat est : " << typeid(ResultType).name() << std::endl;
    }
}

int main()
{
    /**
     * Test avec des valeurs de type float
     */
    float f1 = 1.5f, f2 = 2.5f;
    auto resultFloat = calculate(f1, f2); // Type déduit : float
    displayResult(resultFloat);           // Affiche : Le résultat est un float.

    /**
     * Test avec des valeurs de type double
     */
    double d1 = 1.111111, d2 = 2.222222;
    auto resultDouble = calculate(d1, d2); // Type déduit : double
    displayResult(resultDouble);           // Affiche : Le résultat est un double.

    /**
     * Test avec des types mixtes (float et double)
     */
    auto resultMixed = calculate(f1, d2); // Type déduit : double
    displayResult(resultMixed);           // Affiche : Le résultat est un double.

    /**
     * Test avec des objets de type std::string
     */
    std::string s1 = "Hello, ", s2 = "World!";
    auto resultString = calculate(s1, s2); // Type déduit : std::string
    displayResult(resultString);           // Affiche : Le type du résultat est : <type mangled>

    return 0;
}
