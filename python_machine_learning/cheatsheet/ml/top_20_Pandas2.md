Un DataFrame de la bibliothèque pandas a de nombreuses méthodes et attributs que vous pouvez utiliser. Voici quelques-uns des plus couramment utilisés :

- **Attributs** :
    - `df.shape` : Renvoie un tuple représentant la dimensionnalité du DataFrame.
    - `df.columns` : Renvoie les noms des colonnes du DataFrame.
    - `df.index` : Renvoie l'index du DataFrame.
    - `df.dtypes` : Renvoie les types de données de chaque colonne.
    - `df.values` : Renvoie une représentation Numpy du DataFrame.

- **Méthodes** :
    - `df.head(n)` : Renvoie les `n` premières lignes du DataFrame.
    - `df.tail(n)` : Renvoie les `n` dernières lignes du DataFrame.
    - `df.describe()` : Génère des statistiques descriptives.
    - `df.info()` : Imprime un résumé concis du DataFrame.
    - `df.mean()`, `df.median()`, `df.min()`, `df.max()` : Calculent respectivement la moyenne, la médiane, le minimum et le maximum.
    - `df.apply(func)` : Applique une fonction le long d'un axe du DataFrame.
    - `df.groupby(key)` : Regroupe le DataFrame en utilisant une mappage sur les labels.
    - `df.join(other)` : Joint deux DataFrames en utilisant leurs index.
    - `df.merge(other)` : Fusionne DataFrame ou nommé Series objects avec une base de données de style join.
    - `df.pivot()` : Renvoie un DataFrame redimensionné organisé par les valeurs d'index/columnes données.
    - `df.drop(columns)` : Supprime les colonnes spécifiées du DataFrame.

