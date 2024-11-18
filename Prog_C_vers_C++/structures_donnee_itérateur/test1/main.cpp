#include "containers.h"

int main() {
    // Vector
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::cout << "Vector: ";
    displayVector(v);

    // List
    std::list<std::string> lst = {"hello", "world"};
    std::cout << "List: ";
    displayList(lst);

    // Set
    std::set<int> s = {3, 1, 4};
    std::cout << "Set: ";
    displaySet(s);

    return 0;
}
