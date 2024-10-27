1. **GridSearchCV**: La principale métrique utilisée pour GridSearchCV est la précision du modèle sur les données de test. Les paramètres les plus couramment utilisés sont:

estimator: l’estimateur à utiliser pour ajuster les données.
param_grid: un dictionnaire de paramètres à ajuster.
scoring: la métrique à utiliser pour évaluer les performances du modèle.
cv: le nombre de split à utiliser pour la validation croisée.

2. **set_params**: Cette méthode permet de définir les paramètres d’un estimateur. Les paramètres les plus couramment utilisés sont:

normalize: booléen indiquant si les données doivent être normalisées ou non.
C: la force de régularisation.

3. **RandomForestClassifier**: Les principales métriques utilisées pour RandomForestClassifier sont la précision, le rappel et le score F1. Les paramètres les plus couramment utilisés sont:

n_estimators: le nombre d’arbres dans la forêt.
max_depth: la profondeur maximale de chaque arbre.
min_samples_split: le nombre minimum d’échantillons requis pour diviser un nœud interne.
min_samples_leaf: le nombre minimum d’échantillons requis pour être à une feuille.

4. **DecisionTreeClassifier**: Les principales métriques utilisées pour DecisionTreeClassifier sont la précision, le rappel et le score F1. Les paramètres les plus couramment utilisés sont:

max_depth: la profondeur maximale de l’arbre.
min_samples_split: le nombre minimum d’échantillons requis pour diviser un nœud interne.
min_samples_leaf: le nombre minimum d’échantillons requis pour être à une feuille.

5. **LogisticRegression**: Les principales métriques utilisées pour LogisticRegression sont la précision, le rappel et le score F1. Les paramètres les plus couramment utilisés sont:

C: la force de régularisation.
penalty: la norme de régularisation à utiliser.


6. **LogisticRegression**: Les principales métriques utilisées pour LogisticRegression sont la précision, le rappel et le score F1. Les paramètres les plus couramment utilisés sont:

C: la force de régularisation.

7. **penalty**: la norme de régularisation à utiliser.
StandardScaler: Cette méthode permet de normaliser les données d’entrée. Aucun paramètre n’est généralement utilisé.

OneHotEncoder: Cette méthode permet de convertir les variables catégorielles en variables binaires. Aucun paramètre n’est généralement utilisé.

LabelEncoder: Cette méthode permet de convertir les variables catégorielles en variables numériques. Aucun paramètre n’est généralement utilisé.

8. **DecisionTreeRegressor**: Les principales métriques utilisées pour DecisionTreeRegressor sont l’erreur quadratique moyenne et l’erreur absolue moyenne. Les paramètres les plus couramment utilisés sont:

max_depth: la profondeur maximale de l’arbre.
min_samples_split: le nombre minimum d’échantillons requis pour diviser un nœud interne.
min_samples_leaf: le nombre minimum d’échantillons requis pour être à une feuille.

9. **GradientBoostingClassifier**: Les principales métriques utilisées pour GradientBoostingClassifier sont la précision, le rappel et le score F1. Les paramètres les plus couramment utilisés sont:

n_estimators: le nombre d’estimateurs à utiliser.
max_depth: la profondeur maximale de chaque arbre.
min_samples_split: le nombre minimum d’échantillons requis pour diviser un nœud interne.
min_samples_leaf: le nombre minimum d’échantillons requis pour être à une feuille.

10. **Pipeline**: Les pipelines sont utilisés pour chaîner plusieurs étapes de traitement de données et de modélisation. Les paramètres les plus couramment utilisés sont les paramètres de l’estimateur final.