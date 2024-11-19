
# Cheatsheet : Principales fonctions STL en C++

https://en.cppreference.com/w/cpp/standard_library

## 1. **std::sort**
Trie une plage d'éléments dans l'ordre croissant ou selon un critère personnalisé.

### Prototype :
```cpp
template<class RandomIt>
void sort(RandomIt first, RandomIt last);
template<class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp);
```

### Explications détaillées :
- `std::sort` utilise l'algorithme "introsort", combinant quicksort, heapsort et insertion sort.
- Trie les éléments entre les itérateurs `first` et `last` en place (sans mémoire supplémentaire).
- Par défaut, l'ordre est croissant. Avec un comparateur, l'ordre est défini selon vos besoins.
- Nécessite des itérateurs aléatoires (`std::vector`, `std::deque`, etc.).
- Complexité : O(n log n).

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {5, 3, 9, 1, 4};
    std::sort(v.begin(), v.end());

    for (int n : v) {
        std::cout << n << " "; // 1 3 4 5 9
    }
    return 0;
}
```

---

## 2. **std::find**
Recherche la première occurrence d'une valeur donnée dans une plage.

### Prototype :
```cpp
template<class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& value);
```

### Explications détaillées :
- Cherche séquentiellement `value` dans `[first, last)`.
- Retourne un itérateur sur la première occurrence, ou `last` si introuvable.
- Complexité linéaire (O(n)) : examine chaque élément jusqu'à trouver la valeur ou atteindre la fin.
- Compatible avec `std::vector`, `std::list`, `std::deque`, etc.
- Idéal pour des recherches rapides dans des conteneurs.

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto it = std::find(v.begin(), v.end(), 30);

    if (it != v.end()) {
        std::cout << "Valeur trouvée à l'index : " << std::distance(v.begin(), it) << std::endl;
    } else {
        std::cout << "Valeur non trouvée" << std::endl;
    }
    return 0;
}
```

---

## 3. **std::unique**
Supprime les doublons consécutifs dans une plage.

### Prototype :
```cpp
template<class ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last);
template<class ForwardIt, class BinaryPredicate>
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p);
```

### Explications détaillées :
- Réorganise les éléments pour déplacer les valeurs uniques au début de la plage.
- Retourne un itérateur indiquant la fin logique de la plage modifiée.
- Les doublons doivent être consécutifs, donc utiliser `std::sort` au préalable est courant.
- Avec un prédicat binaire, vous pouvez personnaliser la logique de comparaison.
- Complexité : O(n).

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 1, 2, 3, 3, 3, 4, 4};
    auto it = std::unique(v.begin(), v.end());
    v.erase(it, v.end());

    for (int n : v) {
        std::cout << n << " "; // 1 2 3 4
    }
    return 0;
}
```

---

## 4. **std::accumulate**
Calcule la somme (ou une accumulation personnalisée) des éléments dans une plage.

### Prototype :
```cpp
template<class InputIt, class T>
T accumulate(InputIt first, InputIt last, T init);
template<class InputIt, class T, class BinaryOperation>
T accumulate(InputIt first, InputIt last, T init, BinaryOperation op);
```

### Explications détaillées :
- Additionne les éléments de `[first, last)` en commençant par `init`.
- Retourne un résultat basé sur l'accumulation ou une opération binaire personnalisée.
- Ne modifie pas la plage d'entrée.
- Complexité linéaire (O(n)).
- Utile pour des réductions comme somme, produit, ou calculs personnalisés.

### Exemple avec un vecteur :
```cpp
#include <numeric>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    int sum = std::accumulate(v.begin(), v.end(), 0);

    std::cout << "Somme des éléments : " << sum << std::endl; // 15
    return 0;
}
```

---

## 5. **std::count**
Compte le nombre d'occurrences d'une valeur donnée dans une plage.

### Prototype :
```cpp
template<class InputIt, class T>
typename iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T& value);
```

### Explications détaillées :
- Parcourt `[first, last)` pour compter les occurrences de `value`.
- Retourne un entier correspondant au nombre d'occurrences.
- Complexité linéaire (O(n)).
- Fonctionne avec tous les conteneurs itérables (`std::vector`, `std::list`, etc.).
- Idéal pour des analyses statistiques simples.

### Exemple avec une liste :
```cpp
#include <algorithm>
#include <list>
#include <iostream>

