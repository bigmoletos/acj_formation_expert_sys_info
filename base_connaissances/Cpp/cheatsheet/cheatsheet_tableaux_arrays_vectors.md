# Tableaux Array ou Vector en C++ Library

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

# Plus

| Type                        | Fonction/Commande         | Exemple                                                  | Description                                                                                         |
|:----------------------------|:--------------------------|:---------------------------------------------------------|:----------------------------------------------------------------------------------------------------|
| Tableau classique (C-style) | Déclaration               | int arr[5];                                              | Déclare un tableau classique avec une taille fixe de 5 éléments.                                    |
| Tableau classique (C-style) | Accès aux éléments        | arr[2];                                                  | Accède à l'élément à l'indice 2.                                                                    |
| Tableau classique (C-style) | Lecture (boucle)          | for (int i = 0; i < 5; ++i) { cout << arr[i]; }          | Utilise une boucle pour lire tous les éléments du tableau.                                          |
| Tableau classique (C-style) | Trier                     | Pas possible sans une implémentation manuelle            | Impossible de trier directement un tableau classique sans implémenter votre propre fonction de tri. |
| Tableau classique (C-style) | Insertion (fixe)          | Impossible, taille fixe                                  | Impossible d'insérer un élément dans un tableau classique car sa taille est fixe.                   |
| Tableau classique (C-style) | Suppression (fixe)        | Impossible, taille fixe                                  | Impossible de supprimer un élément dans un tableau classique car sa taille est fixe.                |
| std::array                  | Déclaration               | std::array<int, 5> arr;                                  | Déclare un std::array avec une taille fixe de 5 éléments.                                           |
| std::array                  | Accès aux éléments        | arr[2];                                                  | Accède à l'élément à l'indice 2.                                                                    |
| std::array                  | Lecture (boucle)          | for (int i = 0; i < arr.size(); ++i) { cout << arr[i]; } | Utilise une boucle pour lire tous les éléments du std::array.                                       |
| std::array                  | Trier                     | std::sort(arr.begin(), arr.end());                       | Tri du std::array à l'aide de std::sort.                                                            |
| std::array                  | Insertion (taille fixe)   | Impossible, taille fixe                                  | Insertion impossible dans std::array, car la taille est fixe.                                       |
| std::array                  | Suppression (taille fixe) | Impossible, taille fixe                                  | Suppression impossible dans std::array, car la taille est fixe.                                     |
| std::vector                 | Déclaration               | std::vector<int> vec;                                    | Déclare un std::vector dynamique.                                                                   |
| std::vector                 | Accès aux éléments        | vec[2];                                                  | Accède à l'élément à l'indice 2.                                                                    |
| std::vector                 | Lecture (boucle)          | for (int i = 0; i < vec.size(); ++i) { cout << vec[i]; } | Utilise une boucle pour lire tous les éléments du std::vector.                                      |
| std::vector                 | Trier                     | std::sort(vec.begin(), vec.end());                       | Tri du std::vector à l'aide de std::sort.                                                           |
| std::vector                 | Insertion                 | vec.insert(vec.begin() + 2, 10);                         | Insère un élément dans le std::vector à l'indice 2.                                                 |
| std::vector                 | Suppression               | vec.erase(vec.begin() + 2);                              | Supprime l'élément à l'indice 2 du std::vector.                                                     |



## "Quand choisir ?"
### "Tableau classique (C-style)":
"Utilisez un tableau classique si vous savez à l'avance que la taille est fixe et ne changera jamais. "
"C'est plus simple mais moins flexible que les autres options."

### "std::array":
"Utilisez std::array si vous avez besoin d'un tableau avec une taille fixe mais que vous voulez des "
"fonctionnalités supplémentaires comme la gestion sécurisée avec des méthodes comme .size() ou .at()."

### "std::vector":
"Utilisez std::vector si la taille du tableau peut changer au cours du programme. C'est flexible, "
"vous pouvez ajouter ou supprimer des éléments à tout moment, mais il consomme plus de mémoire."


