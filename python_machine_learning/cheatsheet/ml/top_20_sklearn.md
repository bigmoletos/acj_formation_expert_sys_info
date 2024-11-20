Voici les 20 commandes les plus courantes de la bibliothèque  Scikit-Learn pour l'apprentissage automatique:

1. **fit**: Permet de remplir le modèle avec des données d'entraînement.
2. **predict**: Permet de prédire les valeurs cibles pour les données d'entrée.
3. **transform**: Permet de transformer les données d'entrée en un format compatible avec le modèle.
4. **fit_transform**: Permet de remplir le modèle avec des données d'entraînement et de transformer les données d'entrée en un format compatible avec le modèle.
5. **score**: Permet de calculer la précision du modèle sur les données de test.
6. **get_params**: Permet d'obtenir les paramètres du modèle.
7. **set_params**: Permet de définir les paramètres du modèle.
8. **GridSearchCV**: Permet de rechercher les meilleurs paramètres pour un modèle donné.
9. **RandomizedSearchCV**: Permet de rechercher les meilleurs paramètres pour un modèle donné en utilisant une recherche aléatoire.
10. **cross_val_score**: Permet de calculer la précision du modèle en utilisant la validation croisée.
11. **KFold**: Permet de diviser les données en k groupes pour la validation croisée.
12. **train_test_split**: Permet de diviser les données en ensembles d'entraînement et de test.
13. **Pipeline**: Permet de chaîner plusieurs étapes de traitement de données et de modélisation.
14. **StandardScaler**: Permet de normaliser les données d'entrée.
15. **MinMaxScaler**: Permet de mettre à l'échelle les données d'entrée entre 0 et 1.
16. **OneHotEncoder**: Permet de convertir les variables catégorielles en variables binaires.
17. **LabelEncoder**: Permet de convertir les variables catégorielles en variables numériques.
18. **DecisionTreeClassifier**: Permet de créer un arbre de décision pour la classification.
19. **RandomForestClassifier**: Permet de créer un modèle de forêt aléatoire pour la classification.
20. **GradientBoostingClassifier**: Permet de créer un modèle de boosting de gradient pour la classification.

1. **fit**: Permet de remplir le modèle avec des données d’entraînement.
from sklearn.linear_model import LinearRegression
# Créer un objet de modèle
model = LinearRegression()
# Remplir le modèle avec des données d'entraînement
model.fit(X_train, y_train)

2. **predict**: Permet de prédire les valeurs cibles pour les données d’entrée.
# Prédire les valeurs cibles pour les données d'entrée
y_pred = model.predict(X_test)

3. **transform**: Permet de transformer les données d’entrée en un format compatible avec le modèle.
from sklearn.preprocessing import StandardScaler
# Créer un objet de transformateur
scaler = StandardScaler()
# Transformer les données d'entrée en un format compatible avec le modèle
X_train_scaled = scaler.transform(X_train)

4. **fit_transform**: Permet de remplir le modèle avec des données d’entraînement et de transformer les données d’entrée en un format compatible avec le modèle.
# Remplir le modèle avec des données d'entraînement et transformer les données d'entrée en un format compatible avec le modèle
X_train_scaled = scaler.fit_transform(X_train)

5. **score**: Permet de calculer la précision du modèle sur les données de test.
# Calculer la précision du modèle sur les données de test
model.score(X_test, y_test)

6. **get_params**: Permet d’obtenir les paramètres du modèle.
# Obtenir les paramètres du modèle
model.get_params()

7. **set_params**: Permet de définir les paramètres du modèle.
# Définir les paramètres du modèle
model.set_params(normalize=True)
8. **GridSearchCV**: Permet de rechercher les meilleurs paramètres pour un modèle donné.
from sklearn.model_selection import GridSearchCV
from sklearn.svm import SVC
# Créer un objet de modèle
model = SVC()
# Définir les paramètres à rechercher
param_grid = {'C': [0.1, 1, 10], 'kernel': ['linear', 'rbf']}
# Rechercher les meilleurs paramètres pour le modèle
grid_search = GridSearchCV(model, param_grid)
grid_search.fit(X_train, y_train)

9. **RandomizedSearchCV**: Permet de rechercher les meilleurs paramètres pour un modèle donné en utilisant une recherche aléatoire.
from sklearn.model_selection import RandomizedSearchCV
from sklearn.ensemble import RandomForestClassifier
# Créer un objet de modèle
model = RandomForestClassifier()
# Définir les paramètres à rechercher
param_distributions = {'n_estimators': [10, 100, 1000], 'max_depth': [None, 5, 10]}
# Rechercher les meilleurs paramètres pour le modèle
random_search = RandomizedSearchCV(model, param_distributions)
random_search.fit(X_train, y_train)

10. **cross_val_score**: Permet de calculer la précision du modèle en utilisant la validation croisée.
from sklearn.model_selection import cross_val_score
from sklearn.tree import DecisionTreeClassifier
# Créer un objet de modèle
model = DecisionTreeClassifier()
# Calculer la précision du modèle en utilisant la validation croisée
scores = cross_val_score(model, X, y, cv=5)

11. **KFold**: Permet de diviser les données en k groupes pour la validation croisée.
from sklearn.model_selection import KFold
# Créer un objet de diviseur de données
kf = KFold(n_splits=5)
# Diviser les données en k groupes pour la validation croisée
for train_index, test_index in kf.split(X):
    X_train, X_test = X[train_index], X[test_index]
    y_train, y_test = y[train_index], y[test_index]

