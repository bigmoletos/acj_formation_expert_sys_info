#include <stdio.h>

/**
 * @brief [Description de main]
 *
 * @param argc [Description du param�tre]
 * @param *argv[] [Description du param�tre]
 * @return int [Description du retour]
 */
int main(int argc, char const *argv[]){
   unsigned int first  =  10 ;
   signed int second = -10 ;

   if      (first == second) printf("%+3d = %+3d\n", first, second) ;
   else if (first  > second) printf("%+3d < %+3d\n", first, second) ;
/**
 * @brief [Description de printf]
 *
 * @param %+3d\n" [Description du param�tre]
 * @param first [Description du param�tre]
 * @param second [Description du param�tre]
 * @return else [Description du retour]
 */
   else                      printf("%+3d > %+3d\n", first, second) ;
   }