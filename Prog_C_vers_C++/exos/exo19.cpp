#include <iostream>

// Fonction qui renvoie le maximum de deux entiers
int max(int a, int b)
{
    int max_res = (a > b) ? a : b;
    return max_res;
}

// Fonction qui renvoie le maximum de deux entiers
int max(int a, int b, int c)
{

    int max_res = max(a,max(b,c));
    return max_res;
}
// Fonction qui renvoie le maximum de deux entiers
int max(int a, int b, int c, int d)
{
    int max_res = max(a,max(c,b,d));
    return (a > b) ? a : b;
}


int max(int tab[], int size)
{
    int res = tab[0];
    for (int i = 1; i < size; ++i)
    {

    res=max(tab[i],res);
    }
}

//
void inverse(int &a, int &b);

int main()
{
    int a = 3, b = 7;
    std::cout << "a(" << a << ", " << &a << ") -- ";
    std::cout << "b(" << b << ", " << &b << ")" << std::endl;

    inverse(a, b);

    std::cout << "a(" << a << ", " << &a << ") -- ";
    std::cout << "b(" << b << ", " << &b << ")" << std::endl;
}

void inverse(int &a, int &b)
{
    int tmp = b;
    b = a;
    a = tmp;
}
//#include <iostream>
// exo 3
long long unsigned int factorial_i(int);
long long unsigned int factorial_r(int);

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

long long unsigned int factorial_i(int n)
{
    long long unsigned int res = 1;
    for (int i = 1; i < n + 1; i++)
        res *= i;
    return res;
}

long long unsigned int factorial_r(int n)
{
    return (n < 2) ? 1 : n * factorial_r(n - 1);
}

int main()
{
    int num1 = 10;
    int num2 = 6;
    int num3 = 54;
    int num4 = 26;

    // Appel de la fonction et affichage du résultat
    int max_number = max(num1, num2);
    std::cout << "Le maximum est : " << max_number << std::endl;

    return 0;
}