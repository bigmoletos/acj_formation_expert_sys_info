#include <iostream>

void print_array(int *, int);
void by_values(int a, int b);
void by_pointers(int *, int *);
void by_references(int &, int &);

int main(void)
{
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


void by_values(int a, int b)
{
    int res = (a + b) / 2;
    std::cout << a << ", " << b << " -> " << res << std::endl;
    a++;
    b++;
}

void by_pointers(int *a, int *b)
{
    int res = ((*a) + (*b)) / 2;
    std::cout << *a << ", " << *b << " -> " << res << std::endl;
    (*a)++;
    (*b)++;
}

void by_references(int &a, int &b)
{
    int res = (a + b) / 2;
    std::cout << a << ", " << b << " -> " << res << std::endl;
    a++;
    b++;
}

void print_array(int *T, int size)
{
    for (int k = 0; k < size; ++k)
    {
        std::cout << "T[" << k << "]: " << T[k] << " ";
    }
    std::cout << std::endl;
}
