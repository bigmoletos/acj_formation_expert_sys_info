#include <iostream>

/**
 * @brief [Description de print_array]
 *
 * @param * [Description du param�tre]
 * @param int [Description du param�tre]
 * @return void [Description du retour]
 */
void print_array(int *, int);
/**
 * @brief [Description de by_values]
 *
 * @param a [Description du param�tre]
 * @param b [Description du param�tre]
 * @return void [Description du retour]
 */
void by_values(int a, int b);
/**
 * @brief [Description de by_pointers]
 *
 * @param * [Description du param�tre]
 * @param * [Description du param�tre]
 * @return void [Description du retour]
 */
void by_pointers(int *, int *);
/**
 * @brief [Description de by_references]
 *
 * @param & [Description du param�tre]
 * @param & [Description du param�tre]
 * @return void [Description du retour]
 */
void by_references(int &, int &);

/**
 * @brief [Description de main]
 *
 * @param void [Description du param�tre]
 * @return int [Description du retour]
 */
int main(void)
{
/**
 * @brief [Description de size]
 *
 * @param 7 [Description du param�tre]
 * @return const int [Description du retour]
 */
    const int size(7);
    int tab[size] = {11, 22, 33, 44, 55, 66, 77};
    int *p = tab;
    int *q = tab + 13;

    print_array(p, size);
    print_array(q, size);

    by_values(tab[0], *q);
    print_array(tab, size);

    by_pointers(p, q);
    print_array(tab, size);

    by_pointers(&tab[3], &tab[3]);
    print_array(tab, size);

    by_references(tab[4], *(q - 1));
    print_array(tab, size);
}


/**
 * @brief [Description de by_values]
 *
 * @param a [Description du param�tre]
 * @param b [Description du param�tre]
 * @return void [Description du retour]
 */
void by_values(int a, int b)
{
    int res = (a + b) / 2;
    std::cout << a << ", " << b << " -> " << res << std::endl;
    a++;
    b++;
}

/**
 * @brief [Description de by_pointers]
 *
 * @param *a [Description du param�tre]
 * @param *b [Description du param�tre]
 * @return void [Description du retour]
 */
void by_pointers(int *a, int *b)
{
    int res = ((*a) + (*b)) / 2;
    std::cout << *a << ", " << *b << " -> " << res << std::endl;
    (*a)++;
    (*b)++;
}

/**
 * @brief [Description de by_references]
 *
 * @param &a [Description du param�tre]
 * @param &b [Description du param�tre]
 * @return void [Description du retour]
 */
void by_references(int &a, int &b)
{
    int res = (a + b) / 2;
    std::cout << a << ", " << b << " -> " << res << std::endl;
    a++;
    b++;
}

/**
 * @brief [Description de print_array]
 *
 * @param *T [Description du param�tre]
 * @param size [Description du param�tre]
 * @return void [Description du retour]
 */
void print_array(int *T, int size)
{
    for (int k = 0; k < size; ++k)
    {
        std::cout << "T[" << k << "]: " << T[k] << " ";
    }
    std::cout << std::endl;
}
