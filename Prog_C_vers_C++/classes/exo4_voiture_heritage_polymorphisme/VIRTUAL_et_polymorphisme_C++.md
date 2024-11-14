
# Utilisation de `virtual` et du polymorphisme en C++

Le mot-clé `virtual` en C++ est essentiel pour permettre le **polymorphisme**, en particulier lorsqu'on travaille avec l'héritage. Il garantit que les méthodes et destructeurs appropriés des classes dérivées sont appelés, même si l'objet est référencé via un pointeur ou une référence de la classe de base.

## Sommaire

1. [Pourquoi utiliser `virtual` sur le destructeur](#1-pourquoi-utiliser-virtual-sur-le-destructeur)
2. [Pourquoi utiliser `virtual` sur certaines méthodes](#2-pourquoi-utiliser-virtual-sur-certaines-méthodes)
3. [Exemple complet avec `virtual`](#3-exemple-complet-avec-virtual)
4. [Conclusion](#4-conclusion)

---

## 1. Pourquoi utiliser `virtual` sur le destructeur

Lorsqu'un destructeur est marqué comme `virtual` dans une classe de base, cela garantit que le destructeur de la classe dérivée sera correctement appelé si un objet dérivé est détruit via un pointeur de la classe de base.

### Exemple de problème sans destructeur `virtual`

Imaginons que nous ayons une classe de base `CVehicule` et une classe dérivée `CVoiture`. Si nous détruisons un objet `CVoiture` via un pointeur de type `CVehicule*` sans un destructeur `virtual`, seul le destructeur de `CVehicule` sera appelé, et non celui de `CVoiture`. Cela peut entraîner des **fuites de mémoire** si `CVoiture` alloue dynamiquement des ressources.

```cpp
CVehicule* veh = new CVoiture("Volvo");
delete veh; // Sans destructeur virtuel, seul CVehicule::~CVehicule() est appelé
```

### Solution : ajouter un destructeur `virtual`

En ajoutant `virtual` au destructeur de `CVehicule`, C++ s'assure que le destructeur de la classe dérivée `CVoiture` sera également appelé, libérant correctement toutes les ressources.

```cpp
class CVehicule {
public:
    virtual ~CVehicule(); // Destructeur virtuel
};
```

## 2. Pourquoi utiliser `virtual` sur certaines méthodes

Le mot-clé `virtual` permet de définir des **méthodes polymorphiques**. En marquant une méthode comme `virtual` dans la classe de base, cela permet aux classes dérivées de redéfinir cette méthode, et garantit que la version correcte sera appelée en fonction du type réel de l'objet, même si celui-ci est manipulé via un pointeur de la classe de base.

### Exemple d'utilisation du polymorphisme

Dans votre code, la méthode `afficher()` est redéfinie dans `CVoiture`. En marquant cette méthode comme `virtual` dans `CVehicule` et `override` dans `CVoiture`, on s'assure que la bonne version de `afficher()` est appelée en fonction du type réel de l'objet.

```cpp
class CVehicule {
public:
    virtual void afficher() const; // Méthode virtuelle pour permettre le polymorphisme
};

class CVoiture : public CVehicule {
public:
    void afficher() const override; // Redéfinition de la méthode afficher()
};
```

### Exemple de polymorphisme en action

```cpp
CVehicule* veh = new CVoiture("Volvo");
veh->afficher(); // Appelle CVoiture::afficher() grâce au mot-clé virtual
```

Sans `virtual`, la méthode `CVehicule::afficher()` serait appelée, même si `veh` pointe vers un objet de type `CVoiture`. Grâce à `virtual`, C++ résout l'appel à la méthode la plus spécifique possible en fonction du type de l'objet réel.

## 3. Exemple complet avec `virtual`

Voici un exemple complet montrant l'importance du mot-clé `virtual` dans les destructeurs et les méthodes :

### Fichier `CVehicule.hpp`

```cpp
#ifndef CVEHICULE_HPP
#define CVEHICULE_HPP

#include <string>
#include <iostream>

class CVehicule {
public:
    CVehicule(const std::string& type = "Inconnu");
    virtual ~CVehicule(); // Destructeur virtuel
    virtual void afficher() const; // Méthode virtuelle pour polymorphisme

protected:
    std::string type;
};

#endif
```

### Fichier `CVehicule.cpp`

```cpp
#include "CVehicule.hpp"

CVehicule::CVehicule(const std::string& type) : type(type) {}

CVehicule::~CVehicule() {
    std::cout << "Destruction de CVehicule (" << type << ")" << std::endl;
}

void CVehicule::afficher() const {
    std::cout << "Je suis un véhicule de type : " << type << std::endl;
}
```

### Fichier `CVoiture.hpp`

```cpp
#ifndef CVOITURE_HPP
#define CVOITURE_HPP

#include "CVehicule.hpp"
#include <string>

class CVoiture : public CVehicule {
public:
    CVoiture(const std::string& modele);
    virtual ~CVoiture(); // Destructeur virtuel pour garantir la destruction complète
    void afficher() const override; // Redéfinition de la méthode afficher()

private:
    std::string modele;
};

#endif
```

### Fichier `CVoiture.cpp`

```cpp
#include "CVoiture.hpp"
#include <iostream>

CVoiture::CVoiture(const std::string& modele) : CVehicule("Voiture"), modele(modele) {}

CVoiture::~CVoiture() {
    std::cout << "Destruction de CVoiture (" << modele << ")" << std::endl;
}

void CVoiture::afficher() const {
    std::cout << "Je suis une voiture de modèle : " << modele << std::endl;
}
```

### Exemple d'utilisation dans `main.cpp`

```cpp
#include "CVehicule.hpp"
#include "CVoiture.hpp"
#include <vector>
#include <iostream>

int main() {
    CVehicule* veh = new CVoiture("Volvo");
    veh->afficher(); // Appelle CVoiture::afficher() grâce au polymorphisme

    delete veh; // Appelle le destructeur de CVoiture suivi de CVehicule

    return 0;
}
```

## 4. Conclusion

- **Destructeur `virtual`** : Assure que le destructeur de la classe dérivée est appelé lors de la suppression d'un objet via un pointeur de la classe de base. Cela permet de gérer correctement la mémoire et les ressources.
- **Méthodes `virtual`** : Permet le polymorphisme, ce qui signifie que la bonne version de la méthode est appelée en fonction du type réel de l'objet, même lorsqu'il est manipulé via un pointeur de la classe de base.

Le mot-clé `virtual` est essentiel pour éviter les erreurs de gestion de mémoire et pour tirer parti du polymorphisme, ce qui rend le code plus flexible et plus sûr.
