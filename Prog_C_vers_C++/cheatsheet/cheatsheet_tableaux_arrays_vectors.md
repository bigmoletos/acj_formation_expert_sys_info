| Type              | Fonction             | Exemple                              | Description                                               |
|:------------------|:---------------------|:-------------------------------------|:----------------------------------------------------------|
| Tableau classique | Déclaration          | int arr[5];                          | Déclare un tableau avec une taille fixe de 5 éléments.    |
| Tableau classique | Accès aux éléments   | arr[2];                              | Accède à l'élément à l'indice 2.                          |
| Tableau classique | Taille               | Pas de fonction, taille fixe         | La taille est fixe et définie à la compilation.           |
| Tableau classique | Initialisation       | int arr[5] = {1, 2, 3, 4, 5};        | Initialise un tableau avec 5 éléments spécifiques.        |
| Tableau classique | Modifier un élément  | arr[2] = 10;                         | Modifie l'élément à l'indice 2.                           |
| std::array        | Déclaration          | array<int, 5> arr = {1, 2, 3, 4, 5}; | Déclare un std::array avec une taille fixe de 5 éléments. |
| std::array        | Accès aux éléments   | arr[2];                              | Accède à l'élément à l'indice 2.                          |
| std::array        | Taille               | arr.size();                          | Renvoie la taille du std::array.                          |
| std::array        | Initialisation       | array<int, 5> arr = {1, 2, 3, 4, 5}; | Initialise un std::array avec 5 éléments spécifiques.     |
| std::array        | Modifier un élément  | arr[2] = 10;                         | Modifie l'élément à l'indice 2.                           |
| std::vector       | Déclaration          | vector<int> vec(5);                  | Déclare un vecteur avec 5 éléments initialisés à 0.       |
| std::vector       | Accès aux éléments   | vec[2];                              | Accède à l'élément à l'indice 2.                          |
| std::vector       | Taille               | vec.size();                          | Renvoie la taille du vecteur.                             |
| std::vector       | Ajouter un élément   | vec.push_back(10);                   | Ajoute un élément à la fin du vecteur.                    |
| std::vector       | Supprimer un élément | vec.pop_back();                      | Supprime le dernier élément du vecteur.                   |