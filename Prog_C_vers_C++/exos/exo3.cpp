#include <iostream>

int main() {

   std::cout << " types size on this machine:"               << std::endl ;
   std::cout << " ==========================\n"              << std::endl ;

   std::cout << "BOOL          :  "   << sizeof(bool)            << std::endl ;
   std::cout << "CHAR          :  "   << sizeof(char)            << std::endl ;
   std::cout << "SHORT         :  "   << sizeof(short)           << std::endl ;
   std::cout << "wchar_t       :  "   << sizeof(wchar_t)         << std::endl ;
   std::cout << "char16_t      :  "   << sizeof(char16_t)        << std::endl ;
   std::cout << "char32_t      :  "   << sizeof(char32_t)        << std::endl ;
   std::cout << "INT           :  "   << sizeof(int)             << std::endl ;
   std::cout << "LONG          :  "   << sizeof(long)            << std::endl ;
   std::cout << "LONG LONG     :  "   << sizeof(long long)       << std::endl ;
   std::cout << "FLOAT         :  "   << sizeof(float)           << std::endl ;
   std::cout << "DOUBLE        :  "   << sizeof(double)          << std::endl ;
   std::cout << "LONG DOUBLE   :  "   << sizeof(long double)     << std::endl ;

   return 0 ;
}