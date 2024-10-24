#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std ;
  int total;
  int sum(  int,  int);

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