int main() {
    std::list<int> lst = {1, 2, 3, 2, 4, 2};
    int count = std::count(lst.begin(), lst.end(), 2);

    std::cout << "Le chiffre 2 apparaît " << count << " fois" << std::endl; // 3
    return 0;
}
```

---

## 6. **std::transform**
Applique une fonction à chaque élément d'une plage et stocke les résultats.

### Prototype :
```cpp
template<class InputIt, class OutputIt, class UnaryOperation>
OutputIt transform(InputIt first, InputIt last, OutputIt d_first, UnaryOperation unary_op);
```

### Explications détaillées :
- Applique une fonction ou un lambda à chaque élément de `[first, last)`.
- Stocke les résultats dans `[d_first, d_first + (last - first))`.
- Compatible avec une ou deux plages source.
- Complexité linéaire (O(n)).
- Utile pour des transformations comme mise au carré, conversion en majuscules, etc.

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    std::transform(v.begin(), v.end(), result.begin(), [](int x) { return x * x; });

    for (int n : result) {
        std::cout << n << " "; // 1 4 9 16 25
    }
    return 0;
}
```

---

## 7. **std::lower_bound**
Trouve la première position où un élément peut être inséré tout en maintenant l'ordre trié.

### Prototype :
```cpp
template<class ForwardIt, class T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value);
template<class ForwardIt, class T, class Compare>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp);
```

### Explications détaillées :
- Recherche binaire pour trouver la première position où `value` pourrait être inséré.
- Nécessite que la plage soit triée selon l'ordre croissant ou un comparateur personnalisé.
- Complexité logarithmique O(log n).
- Retourne un itérateur pointant vers la position d'insertion ou vers un élément égal.
- Utile pour des opérations d'insertion efficaces dans des conteneurs triés.

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto it = std::lower_bound(v.begin(), v.end(), 25);

    std::cout << "Position d'insertion : " << std::distance(v.begin(), it) << std::endl; // 2
    return 0;
}
```

---

## 8. **std::upper_bound**
Trouve la première position après les éléments égaux à une valeur donnée dans une plage triée.

### Prototype :
```cpp
template<class ForwardIt, class T>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value);
template<class ForwardIt, class T, class Compare>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp);
```

### Explications détaillées :
- Recherche binaire pour trouver l'itérateur pointant après le dernier élément égal à `value`.
- Nécessite une plage triée selon l'ordre croissant ou un comparateur personnalisé.
- Complexité logarithmique O(log n).
- Différence principale avec `std::lower_bound` : ne retourne pas un élément égal à `value`.
- Pratique pour des itérations sur des plages distinctes de valeurs égales.

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 30, 50};
    auto it = std::upper_bound(v.begin(), v.end(), 30);

    std::cout << "Position après les 30 : " << std::distance(v.begin(), it) << std::endl; // 4
    return 0;
}
```

---

## 9. **std::equal**
Vérifie si deux plages sont égales.

### Prototype :
```cpp
template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);
template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p);
```

### Explications détaillées :
- Compare deux plages élément par élément.
- Retourne `true` si les plages ont les mêmes éléments dans le même ordre.
- La version avec un prédicat permet une comparaison personnalisée.
- La complexité est linéaire O(n), où n est la taille de la première plage.
- Utile pour vérifier l'égalité logique ou approximative de conteneurs.

