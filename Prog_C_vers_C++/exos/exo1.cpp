#include <stdio.h>
#include <stdlib.h>

static const int expected_uid = 1234 , expected_gid = 4321 ;

/**
 * @brief [Description de leave_access]
 *
 * @param uid [Description du paramètre]
 * @param gid [Description du paramètre]
 * @return int [Description du retour]
 */
int leave_access(const int uid, const int gid){
if (gid != expected_gid) return 2 ;
if (uid != expected_gid) return 1 ;
return 0 ;
}

/**
 * @brief [Description de main]
 *
 * @param argc [Description du paramètre]
 * @param *argv[] [Description du paramètre]
 * @return int [Description du retour]
 */
int main(int argc, char const *argv[]){
   if ( 0 != leave_access(1001, 2002)) {
   printf("access not given for you! contact administrator\n"); exit(1); }
   return 0;
}