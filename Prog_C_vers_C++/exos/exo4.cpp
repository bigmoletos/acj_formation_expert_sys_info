#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std ;
  int total;
/**
 * @brief [Description de sum]
 *
 * @param int [Description du paramètre]
 * @param int [Description du paramètre]
 * @return int [Description du retour]
 */
  int sum(  int,  int);

/**
 * @brief [Description de main]
 *
 * @param void [Description du paramètre]
 * @return int [Description du retour]
 */
int main(void){
    int a, b ;
    cout << "\n add function called, enter two numbers: " ;
    cin >> a  >> b ;
    total = sum(a,b);
    printf("\n sum: %d + %d = %d\n\n", a, b, total) ;
    return 0 ; }

 int sum (  int num1,  int num2){
     int result;
    result = num1 + num2 ;
    return (result) ; }



    //cout << " sum : " << a << " + " << b << " = " << total << endl;


