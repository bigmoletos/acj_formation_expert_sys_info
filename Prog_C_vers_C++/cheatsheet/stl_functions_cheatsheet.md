
# Cheatsheet : Fonctions STL les plus courantes en C++

Les fonctions de la bibliothèque standard (STL) de C++ permettent d'effectuer des opérations communes sur les conteneurs comme `std::vector`, `std::list`, ou `std::map`.

---

## 1. **std::sort**
Trie une plage d'éléments dans l'ordre croissant (ou selon un comparateur personnalisé).
```cpp
#include <algorithm>
std::sort(begin, end);
std::sort(begin, end, comparer);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage à trier.
- `comparer` *(optionnel)* : Fonction ou lambda pour personnaliser le tri.

---

## 2. **std::for_each**
Applique une fonction à chaque élément d'une plage.
```cpp
#include <algorithm>
std::for_each(begin, end, fonction);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.
- `fonction` : Fonction ou lambda appliquée à chaque élément.

---

## 3. **std::find**
Recherche un élément dans une plage.
```cpp
#include <algorithm>
auto it = std::find(begin, end, valeur);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.
- `valeur` : Valeur recherchée.
### Retourne :
- Itérateur vers l'élément trouvé ou `end` si non trouvé.

---

## 4. **std::count**
Compte le nombre d'occurrences d'une valeur dans une plage.
```cpp
#include <algorithm>
int n = std::count(begin, end, valeur);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.
- `valeur` : Valeur à compter.

---

## 5. **std::count_if**
Compte le nombre d'éléments satisfaisant une condition.
```cpp
#include <algorithm>
int n = std::count_if(begin, end, condition);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.
- `condition` : Fonction ou lambda retournant `true` pour les éléments à compter.

---

## 6. **std::reverse**
Inverse les éléments d'une plage.
```cpp
#include <algorithm>
std::reverse(begin, end);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.

---

## 7. **std::accumulate**
Calcule la somme ou une réduction personnalisée sur une plage.
```cpp
#include <numeric>
auto result = std::accumulate(begin, end, initial, operation);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.
- `initial` : Valeur initiale pour la somme ou réduction.
- `operation` *(optionnel)* : Fonction binaire pour personnaliser l'opération.

---

## 8. **std::unique**
Supprime les doublons consécutifs dans une plage.
```cpp
#include <algorithm>
auto it = std::unique(begin, end);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.
### Remarque :
- Les éléments après l'itérateur retourné sont indéfinis.

---

## 9. **std::remove**
Supprime une valeur donnée dans une plage (sans réorganiser la mémoire).
```cpp
#include <algorithm>
auto it = std::remove(begin, end, valeur);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.
- `valeur` : Valeur à supprimer.

---

## 10. **std::transform**
Transforme les éléments d'une plage selon une fonction.
```cpp
#include <algorithm>
std::transform(begin, end, destination, fonction);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage source.
- `destination` : Itérateur de destination pour les résultats.
- `fonction` : Fonction ou lambda appliquée à chaque élément.

---

## 11. **std::equal**
Vérifie si deux plages sont égales.
```cpp
#include <algorithm>
bool isEqual = std::equal(begin1, end1, begin2);
```
### Paramètres :
- `begin1`, `end1` : Première plage.
- `begin2` : Début de la seconde plage.

---

## 12. **std::partition**
Réorganise les éléments pour que ceux satisfaisant une condition soient en premier.
```cpp
#include <algorithm>
auto it = std::partition(begin, end, condition);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.
- `condition` : Fonction ou lambda définissant la condition.

---

## 13. **std::lower_bound**
Recherche une position d'insertion ou un élément dans une plage triée.
```cpp
#include <algorithm>
auto it = std::lower_bound(begin, end, valeur);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage triée.
- `valeur` : Valeur recherchée.

---

## 14. **std::nth_element**
Réorganise les éléments pour que le `n`-ième soit à sa position triée.
```cpp
#include <algorithm>
std::nth_element(begin, nth, end);
```
### Paramètres :
- `begin`, `nth`, `end` : Itérateurs définissant la plage et l'élément à positionner.

---

## 15. **std::min_element / std::max_element**
Trouve le plus petit ou le plus grand élément d'une plage.
```cpp
#include <algorithm>
auto minIt = std::min_element(begin, end);
auto maxIt = std::max_element(begin, end);
```
### Paramètres :
- `begin`, `end` : Itérateurs définissant la plage.

---

### Références :
- [cppreference.com](https://en.cppreference.com)
- Bibliothèque standard C++ `<algorithm>`, `<numeric>`

