#include <stdio.h>

/**
 * @brief [Description de main]
 *
 * @param argc [Description du paramètre]
 * @param *argv[] [Description du paramètre]
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
 * @param %+3d\n" [Description du paramètre]
 * @param first [Description du paramètre]
 * @param second [Description du paramètre]
 * @return else [Description du retour]
 */
   else                      printf("%+3d > %+3d\n", first, second) ;
   }