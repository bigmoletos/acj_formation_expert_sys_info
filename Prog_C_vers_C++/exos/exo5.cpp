#include <limits>
#include <iostream>

int main() {
    std::cout << CHAR_BIT << " bits in byte" << std::endl;
    std::cout << "min  SIGNED CHAR: " << SCHAR_MIN << std::endl;
    std::cout << "max  SIGNED CHAR: " << SCHAR_MAX << std::endl;
    std::cout << "max UNSIGNED CHAR: " << UCHAR_MAX << std::endl;

    /* others types */

    std::cout << "max ULONG INT: " << std::numeric_limits<unsigned long int>::max() << std::endl;
    std::cout << "max ULONG LONG INT: " << std::numeric_limits<unsigned long long int>::max() << std::endl;

    return 0;
}
