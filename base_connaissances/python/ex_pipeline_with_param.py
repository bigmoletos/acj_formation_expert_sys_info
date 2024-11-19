import seaborn as sns
import pandas as pd
import numpy as np
from sklearn.pipeline import Pipeline
from sklearn.tree import DecisionTreeClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.datasets import load_titanic
from sklearn.model_selection import train_test_split
from sklearn import tree

# Charger les données du Titanic
titanic = load_titanic()

# Extraire les caractéristiques et les résultats
X = titanic.data
y = titanic.target



# Diviser les données en ensembles d'entraînement et de test
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42)

# Créer un objet de pipeline
pipe = Pipeline([('scaler', StandardScaler()),
                ('classifier', DecisionTreeClassifier())])

# Définir les paramètres du modèle
params = {'classifier__max_depth': 5, 'classifier__min_samples_split': 10}

# Définir les paramètres du pipeline
pipe.set_params(**params)

# Remplir le pipeline avec des données d'entraînement et entraîner le modèle
pipe.fit(X_train, y_train)


# Créer un objet de l'arbre de décision
dtree = DecisionTreeClassifier()

# Ajuster l'arbre de décision aux données d'entraînement
dtree.fit(X_train, y_train)

# Visualiser l'arbre de décision
tree.plot_tree(dtree)
# Charger les données du Titanic
titanic = sns.load_dataset("titanic")

# Créer une matrice de corrélation
corr = titanic.corr()

# Créer un heatmap
sns.heatmap(corr, annot=True)
