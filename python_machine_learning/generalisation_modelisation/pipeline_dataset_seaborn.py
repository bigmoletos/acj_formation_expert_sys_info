# Importations nécessaires
import seaborn as sns
from sklearn.datasets import load_iris, load_wine, load_breast_cancer, load_digits, load_diabetes
import pandas as pd
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.impute import SimpleImputer
from sklearn.model_selection import GridSearchCV, StratifiedKFold, KFold, train_test_split
from sklearn.metrics import accuracy_score, classification_report, r2_score
import matplotlib.pyplot as plt
import seaborn as sns
from abc import ABC, abstractmethod
'''
Explications Détaillées
Classes de Modèles avec Polymorphisme :

BaseModel : Classe abstraite définissant les méthodes get_model et get_param_grid.
Classes spécifiques (e.g., LogisticRegressionModel, SVCModel, etc.) : Héritent de BaseModel et implémentent les méthodes abstraites, fournissant le modèle et sa grille d'hyperparamètres.
Chargement des Datasets :

Scikit-learn Datasets : Chargement et conversion en DataFrame avec une colonne target.
Seaborn Datasets : Chargement des datasets planets, tips, penguins, et diamonds. Pour planets, une transformation manuelle des catégories de method en valeurs numériques est effectuée.
Prétraitement des Données :

Gestion des Valeurs Manquantes : Utilisation de SimpleImputer avec stratégie median pour les numériques et most_frequent pour les catégorielles.
Encodage des Variables Catégorielles : Utilisation de OneHotEncoder avec gestion des catégories inconnues.
Standardisation : Utilisation de StandardScaler pour les caractéristiques numériques.
Gestionnaire de Pipeline avec GridSearchCV :

Pipeline : Combinaison des étapes de prétraitement et du modèle.
GridSearchCV : Recherche exhaustive des hyperparamètres définis dans la grille pour chaque modèle.
Évaluation : Utilisation de la validation croisée pour évaluer les performances (accuracy pour la classification et r2 pour la régression).
Compilation et Visualisation des Résultats :

DataFrame des Résultats : Stockage des scores moyens, écarts-types et meilleurs hyperparamètres pour chaque combinaison dataset-modèle.
Visualisations : Utilisation de boxplot et heatmap pour comparer les performances des modèles.
'''

# 2. Définition des Classes de Modèles (Polymorphisme)
# Nous allons définir une classe abstraite BaseModel qui servira de base à tous les modèles.
# Chaque modèle spécifique héritera de cette classe et définira ses propres hyperparamètres.


# Classe de base abstraite pour les modèles
class BaseModel(ABC):

    def __init__(self):
        self.model = None
        self.param_grid = {}

    @abstractmethod
    def get_model(self):
        pass

    @abstractmethod
    def get_param_grid(self):
        pass


# Classe pour Logistic Regression
from sklearn.linear_model import LogisticRegression


class LogisticRegressionModel(BaseModel):

    def __init__(self):
        super().__init__()
        self.model = LogisticRegression(max_iter=1000)

    def get_model(self):
        return self.model

    def get_param_grid(self):
        return {
            'classifier__C': [0.1, 1, 10, 100],
            'classifier__solver': ['liblinear', 'lbfgs']
        }


# Classe pour SVC
from sklearn.svm import SVC


class SVCModel(BaseModel):

    def __init__(self):
        super().__init__()
        self.model = SVC(probability=True)

    def get_model(self):
        return self.model

    def get_param_grid(self):
        return {
            'classifier__C': [0.1, 1, 10],
            'classifier__gamma': ['scale', 'auto', 0.1, 1],
            'classifier__kernel': ['linear', 'rbf', 'poly']
        }


# Classe pour Random Forest
from sklearn.ensemble import RandomForestClassifier


class RandomForestModel(BaseModel):

    def __init__(self):
        super().__init__()
        self.model = RandomForestClassifier(random_state=42)

    def get_model(self):
        return self.model

    def get_param_grid(self):
        return {
            'classifier__n_estimators': [100, 200],
            'classifier__max_depth': [None, 10, 20],
            'classifier__min_samples_split': [2, 5],
            'classifier__min_samples_leaf': [1, 2]
        }


# Classe pour Gradient Boosting
from sklearn.ensemble import GradientBoostingClassifier