### Exemple avec deux vecteurs :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};

    if (std::equal(v1.begin(), v1.end(), v2.begin())) {
        std::cout << "Les vecteurs sont égaux." << std::endl;
    } else {
        std::cout << "Les vecteurs sont différents." << std::endl;
    }
    return 0;
}
```

---

## 10. **std::mismatch**
Trouve la première position où deux plages diffèrent.

### Prototype :
```cpp
template<class InputIt1, class InputIt2>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2);
template<class InputIt1, class InputIt2, class BinaryPredicate>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p);
```

### Explications détaillées :
- Parcourt deux plages et retourne la première paire d'itérateurs où les éléments diffèrent.
- Si aucune différence n'est trouvée, retourne une paire avec `last1` et `first2 + (last1 - first1)`.
- Utile pour diagnostiquer des différences entre deux conteneurs similaires.
- La version avec prédicat permet de personnaliser la condition d'inégalité.
- Complexité linéaire O(n).

### Exemple avec deux vecteurs :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {1, 2, 0, 4};

    auto result = std::mismatch(v1.begin(), v1.end(), v2.begin());

    if (result.first != v1.end()) {
        std::cout << "Différence trouvée : " << *result.first << " et " << *result.second << std::endl;
    } else {
        std::cout << "Aucune différence." << std::endl;
    }
    return 0;
}
```

---

## 11. **std::fill**
Remplit une plage avec une valeur donnée.

### Prototype :
```cpp
template<class ForwardIt, class T>
void fill(ForwardIt first, ForwardIt last, const T& value);
```

### Explications détaillées :
- Remplace tous les éléments de la plage `[first, last)` par `value`.
- Utile pour initialiser ou réinitialiser un conteneur.
- Complexité linéaire O(n).
- Fonctionne avec tous les conteneurs ayant des itérateurs modifiables.
- Ne nécessite pas d'allocation supplémentaire.

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v(5);
    std::fill(v.begin(), v.end(), 42);

    for (int n : v) {
        std::cout << n << " "; // 42 42 42 42 42
    }
    return 0;
}
```

---

## 12. **std::copy**
Copie une plage d'éléments vers une autre plage.

### Prototype :
```cpp
template<class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first);
```

### Explications détaillées :
- Copie les éléments de la plage `[first, last)` vers `[d_first, d_first + (last - first))`.
- Utile pour dupliquer des conteneurs ou une partie d'eux.
- Complexité linéaire O(n).
- La plage de destination doit avoir suffisamment d'espace alloué pour éviter des comportements indéfinis.
- Si les plages se chevauchent, utiliser `std::copy_backward`.

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> src = {1, 2, 3};
    std::vector<int> dest(3);

    std::copy(src.begin(), src.end(), dest.begin());

    for (int n : dest) {
        std::cout << n << " "; // 1 2 3
    }
    return 0;
}
```

---

## 13. **std::set_intersection**
Calcule l'intersection de deux plages triées.

### Prototype :
```cpp
template<class InputIt1, class InputIt2, class OutputIt>
OutputIt set_intersection(InputIt1 first1, InputIt1 last1,
                          InputIt2 first2, InputIt2 last2,
                          OutputIt d_first);
```

### Explications détaillées :
- Nécessite que les deux plages soient triées.
- Retourne une plage contenant les éléments communs aux deux plages.
- Complexité linéaire O(n), où n est la somme des tailles des plages.
- Utile pour des opérations sur des ensembles triés.
- Si une version personnalisée de comparaison est nécessaire, fournir une fonction `Compare`.

### Exemple avec deux vecteurs :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {3, 4, 5, 6};
    std::vector<int> result;

    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                          std::back_inserter(result));

    for (int n : result) {
        std::cout << n << " "; // 3 4
    }
    return 0;
}
```

---

## 14. **std::set_union**
Calcule l'union de deux plages triées.

### Prototype :
```cpp
template<class InputIt1, class InputIt2, class OutputIt>
OutputIt set_union(InputIt1 first1, InputIt1 last1,
                   InputIt2 first2, InputIt2 last2,
                   OutputIt d_first);
