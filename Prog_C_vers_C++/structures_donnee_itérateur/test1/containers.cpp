#include "containers.h"

// Afficher les éléments d'un std::vector
void displayVector(const std::vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Afficher les éléments d'un std::list
void displayList(const std::list<std::string>& lst) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Afficher les éléments d'un std::set
void displaySet(const std::set<int>& s) {
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
