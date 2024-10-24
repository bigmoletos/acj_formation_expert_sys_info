#include <iostream>
#include <climits>
#include <cfloat>

using namespace std;

int main( ) {

   cout << "The number of bits in a byte            = "  << CHAR_BIT       << endl << endl;

   cout << "minimum SIGNED CHAR                     = "  << SCHAR_MIN      << endl;
   cout << "maximum SIGNED CHAR                     = "  << SCHAR_MAX      << endl;
   cout << "maximum UNSIGNED CHAR                   = "  << UCHAR_MAX      << endl << endl;

   cout << "minimum SHORT INT                       = "  << SHRT_MIN       << endl;
   cout << "maximum SHORT INT                       = "  << SHRT_MAX       << endl;
   cout << "maximum UNSIGNED SHORT INT              = "  << USHRT_MAX      << endl << endl;

   cout << "The minimum value of INT                = "  << INT_MIN        << endl;
   cout << "The maximum value of INT                = "  << INT_MAX        << endl;
   cout << "The maximum value of USIGNED INT        = "  << UINT_MAX       << endl << endl;

   cout << "The minimum value of CHAR               = "  << CHAR_MIN       << endl;
   cout << "The maximum value of CHAR               = "  << CHAR_MAX       << endl;
   cout << "The maximum value of UNSIGNED CHAR      = "  << UCHAR_MAX      << endl << endl;

   cout << "The minimum value of LONG               = "  << LONG_MIN       << endl;
   cout << "The maximum value of LONG               = "  << LONG_MAX       << endl;
   cout << "The maximum value of UNSIGNED LONG      = "  << ULONG_MAX      << endl << endl;

   cout << "The minimum value of LONG LONG          = "  << LLONG_MIN      << endl;
   cout << "The maximum value of LONG LONG          = "  << LLONG_MAX      << endl;
   cout << "The maximum value of UNSIGNED LONG LONG = "  << ULONG_MAX      << endl << endl;

   cout << "The minimum value of POSITIVE FLOAT     = "  << FLT_MIN        << endl;
   cout << "The maximum value of POSITIVE FLOAT     = "  << FLT_MAX        << endl;
   cout << "The minimum EPSILON value for FLOAT     = "  << FLT_EPSILON    << endl << endl;

   cout << "The minimum value of POSITIVE DOUBLE     = " << DBL_MIN        << endl;
   cout << "The maximum value of POSITIVE DOUBLE     = " << DBL_MAX        << endl;
   cout << "The minimum EPSILON value for DOUBLE     = " << DBL_EPSILON    << endl << endl;

   cout << "The minimum value of POSITIVE DOUBLE     = " << LDBL_MIN       << endl;
   cout << "The maximum value of POSITIVE DOUBLE     = " << LDBL_MAX       << endl;
   cout << "The minimum EPSILON value for DOUBLE     = " << LDBL_EPSILON   << endl << endl;

   return 0 ;

}