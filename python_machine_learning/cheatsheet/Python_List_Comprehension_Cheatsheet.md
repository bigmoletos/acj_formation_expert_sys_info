
# Python List Comprehension Cheatsheet

Les **list comprehensions** permettent de créer des listes de manière concise et lisible en Python. Voici 10 exemples pratiques :

---

## 1. **Créer une liste de nombres carrés**
```python
squares = [x**2 for x in range(10)]
# Résultat : [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
```

---

## 2. **Créer une liste de nombres pairs**
```python
evens = [x for x in range(20) if x % 2 == 0]
# Résultat : [0, 2, 4, 6, 8, 10, 12, 14, 16, 18]
```

---

## 3. **Créer une liste de tuples (nombre, carré)**
```python
tuples = [(x, x**2) for x in range(5)]
# Résultat : [(0, 0), (1, 1), (2, 4), (3, 9), (4, 16)]
```

---

## 4. **Appliquer une fonction sur une liste**
```python
words = ["hello", "world"]
upper_words = [word.upper() for word in words]
# Résultat : ['HELLO', 'WORLD']
```

---

## 5. **Filtrer et transformer une liste**
```python
nums = [1, -2, 3, -4, 5]
positives_squared = [x**2 for x in nums if x > 0]
# Résultat : [1, 9, 25]
```

---

## 6. **Aplatir une liste de listes**
```python
nested = [[1, 2], [3, 4], [5, 6]]
flattened = [num for sublist in nested for num in sublist]
# Résultat : [1, 2, 3, 4, 5, 6]
```

---

## 7. **Créer une liste de caractères à partir d'une chaîne**
```python
chars = [char for char in "Python"]
# Résultat : ['P', 'y', 't', 'h', 'o', 'n']
```

---

## 8. **Créer une matrice identité (diagonale = 1)**
```python
matrix_identity = [[1 if i == j else 0 for j in range(3)] for i in range(3)]
# Résultat : [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
```

---

## 9. **Créer une liste avec des conditions multiples**
```python
fizz_buzz = ["FizzBuzz" if x % 15 == 0 else "Fizz" if x % 3 == 0 else "Buzz" if x % 5 == 0 else x for x in range(1, 16)]
# Résultat : [1, 2, 'Fizz', 4, 'Buzz', 'Fizz', 7, 8, 'Fizz', 'Buzz', 11, 'Fizz', 13, 14, 'FizzBuzz']
```

---

## 10. **Créer une liste de mots filtrés par longueur**
```python
words = ["python", "list", "comprehension", "cheatsheet"]
short_words = [word for word in words if len(word) <= 5]
# Résultat : ['list']
```

---

### Notes
- Les compréhensions de listes sont plus lisibles et souvent plus rapides que les boucles `for` classiques.
- **Syntaxe générale** : `[expression for item in iterable if condition]`

---