class GradientBoostingModel(BaseModel):

    def __init__(self):
        super().__init__()
        self.model = GradientBoostingClassifier(random_state=42)

    def get_model(self):
        return self.model

    def get_param_grid(self):
        return {
            'classifier__n_estimators': [100, 200],
            'classifier__learning_rate': [0.01, 0.1],
            'classifier__max_depth': [3, 5]
        }


# Classe pour K-Nearest Neighbors
from sklearn.neighbors import KNeighborsClassifier


class KNeighborsModel(BaseModel):

    def __init__(self):
        super().__init__()
        self.model = KNeighborsClassifier()

    def get_model(self):
        return self.model

    def get_param_grid(self):
        return {
            'classifier__n_neighbors': [3, 5, 7],
            'classifier__weights': ['uniform', 'distance'],
            'classifier__metric': ['euclidean', 'manhattan']
        }


# Classe pour Decision Tree
from sklearn.tree import DecisionTreeClassifier


class DecisionTreeModel(BaseModel):

    def __init__(self):
        super().__init__()
        self.model = DecisionTreeClassifier(random_state=42)

    def get_model(self):
        return self.model

    def get_param_grid(self):
        return {
            'classifier__max_depth': [None, 10, 20],
            'classifier__min_samples_split': [2, 5],
            'classifier__min_samples_leaf': [1, 2]
        }


# Classe pour Gaussian NB
from sklearn.naive_bayes import GaussianNB


class GaussianNBModel(BaseModel):

    def __init__(self):
        super().__init__()
        self.model = GaussianNB()

    def get_model(self):
        return self.model

    def get_param_grid(self):
        return {'classifier__var_smoothing': [1e-09, 1e-08, 1e-07]}


#  3. Fonctions de Chargement et Prétraitement des Datasets
# Fonction pour charger les datasets
def load_datasets():
    datasets = {}

    # Datasets scikit-learn
    sklearn_datasets = {
        'Iris': load_iris(),
        'Wine': load_wine(),
        'Breast Cancer': load_breast_cancer(),
        'Digits': load_digits(),
        'Diabetes': load_diabetes()
    }

    for name, data in sklearn_datasets.items():
        df = pd.DataFrame(data.data, columns=data.feature_names)
        df['target'] = data.target
        datasets[name] = df

    # Datasets seaborn
    seaborn_datasets = ['planets', 'tips', 'penguins', 'diamonds']
    for name in seaborn_datasets:
        df = sns.load_dataset(name)
        # Prétraitement spécifique pour certains datasets si nécessaire
        if name == 'planets':
            # Transformation manuelle des catégories de 'method' en valeurs numériques
            method_mapping = {
                'Radial Velocity': 1,
                'Transit': 2,
                'Astrometry': 3,
                'Transit Timing Variations': 4,
                'Orbital Brightness Modulation': 5,
                'Pulsar Timing': 6
            }
            df["method_numeric"] = df["method"].map(method_mapping)
            df.drop(columns=["method"], inplace=True)
            target_column = 'method_numeric'
        elif name == 'tips':
            target_column = 'tip'
        elif name == 'penguins':
            target_column = 'species'
        elif name == 'diamonds':
            target_column = 'price'

        datasets[name.capitalize()] = df

    return datasets


# Fonction de prétraitement
def preprocess_data(df, target_column):
    X = df.drop(columns=[target_column])
    y = df[target_column]

    # Identifier les types de colonnes
    numeric_features = X.select_dtypes(
        include=['int64', 'float64']).columns.tolist()
    categorical_features = X.select_dtypes(
        include=['object', 'category', 'bool']).columns.tolist()

    # Pipelines pour les caractéristiques numériques et catégorielles
    numeric_transformer = Pipeline(
        steps=[('imputer',
                SimpleImputer(strategy='median')), ('scaler',
                                                    StandardScaler())])

    categorical_transformer = Pipeline(
        steps=[('imputer', SimpleImputer(strategy='most_frequent')
                ), ('onehot', OneHotEncoder(handle_unknown='ignore'))])

    # Combiner les transformations
    preprocessor = ColumnTransformer(
        transformers=[('num', numeric_transformer, numeric_features
                       ), ('cat', categorical_transformer,
                           categorical_features)])

    return X, y, preprocessor


