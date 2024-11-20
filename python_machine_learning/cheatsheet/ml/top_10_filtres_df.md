# Importation de la bibliothèque pandas
```python
import pandas as pd
import numpy as np

# Création d'un dataframe exemple
```python
df = pd.DataFrame({
    'A': [1, 2, 3, np.nan],
    'B': [4, 5, 6, np.nan],
    'C': ['foo', 'bar', 'baz', 'qux'],
    'D': pd.date_range(start='1/1/2020', end='1/4/2020')
})


# Filtrage par valeur de colonne
```python
filtered_df1 = df[df['A'] > 1]
print("res1:", filtered_df1)

Résultat :
1  2.0  5.0  bar 2020-01-02
2  3.0  6.0  baz 2020-01-03

# Filtrage basé sur plusieurs conditions
```python
filtered_df2 = df[(df['A'] > 1) & (df['B'] < 6)]
print("res2:", filtered_df2)
Résultat :
1  2.0  5.0  bar 2020-01-02


# Filtrage basé sur les dates
```python
filtered_df3 = df[(df['D'] > '2020-01-02') & (df['D'] <= '2020-01-03')]
print("res13", filtered_df3)
Résultat :
1  2.0  5.0  bar 2020-01-02


# Filtrage à une chaîne spécifique
```python
filtered_df4 = df[df['C'].str.contains('foo')]
print("res4:", filtered_df4)
Résultat :
0  1.0  4.0  foo 2020-01-01


# Sélection de lignes de dataframe basées sur une liste de valeurs
```python
filtered_df5 = df[df['A'].isin([1, 2])]
print("res5:", filtered_df5)
Résultat :
0  1.0  4.0  foo 2020-01-01
1  2.0  5.0  bar 2020-01-02


# Sélection de lignes de dataframe à l'aide d'expressions régulières (Regex)
```python
filtered_df6 = df[df['C'].str.match('fo.*')]
print("res6:", filtered_df6)
Résultat :
0  1.0  4.0  foo 2020-01-01


# Sélection de lignes de dataframe Null ou Non Null
```python
filtered_df7 = df[df['A'].isnull()]
print("res7:", filtered_df7)
Résultat :
3 NaN NaN  qux 2020-01-04

# Utilisation de la méthode loc()
```python
filtered_df8 = df.loc[df['A'] > 1]
print("res8:", filtered_df8)
Résultat :
1  2.0  5.0  bar 2020-01-02
2  3.0  6.0  baz 2020-01-03


# Utilisation de la méthode query()
```python
filtered_df9 = df.query('A > 1')
print("res9:", filtered_df9)
Résultat :
1  2.0  5.0  bar 2020-01-02
2  3.0  6.0  baz 2020-01-03

# Utilisation de la méthode iloc()
```python
filtered_df10 = df.iloc[0:2]
print("res10:", filtered_df10)
Résultat :
0  1.0  4.0  foo 2020-01-01
1  2.0  5.0  bar 2020-01-02


# Utilisation de la fonction where()
```python
filtered_df11 = df.where(df['A'] > 1)
print("res11:", filtered_df11)
Résultat :
0  NaN  NaN  NaN        NaT
1  2.0  5.0  bar 2020-01-02
2  3.0  6.0  baz 2020-01-03
3  NaN  NaN  NaN        NaT

