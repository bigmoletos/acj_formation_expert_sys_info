**NumPy** :
**Création d'un tableau** : `a = np.array([1,2,3])`

**Création d'un tableau à deux dimensions** : `b = np.array([(1.5,2,3), (4,5,6)], dtype = float)`

**Création d'un tableau à trois dimensions** : `c = np.array([[(1.5,2,3), (4,5,6)],[(3,2,1), (4,5,6)]], dtype = float)`

**Sélection d'un élément** : `a[2]`

**Sélection d'un élément dans un tableau à deux dimensions** : `b[1,2]`

**Slicing d'un tableau** : `a[0:2]`

**Slicing d'un tableau à deux dimensions (lignes)** : `b[0:2]`

**Slicing d'un tableau à deux dimensions (colonnes)** : `b[:,0:2]`


**Pandas** :
**Création d'une série** : `s = pd.Series([1, 2, 3], index=['a', 'b', 'c'])`

 **Création d'un DataFrame** : `df = pd.DataFrame({'A': [1, 2, 3], 'B': [4, 5, 6]})`

 **Sélection d'une colonne** : `df['A']`

 **Sélection de plusieurs colonnes** : `df[['A', 'B']]`

 **Sélection d'une ligne par son indice** : `df.loc[0]`

 **Sélection de plusieurs lignes par leurs indices** : `df.loc[[0, 1, 2]]`

 **Sélection d'une ligne par sa position** : `df.iloc[0]`

 **Sélection de plusieurs lignes par leurs positions** : `df.iloc[[0, 1, 2]]`

 **Slicing d'un DataFrame (lignes)** : `df[0:2]`

 **Slicing d'un DataFrame (colonnes)** : `df.iloc[:,0:2]`

 **Sélection de lignes basée sur une condition** : `df[df['A'] > 1]`

 **Sélection de lignes basée sur plusieurs conditions** : `df[(df['A'] > 1) & (df['B'] < 5)]`
