# %% [markdown]
# # Formation AJC
# ## Analyse des Variables Discrètes et Continues avec le Dataset Tips

# %% [markdown]
# ## Imports nécessaires

# %% Run Cell | Run Above | Debug Cell
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Configuration de l'affichage
plt.style.use('default')
sns.set_theme()
pd.set_option('display.max_columns', None)

# Configuration du logger
import logging

logger = logging.getLogger("analyse_variables")
logger.setLevel(logging.DEBUG)
handler = logging.StreamHandler()
handler.setFormatter(
    logging.Formatter('%(asctime)s - %(levelname)s - %(message)s'))
logger.addHandler(handler)

# %% [markdown]
# ## 1. Chargement et aperçu des données

# %% Run Cell | Run Above | Debug Cell
# Chargement du dataset tips
df = sns.load_dataset('tips')
logger.info("Structure du dataset tips :")
print("\nAperçu des données :")
print(df.head())
print("\nInformations sur les colonnes :")
print(df.info())

# %% [markdown]
# ## 2. Analyse Univariée
# ### 2.1 Variables Discrètes (Catégorielles)


# %% Run Cell | Run Above | Debug Cell
def analyser_variable_discrete(df, colonne):
    """
    Analyse une variable discrète avec un graphique en barres et des statistiques
    """
    plt.figure(figsize=(10, 5))

    # Graphique en barres
    sns.countplot(data=df, x=colonne)
    plt.title(f'Distribution de {colonne}')
    plt.xticks(rotation=45)

    # Calcul et affichage des fréquences
    freq = df[colonne].value_counts(normalize=True).round(3) * 100
    logger.info(f"\nFréquences pour {colonne} (%):\n{freq}")

    plt.show()


# Analyse des variables discrètes du dataset tips
variables_discretes = ['sex', 'smoker', 'day', 'time']
for colonne in variables_discretes:
    analyser_variable_discrete(df, colonne)

# %% [markdown]
# ### 2.2 Variables Continues


# %% Run Cell | Run Above | Debug Cell
def analyser_variable_continue(df, colonne):
    """
    Analyse une variable continue avec histogramme, boîte à moustaches et statistiques
    """
    plt.figure(figsize=(12, 4))

    # Histogramme
    plt.subplot(1, 2, 1)
    sns.histplot(data=df, x=colonne, kde=True)
    plt.title(f'Distribution de {colonne}')

    # Boîte à moustaches
    plt.subplot(1, 2, 2)
    sns.boxplot(data=df, y=colonne)
    plt.title(f'Boîte à moustaches de {colonne}')

    # Statistiques descriptives
    stats = df[colonne].describe().round(2)
    logger.info(f"\nStatistiques pour {colonne}:\n{stats}")

    plt.tight_layout()
    plt.show()


# Analyse des variables continues du dataset tips
variables_continues = ['total_bill', 'tip', 'size']
for colonne in variables_continues:
    analyser_variable_continue(df, colonne)

# %% [markdown]
# ## 3. Analyse Multivariée

# %% Run Cell | Run Above | Debug Cell
# Relation entre le montant total et le pourboire
plt.figure(figsize=(10, 6))
sns.scatterplot(data=df, x='total_bill', y='tip', hue='time')
plt.title("Relation entre montant total et pourboire")
plt.show()

# Matrice de corrélation pour les variables numériques
correlation_matrix = df[['total_bill', 'tip', 'size']].corr()

plt.figure(figsize=(8, 6))
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', center=0)
plt.title('Matrice de corrélation')
plt.show()

# Analyse des pourboires par jour et moment de la journée
plt.figure(figsize=(12, 6))
sns.boxplot(data=df, x='day', y='tip', hue='time')
plt.title("Distribution des pourboires par jour et moment")
plt.xticks(rotation=45)
plt.show()

# %% [markdown]
# ## Conclusions
#
# 1. **Variables Discrètes dans Tips** :
#    - sex : Genre du client
#    - smoker : Fumeur ou non
#    - day : Jour de la semaine
#    - time : Moment de la journée (Déjeuner/Dîner)
#
# 2. **Variables Continues dans Tips** :
#    - total_bill : Montant total de l'addition
#    - tip : Montant du pourboire
#    - size : Taille du groupe
#
# 3. **Relations Observées** :
#    - Corrélation entre le montant total et le pourboire
#    - Variations des pourboires selon le moment de la journée
#    - Impact de la taille du groupe sur les montants
