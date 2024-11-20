**Importation de Pandas** :
`import pandas as pd`
**Création d'une série** :
`s = pd.Series([1, 2, 3], index=['a', 'b', 'c'])`
**Création d'un DataFrame à partir d'un dictionnaire** :
`df = pd.DataFrame({'A': [1, 2, 3], 'B': [4, 5, 6]})`
**Lecture d'un fichier CSV** :
`df = pd.read_csv('file.csv')`
**Écriture dans un fichier CSV** :
`df.to_csv('file.csv')`
**Lecture d'un fichier Excel** :
`df = pd.read_excel('file.xlsx')`
**Écriture dans un fichier Excel** :
`df.to_excel('file.xlsx')`
**Lecture d'une requête SQL** :
`df = pd.read_sql_query('SELECT * FROM table', connection_object)`
**Écriture dans une table SQL** :
`df.to_sql('table', connection_object)`
**Obtention des premiers éléments d'une série ou d'un DataFrame** :
`s.head()`, `df.head()`
**Obtention des derniers éléments d'une série ou d'un DataFrame** :
`s.tail()`, `df.tail()`
**Obtention de la forme d'un DataFrame** :
`df.shape`
**Obtention des types de données d'un DataFrame** :
`df.dtypes`
**Obtention des noms de colonnes d'un DataFrame** :
`df.columns`
**Sélection d'une colonne d'un DataFrame** :
`df['A']`
**Sélection de plusieurs colonnes d'un DataFrame** :
`df[['A', 'B']]`
**Sélection d'une ligne d'un DataFrame par son indice** :
`df.loc[0]`
**Sélection de plusieurs lignes d'un DataFrame par leurs indices** :
`df.loc[[0, 1, 2]]`
**Sélection d'une ligne d'un DataFrame par sa position** :
`df.iloc[0]`
**Sélection de plusieurs lignes d'un DataFrame par leurs positions** :
`df.iloc[[0, 1, 2]]`

