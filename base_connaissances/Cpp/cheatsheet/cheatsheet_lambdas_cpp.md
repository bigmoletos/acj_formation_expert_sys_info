
# Cheatsheet : Les Fonctions Lambda en C++

Les fonctions lambda, ou fonctions anonymes, sont des expressions qui permettent de déclarer des fonctions directement dans le code. Elles sont particulièrement utiles pour les opérations rapides ou les callbacks.

---

## 1. Syntaxe de Base
```cpp
[ capture_clause ] ( parameters ) -> return_type { body }
```

### Description des composants :
- **`capture_clause`** : Définit les variables accessibles dans la lambda (`[]`, `[=]`, `[&]`).
- **`parameters`** : Liste des paramètres, comme dans une fonction normale.
- **`return_type`** *(optionnel)* : Type de retour de la lambda.
- **`body`** : Bloc d'instructions de la lambda.

---

## 2. Exemple Simple
```cpp
#include <iostream>
using namespace std;

int main() {
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    cout << "Résultat : " << add(5, 3) << endl; // Affiche 8
    return 0;
}
```

---

## 3. Capture des Variables

### Capture par Valeur (`[=]`) :
```cpp
int x = 10;
auto lambda_val = [=]() {
    cout << "x (valeur) : " << x << endl;
};
lambda_val();
```

### Capture par Référence (`[&]`) :
```cpp
int x = 10;
auto lambda_ref = [&]() {
    x *= 2;
    cout << "x (référence) : " << x << endl;
};
lambda_ref(); // Modifie x
```

### Capture de Variables Individuelles :
```cpp
int a = 5, b = 10;
auto lambda = [a, &b]() {
    // a est capturé par valeur, b par référence
    cout << "a : " << a << ", b : " << b << endl;
};
lambda();
```

---

## 4. Utilisation avec `std::for_each`
### Doubler les Valeurs d'un `std::vector` :
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // pour std::for_each
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    for_each(vec.begin(), vec.end(), [](int &x) { x *= 2; });
    for (int x : vec) {
        cout << x << " "; // Affiche : 2 4 6 8 10
    }
    return 0;
}
```

---

## 5. Utilisation avec `std::count_if`
### Compter les Valeurs Supérieures à 10 :
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // pour std::count_if
using namespace std;

int main() {
    vector<int> vec = {5, 15, 20, 8, 25};
    int count = count_if(vec.begin(), vec.end(), [](int x) { return x > 10; });
    cout << "Nombre d'éléments > 10 : " << count << endl; // Affiche 3
    return 0;
}
```

---

## 6. Utilisation avec `std::sort`
### Trier un `std::vector` dans l'ordre décroissant :
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // pour std::sort
using namespace std;

int main() {
    vector<int> vec = {5, 1, 4, 2, 8};
    sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });
    for (int x : vec) {
        cout << x << " "; // Affiche : 8 5 4 2 1
    }
    return 0;
}
```

---

## 7. Lambda avec Capture Impliquée
### Exemple :
```cpp
int x = 10, y = 20;
auto lambda = [=, &y]() {
    // x est capturé par valeur, y par référence
    y += x;
    cout << "y : " << y << endl;
};
lambda();
```

---

## 8. Lambda comme Callback
### Exemple avec une Fonction :
```cpp
#include <iostream>
#include <functional>
using namespace std;

void execute_callback(function<void()> callback) {
    callback();
}

int main() {
    execute_callback([]() {
        cout << "Callback exécuté !" << endl;
    });
    return 0;
}
```

---

### Notes :
1. Les lambdas sont idéales pour des tâches rapides ou les expressions anonymes.
2. Le mot-clé `auto` est souvent utilisé pour stocker les lambdas.
3. Les lambdas peuvent capturer automatiquement des variables locales.

---

### Références :
- Bibliothèque STL : `<algorithm>`, `<functional>`
- Documentation officielle : [cppreference.com](https://en.cppreference.com)
