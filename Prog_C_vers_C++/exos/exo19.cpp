#include <iostream>

// Fonction qui renvoie le maximum de deux entiers
/**
 * @brief [Description de max]
 *
 * @param a [Description du paramètre]
 * @param b [Description du paramètre]
 * @return int [Description du retour]
 */
int max(int a, int b)
{
    int max_res = (a > b) ? a : b;
    return max_res;
}

// Fonction qui renvoie le maximum de deux entiers
/**
 * @brief [Description de max]
 *
 * @param a [Description du paramètre]
 * @param b [Description du paramètre]
 * @param c [Description du paramètre]
 * @return int [Description du retour]
 */
int max(int a, int b, int c)
{

    int max_res = max(a,max(b,c));
    return max_res;
}
// Fonction qui renvoie le maximum de deux entiers
/**
 * @brief [Description de max]
 *
 * @param a [Description du paramètre]
 * @param b [Description du paramètre]
 * @param c [Description du paramètre]
 * @param d [Description du paramètre]
 * @return int [Description du retour]
 */
int max(int a, int b, int c, int d)
{
    int max_res = max(a,max(c,b,d));
    return (a > b) ? a : b;
}


/**
 * @brief [Description de max]
 *
 * @param tab[] [Description du paramètre]
 * @param size [Description du paramètre]
 * @return int [Description du retour]
 */
int max(int tab[], int size)
{
    int res = tab[0];
    for (int i = 1; i < size; ++i)
    {

    res=max(tab[i],res);
    }
}

//
/**
 * @brief [Description de inverse]
 *
 * @param &a [Description du paramètre]
 * @param &b [Description du paramètre]
 * @return void [Description du retour]
 */
void inverse(int &a, int &b);

/**
 * @brief [Description de main]
 *
 * @param Aucun [Cette fonction n'a pas de paramètres]
 * @return int [Description du retour]
 */
int main()
{
    int a = 3, b = 7;
    std::cout << "a(" << a << ", " << &a << ") -- ";
    std::cout << "b(" << b << ", " << &b << ")" << std::endl;

    inverse(a, b);

    std::cout << "a(" << a << ", " << &a << ") -- ";
    std::cout << "b(" << b << ", " << &b << ")" << std::endl;
}

/**
 * @brief [Description de inverse]
 *
 * @param &a [Description du paramètre]
 * @param &b [Description du paramètre]
 * @return void [Description du retour]
 */
void inverse(int &a, int &b)
{
    int tmp = b;
    b = a;
    a = tmp;
}
//#include <iostream>
// exo 3
/**
 * @brief [Description de factorial_i]
 *
 * @param int [Description du paramètre]
 * @return long long unsigned int [Description du retour]
 */
long long unsigned int factorial_i(int);
/**
 * @brief [Description de factorial_r]
 *
 * @param int [Description du paramètre]
 * @return long long unsigned int [Description du retour]
 */
long long unsigned int factorial_r(int);

/**
 * @brief [Description de main]
 *
 * @param argc [Description du paramètre]
 * @param *argv[] [Description du paramètre]
 * @return int [Description du retour]
 */
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "wrong use" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]);
    std::cout << n << "! = " << factorial_i(n) << std::endl;
    std::cout << n << "! = " << factorial_r(n) << std::endl;
}

/**
 * @brief [Description de factorial_i]
 *
 * @param n [Description du paramètre]
 * @return long long unsigned int [Description du retour]
 */
long long unsigned int factorial_i(int n)
{
    long long unsigned int res = 1;
    for (int i = 1; i < n + 1; i++)
        res *= i;
    return res;
}

/**
 * @brief [Description de factorial_r]
 *
 * @param n [Description du paramètre]
 * @return long long unsigned int [Description du retour]
 */
long long unsigned int factorial_r(int n)
{
    return (n < 2) ? 1 : n * factorial_r(n - 1);
}

/**
 * @brief [Description de main]
 *
 * @param Aucun [Cette fonction n'a pas de paramètres]
 * @return int [Description du retour]
 */
int main()
{
    int num1 = 10;
    int num2 = 6;
    int num3 = 54;
    int num4 = 26;

    // Appel de la fonction et affichage du rÃ©sultat
    int max_number = max(num1, num2);
    std::cout << "Le maximum est : " << max_number << std::endl;

    return 0;
}