```

### Explications détaillées :
- Combine deux plages triées en une seule, contenant tous les éléments (sans doublons).
- Nécessite que les plages soient triées.
- Complexité linéaire O(n).
- Utile pour travailler avec des ensembles triés.

### Exemple avec deux vecteurs :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {3, 4, 5, 6};
    std::vector<int> result;

    std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(),
                   std::back_inserter(result));

    for (int n : result) {
        std::cout << n << " "; // 1 2 3 4 5 6
    }
    return 0;
}
```

---

## 15. **std::remove**
Supprime des éléments spécifiques d'une plage (logiquement).

### Prototype :
```cpp
template<class ForwardIt, class T>
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value);
```

### Explications détaillées :
- Réorganise les éléments pour déplacer ceux qui ne correspondent pas à `value` vers le début.
- Retourne un itérateur à la nouvelle fin logique.
- Pour supprimer physiquement les éléments, utilisez `erase` du conteneur.
- Complexité linéaire O(n).

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 2, 4};
    auto it = std::remove(v.begin(), v.end(), 2);
    v.erase(it, v.end());

    for (int n : v) {
        std::cout << n << " "; // 1 3 4
    }
    return 0;
}
```

---

## 16. **std::find_if**
Trouve le premier élément correspondant à une condition.

### Prototype :
```cpp
template<class InputIt, class UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p);
```

### Explications détaillées :
- Parcourt `[first, last)` pour trouver le premier élément satisfaisant la condition `p`.
- Retourne `last` si aucun élément ne correspond.
- Utile pour des recherches conditionnelles.

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 3, 5, 8, 9};
    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });

    if (it != v.end()) {
        std::cout << "Premier nombre pair : " << *it << std::endl; // 8
    } else {
        std::cout << "Aucun nombre pair trouvé." << std::endl;
    }
    return 0;
}
```

---

## 17. **std::generate**
Remplit une plage avec des valeurs générées par une fonction.

### Prototype :
```cpp
template<class ForwardIt, class Generator>
void generate(ForwardIt first, ForwardIt last, Generator g);
```

### Explications détaillées :
- Applique la fonction `g` pour remplir chaque élément dans `[first, last)`.
- Utile pour initialiser des conteneurs avec des valeurs calculées dynamiquement.
- Complexité linéaire O(n).

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v(5);
    int n = 0;
    std::generate(v.begin(), v.end(), [&n]() { return n++; });

    for (int x : v) {
        std::cout << x << " "; // 0 1 2 3 4
    }
    return 0;
}
```

---

## 18. **std::partition**
Réorganise une plage pour séparer les éléments selon une condition.

### Prototype :
```cpp
template<class BidirectionalIt, class UnaryPredicate>
BidirectionalIt partition(BidirectionalIt first, BidirectionalIt last, UnaryPredicate p);
```

### Explications détaillées :
- Place tous les éléments satisfaisant `p` avant ceux qui ne le satisfont pas.
- Retourne un itérateur à la fin des éléments satisfaisant `p`.
- Complexité linéaire O(n).
- Utile pour regrouper des éléments selon des critères.

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = std::partition(v.begin(), v.end(), [](int x) { return x % 2 == 0; });

    for (int n : v) {
        std::cout << n << " "; // 2 4 1 3 5
    }
    return 0;
}
```

---

## 19. **std::nth_element**
Réorganise les éléments pour qu'un élément soit à sa position finale triée.

### Prototype :
```cpp
template<class RandomIt>
void nth_element(RandomIt first, RandomIt nth, RandomIt last);
template<class RandomIt, class Compare>
void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp);
```

### Explications détaillées :
- Après exécution, l'élément pointé par `nth` est à sa position finale si la plage était triée.
- Les éléments avant sont inférieurs, et ceux après sont supérieurs (non triés).
- Complexité moyenne O(n).
- Utile pour trouver rapidement le k-ième plus petit élément.

### Exemple avec un vecteur :
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2};
    std::nth_element(v.begin(), v.begin() + 3, v.end());

    std::cout << "Élément à la position 3 : " << v[3] << std::endl;
    return 0;
}
```

