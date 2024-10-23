#include <stdio.h>
#include <stdlib.h>

static const int expected_uid = 1234 , expected_gid = 4321 ;

int leave_access(const int uid, const int gid){
if (gid != expected_gid) return 2 ;
if (uid != expected_gid) return 1 ;
return 0 ;
}

int main(int argc, char const *argv[]){
   if ( 0 != leave_access(1001, 2002)) {
   printf("access not given for you! contact administrator\n"); exit(1); }
   return 0;
}