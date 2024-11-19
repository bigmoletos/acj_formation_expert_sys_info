#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std ;

/**
 * @brief [Description de main]
 *
 * @param void [Description du paramètre]
 * @return int [Description du retour]
 */
int main(void){

    bool           a = 123 ;
    int            b = a+2 ;
    double         c = a ;
    unsigned char d = -1 ;
    char e = 3.14159 ;
    int f  = 1.9999999999999999 ;
    int g  = -3.999999999 ;
    int h  = (int) 2.718281 ;
    int i  = (int) 1/a ;

    cout << "a: " << a << endl ;
    cout << "b: " << b << endl ;
    cout << "c: " << c << endl ;
    cout << "d: " << d << endl ;
    cout << "e: " << e << endl ;
    cout << "f: " << f << endl ;
    cout << "g: " << g << endl ;
    cout << "h: " << h << endl ;
    cout << "i: " << i << endl ;
}

