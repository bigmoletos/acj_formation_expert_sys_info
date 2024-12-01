
# Cheatsheet : Choisir un Modèle de Machine Learning

Ce cheatsheet vous aide à choisir un modèle de machine learning en fonction :
- **Du type de données (structurées/non structurées)**
- **De l'objectif (classification, régression, clustering, réduction de dimensionnalité)**

---

## 1. **Critère 1 : Quantité de Données**
- **Petites données (moins de 10 000 observations) :**
  - Préférer des modèles simples comme :
    - **Régression linéaire/logistique**
    - **K-Nearest Neighbors (KNN)**
    - **Decision Tree**
- **Données modérées (10 000 - 100 000 observations) :**
  - Modèles plus complexes comme :
    - **Random Forest**
    - **Gradient Boosting (XGBoost, LightGBM, CatBoost)**
- **Données massives (+100 000 observations) :**
  - Modèles performants à grande échelle :
    - **Descente de Gradient Stochastique (SGDClassifier, SGDRegressor)**
    - **Réseaux de Neurones (Deep Learning)**

---

## 2. **Critère 2 : Structure des Données**
- **Données structurées (tableau, features clairement définies) :**
  - Utilisez des modèles basés sur les arbres (**Random Forest, XGBoost**) ou des modèles linéaires (**Régression, SVM**).
- **Données non structurées (texte, images, audio) :**
  - **Texte :** NLP avec des modèles comme **TF-IDF + Logistic Regression**, ou des architectures modernes comme **Transformers (BERT, GPT)**.
  - **Images :** Réseaux de Neurones Convolutionnels (**CNNs**).
  - **Audio :** Modèles d'analyse spectrale ou **RNN**.

---

## 3. **Critère 3 : Objectif de l'Analyse**
### Classification (prédire une classe)
- **Exemples de modèles :**
  - **Logistic Regression** (simple, efficace pour données linéaires)
  - **Random Forest / Gradient Boosting** (données complexes, robustesse)
  - **SVM** (données linéairement/non linéairement séparables)
- **Exemple de Dataset :**
  - [Iris Dataset (Scikit-learn)](https://scikit-learn.org/stable/auto_examples/datasets/plot_iris_dataset.html)
    - Objectif : Classifier les fleurs en fonction de leur espèce.

### Régression (prédire une valeur continue)
- **Exemples de modèles :**
  - **Régression linéaire / Ridge / Lasso**
  - **Random Forest Regressor**
  - **Gradient Boosting Regressor (XGBoost, LightGBM)**
- **Exemple de Dataset :**
  - [Boston Housing Dataset (Seaborn)](https://seaborn.pydata.org/examples/many_facets.html)
    - Objectif : Prédire le prix des maisons.

### Clustering (regrouper des observations similaires)
- **Exemples de modèles :**
  - **K-Means** (rapide, facile à comprendre)
  - **DBSCAN** (robuste aux outliers)
  - **Gaussian Mixture Models (GMM)** (basé sur la probabilité)
- **Exemple de Dataset :**
  - [Planets Dataset (Seaborn)](https://seaborn.pydata.org/examples/index.html)
    - Objectif : Regrouper les exoplanètes selon leurs caractéristiques.

### Réduction de Dimensionnalité
- **Exemples de modèles :**
  - **PCA (Principal Component Analysis)** (linéaire)
  - **t-SNE / UMAP** (non linéaires, pour visualisation)
- **Exemple de Dataset :**
  - [Digits Dataset (Scikit-learn)](https://scikit-learn.org/stable/auto_examples/classification/plot_digits_classification.html)
    - Objectif : Réduire les dimensions pour visualiser des chiffres manuscrits.

---

## 4. **Critère 4 : Nature des Variables**
- **Quantitatives (numériques) :**
  - Modèles basés sur des moyennes ou des relations linéaires :
    - **Régression linéaire, Random Forest**
- **Qualitatives (catégoriques) :**
  - Modèles prenant en charge des variables catégorielles :
    - **Gradient Boosting (CatBoost, LightGBM)**, **Logistic Regression**

---

## 5. **Ressources et Datasets**

### Scikit-learn Datasets :
- **Iris Dataset :** [Lien ici](https://scikit-learn.org/stable/auto_examples/datasets/plot_iris_dataset.html)
- **Digits Dataset :** [Lien ici](https://scikit-learn.org/stable/auto_examples/classification/plot_digits_classification.html)
- **Boston Housing :** [Lien ici](https://scikit-learn.org/stable/datasets/toy_dataset.html#boston-dataset)

### Seaborn Datasets :
- **Planets Dataset :** [Lien ici](https://seaborn.pydata.org/examples/index.html)
- **Tips Dataset :** [Lien ici](https://seaborn.pydata.org/examples/index.html)

---

## 6. **Conseils Généraux**
1. **Toujours tester plusieurs modèles :**
   - Utilisez une bibliothèque comme `scikit-learn` pour créer des pipelines.
2. **Effectuer une validation croisée :**
   - Validez vos modèles avec **K-Fold Cross-Validation**.
3. **Hyperparamètres :**
   - Optimisez les hyperparamètres avec des outils comme **GridSearchCV** ou **RandomizedSearchCV**.
4. **Précaution avec les données :**
   - Vérifiez les outliers et les valeurs manquantes avant de choisir un modèle.

---

## 7. **Outils Recommandés**
- **Scikit-learn :** Pour modèles classiques.
- **Seaborn / Matplotlib :** Pour la visualisation.
- **TensorFlow / PyTorch :** Pour le Deep Learning.

---


https://scikit-learn.org/stable/machine_learning_map.html

https://www.youtube.com/watch?v=4mqKmTbAnHY

https://seaborn.pydata.org/examples/index.html

https://seaborn.pydata.org/examples/index.html