import pandas as pd
import numpy as np
import pickle
from sklearn.model_selection import train_test_split, GridSearchCV, RandomizedSearchCV
from sklearn.preprocessing import StandardScaler, LabelEncoder, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

# Lire le dataset
dataset = pd.read_csv(r"C:\AJC_formation\data\csv\churn_modelling.csv")

# Séparation des variables indépendantes et dépendantes
x = dataset.iloc[:, 3:-1].values
y = dataset.iloc[:, -1].values

# Encodage des données catégorielles
# Encodage de la colonne Genre
le = LabelEncoder()
x[:, 2] = le.fit_transform(x[:, 2])

# Encodage de la colonne "Geography" avec OneHotEncoder
ct = ColumnTransformer(transformers=[('encoder', OneHotEncoder(drop='first'),
                                      [1])],
                       remainder='passthrough')
x = np.array(ct.fit_transform(x))

# Sauvegarde du LabelEncoder et du ColumnTransformer pour utilisation future
with open('label_encoder.pkl', 'wb') as le_file:
    pickle.dump(le, le_file)

with open('column_transformer.pkl', 'wb') as ct_file:
    pickle.dump(ct, ct_file)

#Division du dataset
x_train, x_test, y_train, y_test = train_test_split(x,
                                                    y,
                                                    test_size=0.2,
                                                    random_state=42)

print(x_train.shape, x_test.shape, y_train.shape, y_test.shape)

#Normalisation des donnees
sc = StandardScaler()
x_train = sc.fit_transform(x_train)
x_test = sc.transform(x_test)

# Sauvegarde du StandardScaler pour utilisation future
with open('scaler.pkl', 'wb') as sc_file:
    pickle.dump(sc, sc_file)

#Definir les modeles et le leur hyperparametres
models = {
    'RandomForest': {
        'model': RandomForestClassifier(random_state=42),
        'params': {
            'n_estimators': [100, 200, 300, 400],
            'max_depth': [10, 20, 30],
            'min_samples_leaf': [1, 2, 4],
            'min_samples_split': [2, 5, 10]
        }
    },
    'SVC': {
        'model': SVC(),
        'params': {
            'C': [0.1, 1, 10, 100],
            'kernel': ['linear', 'rbf', 'poly', 'sigmoid'],
            'gamma': ['scale', 'auto']
        }
    },
    'LogisticRegression': {
        'model': LogisticRegression(random_state=42),
        'params': {
            'C': [0.1, 1, 10, 100],
            'solver': ['newton-cg', 'lbfgs', 'liblinear'],
            'max_iter': [100, 200, 300]
        }
    }
}

# Effectuer une recherche d'hyperparamètres pour chaque modèle
best_models = {}
for model_name, model_dict in models.items():
    print(f"Entrainement et optimisation du modèle : {model_name}")
    grid_search = GridSearchCV(model_dict['model'],
                               model_dict['params'],
                               cv=5,
                               n_jobs=-1,
                               verbose=3)
    grid_search.fit(x_train, y_train)
    best_models[model_name] = grid_search.best_estimator_
    print(
        f"Meilleurs hyperparamètres pour {model_name}: {grid_search.best_params_}"
    )

# Évaluation de chaque modèle
for model_name, model in best_models.items():
    print(f"\nÉvaluation du modèle : {model_name}")
    y_pred = model.predict(x_test)
    accuracy = accuracy_score(y_test, y_pred)
    conf_matrix = confusion_matrix(y_test, y_pred)
    class_report = classification_report(y_test, y_pred)

    print(f"Accuracy: {accuracy * 100:.2f}%")
    print("Matrice de confusion :")
    print(conf_matrix)
    print("Rapport de classification :")
    print(class_report)

# Sauvegarder le meilleur modèle pour une utilisation future
best_model_name = max(
    best_models,
    key=lambda k: accuracy_score(y_test, best_models[k].predict(x_test)))
best_model = best_models[best_model_name]
with open(f'best_model_{best_model_name}.pkl', 'wb') as model_file:
    pickle.dump(best_model, model_file)

print(
    f"\nLe meilleur modèle est {best_model_name} avec une précision de {accuracy_score(y_test, best_model.predict(x_test)) * 100:.2f}%."
)