#     4. Gestionnaire de Pipeline
# Cette partie gère l'entraînement, la recherche d'hyperparamètres et l'évaluation des modèles.
# Fonction d'évaluation avec GridSearchCV
def evaluate_model_with_gridsearch(clf,
                                   param_grid,
                                   X,
                                   y,
                                   is_classification=True):
    if is_classification:
        cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
        scoring = 'accuracy'
    else:
        cv = KFold(n_splits=5, shuffle=True, random_state=42)
        scoring = 'r2'

    grid_search = GridSearchCV(clf,
                               param_grid,
                               cv=cv,
                               scoring=scoring,
                               n_jobs=-1,
                               verbose=0)
    grid_search.fit(X, y)

    mean_score = grid_search.best_score_
    std_score = grid_search.cv_results_['std_test_score'][
        grid_search.best_index_]
    best_params = grid_search.best_params_

    return mean_score, std_score, best_params


# 5. Visualisation des Résultats/
# Fonction de visualisation
def visualize_results(results_df):
    import matplotlib.pyplot as plt
    import seaborn as sns

    # Boxplot des scores par modèle
    plt.figure(figsize=(14, 8))
    sns.boxplot(x='Model', y='Mean Score', data=results_df)
    plt.title('Comparaison des performances des modèles (GridSearchCV)')
    plt.xlabel('Modèle')
    plt.ylabel('Score moyen')
    plt.xticks(rotation=45)
    plt.show()

    # Heatmap des scores moyens par modèle et dataset
    pivot_df = results_df.pivot("Dataset", "Model", "Mean Score")
    plt.figure(figsize=(14, 8))
    sns.heatmap(pivot_df, annot=True, cmap="viridis")
    plt.title('Heatmap des scores moyens par modèle et dataset (GridSearchCV)')
    plt.show()


# 6. Exécution du Pipeline

# Définir les modèles et leurs hyperparamètres via les classes
model_classes = [
    LogisticRegressionModel, SVCModel, RandomForestModel,
    GradientBoostingModel, KNeighborsModel, DecisionTreeModel, GaussianNBModel
]

# Initialiser les instances des modèles
models = {cls.__name__.replace('Model', ''): cls() for cls in model_classes}

# Initialiser une liste pour stocker les résultats
results = []

# Charger les datasets
datasets = load_datasets()

for name, df in datasets.items():
    print(f"\nTraitement du dataset : {name}")

    # Identifier la colonne cible
    if 'target' in df.columns:
        target = 'target'
        is_classification = True
    elif 'species' in df.columns:
        target = 'species'
        is_classification = True
    elif 'method_numeric' in df.columns:
        target = 'method_numeric'
        is_classification = True
    elif 'price' in df.columns:
        target = 'price'
        is_classification = False
    else:
        # Pour les autres datasets, définir une cible appropriée ou sauter
        print(f"Dataset {name} non supporté pour cette démonstration.")
        continue

    # Prétraitement des données
    X, y, preprocessor = preprocess_data(df, target)

    # Itérer sur chaque modèle
    for model_name, model_instance in models.items():
        print(f"  Modèle : {model_name}")

        # Créer un pipeline avec prétraitement et modèle
        clf = Pipeline(
            steps=[('preprocessor',
                    preprocessor), ('classifier', model_instance.get_model())])

        # Récupérer la grille d'hyperparamètres pour le modèle actuel
        param_grid = model_instance.get_param_grid()

        # Vérifier si une grille d'hyperparamètres est définie
        if not param_grid:
            print(
                f"    Pas de grille d'hyperparamètres définie pour {model_name}. Utilisation des paramètres par défaut."
            )

        # Évaluer le modèle avec GridSearchCV
        mean_score, std_score, best_params = evaluate_model_with_gridsearch(
            clf, param_grid, X, y, is_classification)

        # Enregistrer les résultats
        results.append({
            'Dataset': name,
            'Model': model_name,
            'Mean Score': mean_score,
            'Std Dev': std_score,
            'Best Params': best_params
        })
        print(f"    Score : {mean_score:.4f} ± {std_score:.4f}")
        print(f"    Meilleurs paramètres : {best_params}")

# Créer un DataFrame des résultats
results_df = pd.DataFrame(results)
print("\nRésumé des performances des modèles avec GridSearchCV :")
print(results_df)

# Visualiser les résultats
visualize_results(results_df)
