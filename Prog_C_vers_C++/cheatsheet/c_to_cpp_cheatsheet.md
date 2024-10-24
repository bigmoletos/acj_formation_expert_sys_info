
# C to C++ Transition Cheatsheet

## 1. File Extension
- **C** : `.c`
- **C++** : `.cpp`

## 2. Basic Compilation
- **C** :
  ```bash
  gcc file.c -o output
  ```
- **C++** :
  ```bash
  g++ file.cpp -o output
  ```

## 3. Input/Output
- **C** :
  ```c
  #include <stdio.h>

  int main() {
      printf("Hello, World!\n");
      return 0;
  }
  ```
- **C++** :
  ```cpp
  #include <iostream>

  int main() {
      std::cout << "Hello, World!" << std::endl;
      return 0;
  }
  ```

## 4. Comments
- **C** :
  ```c
  // Single-line comment
  /* Multi-line
     comment */
  ```
- **C++** :
  ```cpp
  // Single-line comment
  /* Multi-line
     comment */
  ```

## 5. Memory Allocation
- **C** :
  ```c
  int* p = (int*)malloc(sizeof(int));
  free(p);
  ```
- **C++** :
  ```cpp
  int* p = new int;
  delete p;
  ```

## 6. Functions
- **C** :
  ```c
  int add(int a, int b) {
      return a + b;
  }
  ```
- **C++** :
  ```cpp
  int add(int a, int b) {
      return a + b;
  }
  ```

## 7. Classes (C++ only)
- **C** : No support for classes
- **C++** :
  ```cpp
  class MyClass {
  public:
      void myMethod() {
          std::cout << "Hello from MyClass!" << std::endl;
      }
  };
  ```

## 8. Namespaces (C++ only)
- **C** : No namespaces
- **C++** :
  ```cpp
  namespace myNamespace {
      int x = 10;
  }
  ```

## 9. Exception Handling (C++ only)
- **C** : No built-in exception handling
- **C++** :
  ```cpp
  try {
      // Code that may throw an exception
  } catch (int e) {
      std::cout << "Exception caught: " << e << std::endl;
  }
  ```

## 10. Headers
- **C** :
  ```c
  #include <stdio.h>
  #include <stdlib.h>
  ```
- **C++** :
  ```cpp
  #include <iostream>
  #include <cstdlib>
  ```

## 11. Standard Libraries
- **C** : Standard libraries include `stdio.h`, `stdlib.h`, etc.
- **C++** : Standard libraries include `iostream`, `vector`, `string`, `algorithm`, etc.

## 12. Structure Declaration
- **C** :
  ```c
  struct MyStruct {
      int a;
      float b;
  };
  ```
- **C++** :
  ```cpp
  struct MyStruct {
      int a;
      float b;
  };
  ```

## 13. Object-Oriented Programming (C++ only)
- **C** : No OOP support
- **C++** : C++ supports object-oriented programming with classes, inheritance, polymorphism, and encapsulation.



## compiler et lancer en controlant les erreurs :
- **-Wunused-const-variable Wunused-parameter -Werror -Wsign-compare**
```cpp
g++ exo1.cpp -o exo1 -Wunused-const-variable Wunused-parameter -Werror && ./exo1

```
- **-creation fichier Makefile (sans extension) et dans le même dossier que le oules fichiers à compiler pour capter les erreurs et les warning au moment du build**
```cpp
// fichier Makefile
# Variables
CC = g++
CFLAGS = -Wall -Wextra -Wunused-const-variable -Wunused-parameter -Werror

# Règle générique pour compiler n'importe quel fichier .cpp
%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

# Nettoyer tous les exécutables générés
clean:
	rm -f *.o $(wildcard *.exe) $(wildcard *.out) $(wildcard *.obj)

```
pour l'utiliser il suffit de faire :
```cpp
make nom_fichier
// ex
make exo2

//  pour supprimer les fichiers exe
make clean exo3

```


## Debugger  gdb   (GNU Debug)

```bash
sudo apt install gdb

(gdb) break main       # Définir un point d'arrêt à la fonction main
(gdb) run              # Lancer le programme jusqu'au point d'arrêt
(gdb) next             # Avancer à la prochaine ligne
(gdb) print variable   # Afficher la valeur d'une variable
(gdb) quit             # Quitter GDB

gdb ./exo3
```


