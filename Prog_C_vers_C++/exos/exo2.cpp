#include <stdio.h>

int main(int argc, char const *argv[]){
   unsigned int first  =  10 ;
   signed int second = -10 ;

   if      (first == second) printf("%+3d = %+3d\n", first, second) ;
   else if (first  > second) printf("%+3d < %+3d\n", first, second) ;
   else                      printf("%+3d > %+3d\n", first, second) ;
   }