
# Cheatsheet sur les Structures de Données en C++

Ce cheatsheet couvre les principales structures de données en C++ et propose des exemples pratiques pour les utiliser : `std::list`, `std::vector`, `std::set`, `std::map`, `std::stack`, `std::queue`, `std::multiset`, et `std::multimap`.

---

## 1. std::list
### Description
Liste doublement chaînée. Permet des insertions et suppressions efficaces.

### Exemples :
```cpp
#include <list>
#include <iostream>
using namespace std;

int main() {
    list<int> myList = {1, 2, 3};
    myList.push_back(4); // Ajouter à la fin
    myList.push_front(0); // Ajouter au début

    myList.remove(2); // Supprimer la valeur 2

    for (int x : myList) {
        cout << x << " ";
    }
    return 0;
}
```
---

## 2. std::vector
### Description
Tableau dynamique avec accès rapide aux éléments par index.

### Exemples :
```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> myVector = {1, 2, 3};
    myVector.push_back(4); // Ajouter à la fin

    myVector[1] = 5; // Modifier l'élément à l'index 1

    myVector.pop_back(); // Supprimer le dernier élément

    for (int x : myVector) {
        cout << x << " ";
    }
    return 0;
}
```
---

## 3. std::set
### Description
Conteneur ordonné qui ne contient que des éléments uniques.

### Exemples :
```cpp
#include <set>
#include <iostream>
using namespace std;

int main() {
    set<int> mySet = {1, 2, 3};
    mySet.insert(4); // Insérer un élément
    mySet.erase(2); // Supprimer un élément

    for (int x : mySet) {
        cout << x << " ";
    }
    return 0;
}
```
---

## 4. std::map
### Description
Table associative clé-valeur.

### Exemples :
```cpp
#include <map>
#include <iostream>
using namespace std;

int main() {
    map<string, int> myMap;
    myMap["apple"] = 5; // Ajouter ou modifier
    myMap["banana"] = 2;

    myMap.erase("apple"); // Supprimer une clé

    for (auto &[key, value] : myMap) {
        cout << key << ": " << value << endl;
    }
    return 0;
}
```
---

## 5. std::stack
### Description
Pile (LIFO : dernier entré, premier sorti).

### Exemples :
```cpp
#include <stack>
#include <iostream>
using namespace std;

int main() {
    stack<int> myStack;
    myStack.push(1); // Ajouter un élément
    myStack.push(2);

    myStack.pop(); // Retirer le dernier élément

    cout << "Top element: " << myStack.top() << endl;
    return 0;
}
```
---

## 6. std::queue
### Description
File (FIFO : premier entré, premier sorti).

### Exemples :
```cpp
#include <queue>
#include <iostream>
using namespace std;

int main() {
    queue<int> myQueue;
    myQueue.push(1); // Ajouter un élément
    myQueue.push(2);

    myQueue.pop(); // Retirer le premier élément

    cout << "Front element: " << myQueue.front() << endl;
    return 0;
}
```
---

## 7. std::multiset
### Description
Conteneur ordonné qui permet des éléments dupliqués.

### Exemples :
```cpp
#include <set>
#include <iostream>
using namespace std;

int main() {
    multiset<int> myMultiset = {1, 2, 2, 3};
    myMultiset.insert(4); // Ajouter un élément
    myMultiset.erase(myMultiset.find(2)); // Supprimer un élément (une seule occurrence)

    for (int x : myMultiset) {
        cout << x << " ";
    }
    return 0;
}
```
---

## 8. std::multimap
### Description
Table associative clé-valeur qui permet des clés dupliquées.

### Exemples :
```cpp
#include <map>
#include <iostream>
using namespace std;

int main() {
    multimap<string, int> myMultimap;
    myMultimap.insert({"apple", 5});
    myMultimap.insert({"apple", 3}); // Clé dupliquée

    for (auto &[key, value] : myMultimap) {
        cout << key << ": " << value << endl;
    }
    return 0;
}
```
---

### Notes Générales
- Inclure les bons headers pour chaque conteneur.
- Adapter les structures de données aux besoins spécifiques en performance et contraintes.

