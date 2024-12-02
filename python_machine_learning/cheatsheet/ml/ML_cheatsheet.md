
# Cheatsheet : Différences entre Classification, Régression, Clustering, et Analyse de Dimensions

## 1. **Classification**
- **Objectif :** Prédire une catégorie ou une classe.
- **Type de sortie :** Discrète (e.g., {0, 1, 2}, "Spam"/"Non Spam").
- **Exemples de datasets :**
  - [Iris Dataset](https://archive.ics.uci.edu/ml/datasets/iris): Classification des espèces de fleurs.
  - [MNIST](http://yann.lecun.com/exdb/mnist/): Reconnaissance de chiffres manuscrits.
- **Exemples de modèles :**
  - K-Nearest Neighbors (KNN)
  - Logistic Regression
  - Random Forest
- **Application :**
  - Filtrage de spam
  - Détection de maladies

---

## 2. **Régression**
- **Objectif :** Prédire une valeur continue.
- **Type de sortie :** Continue (e.g., prix, température).
- **Exemples de datasets :**
  - [Boston Housing](https://archive.ics.uci.edu/ml/datasets/Housing): Prédiction des prix de l'immobilier.
  - [Diabetes Dataset](https://scikit-learn.org/stable/datasets/toy_dataset.html#diabetes-dataset): Prédiction de la progression du diabète.
- **Exemples de modèles :**
  - Linear Regression
  - Support Vector Regression (SVR)
  - Gradient Boosting
- **Application :**
  - Prédiction des ventes
  - Modélisation des cours boursiers

---

## 3. **Clustering**
- **Objectif :** Découper les données en groupes ou clusters similaires.
- **Type de sortie :** Groupes (pas d'étiquette prédéfinie).
- **Exemples de datasets :**
  - [Customer Segmentation Data](https://www.kaggle.com/arjunbhasin2013/ccdata): Segmentation de clients.
  - [Wine Dataset](https://archive.ics.uci.edu/ml/datasets/wine): Groupement de vins selon leurs caractéristiques.
- **Exemples de modèles :**
  - K-Means
  - DBSCAN
  - Hierarchical Clustering
- **Application :**
  - Segmentation de marché
  - Identification d’anomalies

---

## 4. **Analyse de Dimensions**
- **Objectif :** Réduire le nombre de dimensions tout en conservant l'information pertinente.
- **Type de sortie :** Représentation avec moins de dimensions.
- **Exemples de datasets :**
  - [Digits Dataset](https://scikit-learn.org/stable/auto_examples/datasets/plot_digits_last_image.html): Réduction de dimensions pour des données visuelles.
  - [World Happiness Report Data](https://www.kaggle.com/unsdsn/world-happiness): Réduction pour l’analyse des corrélations.
- **Exemples de techniques :**
  - PCA (Principal Component Analysis)
  - t-SNE (t-Distributed Stochastic Neighbor Embedding)
  - UMAP (Uniform Manifold Approximation and Projection)
- **Application :**
  - Visualisation de données complexes
  - Prétraitement avant classification ou clustering

---

## Résumé des différences
| Aspect              | Classification      | Régression         | Clustering          | Analyse de Dimensions |
|---------------------|---------------------|--------------------|---------------------|-----------------------|
| **Sortie**          | Catégories          | Valeurs continues  | Groupes             | Dimensions réduites   |
| **Supervisé ?**     | Oui                 | Oui                | Non                 | Non                   |
| **Applications**    | Spam, diagnostics   | Prix, prédictions  | Segmentation clients| Visualisation, PCA    |
| **Exemples de modèles** | SVM, KNN, RF     | LR, GBM, SVR       | K-Means, DBSCAN     | PCA, t-SNE, UMAP      |

---

## Visualisation des Concepts
### Classification

![Classification Example](https://upload.wikimedia.org/wikipedia/commons/6/6b/Scatter_diagram_with_linear_regression.svg)

### Régression
![Regression Example](https://upload.wikimedia.org/wikipedia/commons/3/3a/Linear_regression.svg)

### Clustering
![Clustering Example](https://upload.wikimedia.org/wikipedia/commons/e/ea/K-means_convergence.gif)

### Analyse de Dimensions
![Dimensionality Reduction Example](https://upload.wikimedia.org/wikipedia/commons/f/fb/PCA_iris.svg)

---

**Liens utiles :**
- [Scikit-learn User Guide](https://scikit-learn.org/stable/user_guide.html)
- [UCI Machine Learning Repository](https://archive.ics.uci.edu/ml/index.php)
- [Kaggle Datasets](https://www.kaggle.com/datasets)