12. **train_test_split**: Permet de diviser les données en ensembles d’entraînement et de test.
from sklearn.model_selection import train_test_split
# Diviser les données en ensembles d'entraînement et de test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

13. **Pipeline**: Permet de chaîner plusieurs étapes de traitement de données et de modélisation.
from sklearn.pipeline import Pipeline
from sklearn.decomposition import PCA
from sklearn.linear_model import LogisticRegression

# Créer un objet de pipeline
pipe = Pipeline([('pca', PCA()), ('logistic', LogisticRegression())])

# Remplir le pipeline avec des données d'entraînement et entraîner le modèle
pipe.fit(X_train, y_train)

14. **StandardScaler**: Permet de normaliser les données d’entrée.
from sklearn.preprocessing import StandardScaler
# Créer un objet de normaliseur
scaler = StandardScaler()
# Normaliser les données d'entrée
X_train_scaled = scaler.fit_transform(X_train)

15. **MinMaxScaler**: Permet de mettre à l’échelle les données d’entrée entre 0 et 1.
from sklearn.preprocessing import MinMaxScaler
# Créer un objet de mise à l'échelle
scaler = MinMaxScaler()
# Mettre à l'échelle les données d'entrée entre 0 et 1
X_train_scaled = scaler.fit_transform(X_train)

16. **OneHotEncoder**: Permet de convertir les variables catégorielles en variables binaires.
from sklearn.preprocessing import OneHotEncoder
# Créer un objet de convertisseur
encoder = OneHotEncoder()
# Convertir les variables catégorielles en variables binaires
X_train_encoded = encoder.fit_transform(X_train)

17. **LabelEncoder**: Permet de convertir les variables catégorielles en variables numériques.
from sklearn.preprocessing import LabelEncoder
# Créer un objet de convertisseur
encoder = LabelEncoder()
# Convertir les variables catégorielles en variables numériques
y_train_encoded = encoder.fit_transform(y_train)

18. **DecisionTreeClassifier**: Permet de créer un arbre de décision pour la classification.
from sklearn.tree import DecisionTreeClassifier
# Créer un objet de modèle
model = DecisionTreeClassifier()
# Remplir le modèle avec des données d'entraînement
model.fit(X_train, y_train)

19. **RandomForestClassifier**: Permet de créer un modèle de forêt aléatoire pour la classification.
from sklearn.ensemble import RandomForestClassifier
# Créer un objet de modèle
model = RandomForestClassifier()
# Remplir le modèle avec des données d'entraînement
model.fit(X_train, y_train)

20. **GradientBoostingClassifier**: Permet de créer un modèle de boosting de gradient pour la classification.
from sklearn.ensemble import GradientBoostingClassifier
# Créer un objet de modèle
model = GradientBoostingClassifier()
# Remplir le modèle avec des données d'entraînement
model.fit(X_train, y_train)

# VALEURS PAR DEFAUT
**GridSearchCV**: Les valeurs par défaut pour GridSearchCV sont:

estimator: None.
param_grid: None.
scoring: None.
cv: None.


**RandomForestClassifier**: Les valeurs par défaut pour RandomForestClassifier sont:

n_estimators: 100.
criterion: “gini”.
max_depth: None.
min_samples_split: 2.
min_samples_leaf: 1.
min_weight_fraction_leaf: 0.0.
max_features: “auto”.
max_leaf_nodes: None.
min_impurity_decrease: 0.0.
min_impurity_split: None.
bootstrap: True.
oob_score: False.
n_jobs: None.
random_state: None.
verbose: 0.
warm_start: False.
class_weight: None.
ccp_alpha: 0.0.
max_samples: None.

**DecisionTreeClassifier**: Les valeurs par défaut pour DecisionTreeClassifier sont:

criterion: “gini”.
splitter: “best”.
max_depth: None.
min_samples_split: 2.
min_samples_leaf: 1.
min_weight_fraction_leaf: 0.0.
max_features: None.
random_state: None.
max_leaf_nodes: None.
min_impurity_decrease: 0.0.
min_impurity_split: None.
class_weight: None.
ccp_alpha: 0.0.

**LogisticRegression**: Les valeurs par défaut pour LogisticRegression sont:

penalty: “l2”.
dual: False.
tol: 0.0001.
C: 1.0.
fit_intercept: True.
intercept_scaling: 1.
class_weight: None.
random_state: None.
solver: “lbfgs”.
max_iter: 100.
multi_class: “auto”.
verbose: 0.
warm_start: False.
n_jobs: None.
l1_ratio: None.


**DecisionTreeRegressor**: Les valeurs par défaut pour DecisionTreeRegressor sont:

criterion: “mse”.
splitter: “best”.
max_depth: None.
min_samples_split: 2.
min_samples_leaf: 1.
min_weight_fraction_leaf: 0.0.
max_features: None.
random_state: None.
max_leaf_nodes: None.
min_impurity_decrease: 0.0.
min_impurity_split: None.
ccp_alpha: 0.0.

**GradientBoostingClassifier**: Les valeurs par défaut pour GradientBoostingClassifier sont:

loss: “deviance”.
learning_rate: 0.1.
n_estimators: 100.
subsample: 1.0.
criterion: “friedman_mse”.
`min_samples
