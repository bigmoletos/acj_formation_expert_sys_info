# mettre python à jour
```python.exe -m pip install --upgrade pip```

#  installer Streamlit
```pip install streamlit```


# Installer virtualenv
```pip install virtualenv```

# Premier script Streamlit
## Créez un fichier, par exemple app.py, puis ajoutez
```bash
import streamlit as st
st.title('Mon premier app Streamlit')
st.write('Bienvenue dans cette application.')
```


# Créer un environnement virtuel
```python -m venv streamlit_env[text](../../../../../../WildCodeSchool/Formation_IA_DATA_nov2023/live_coding/flask/lancement_envi_virtuel_flask.md)```


# Activer l'environnement virtuel
```.\streamlit_env\Scripts\activate```


# Installer les packages
```pip install streamlit pandas numpy plotly seaborn scikit-learn pandas```

# Enregistrer les packages installés dans un fichier requirements.txt
```pip freeze > requirements.txt```

# Installer les packages à partir du fichier requirements.txt
```pip install -r requirements.txt```


# lancer le fichier app.py depuis le terminal !
```streamlit run app.py```
# pour arreter l'environnement virtuel
deactivate

# si besoin de désinstaller des prog
```pip uninstall streamlit pandas numpy plotly seaborn scikit-learn```

#  les templates par défaut doivent se trouver dans le repertoire à la racine de app.py dans un dossier templates
/my_streamlit_app
|-- /templates
|-- /static
|   |-- /images
|   |-- /css
|-- app.py

# sur le navigateur ou http://localhost:8501/


# TEMPLATE
## Affichage de données
Texte simple :
```bash
st.text('Affiche du texte simple.')
```
## Markdown :
```bash
st.markdown('**Markdown** _supporté_.')
```
## Messages d'alerte :
```bash
st.success('Succès!')
st.info('Information.')
st.warning('Attention.')
st.error('Erreur.')
```
## Latex :
```bash
st.latex(r''' e^{i\pi} + 1 = 0 ''')
```
# Widgets

## Bouton :
```bash
if st.button('Dis Bonjour'):
    st.write('Bonjour!')
```
## Case à cocher :
```bash
if st.checkbox('Afficher/Cachez'):
    st.text('Affiché!')
```
## Sélecteur :
```bash
option = st.selectbox('Choisissez un numéro:', [1, 2, 3])
st.write(f'Vous avez sélectionné: {option}')
```
## Curseur :
```bash
age = st.slider('Quel est votre âge?', 0, 130, 25)
st.write(f"J'ai {age} ans")
```
# Affichage de données complexes

## DataFrames :
```bash
import pandas as pd

df = pd.DataFrame({'col1': [1, 2, 3], 'col2': [4, 5, 6]})
st.dataframe(df)
```
## Graphiques :
```bash
import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots()
ax.hist(np.random.randn(1000), bins=30)
st.pyplot(fig)
```
# Mise en cache
## Utilisez le décorateur @st.cache pour mettre en cache le résultat d'une fonction coûteuse :

```bash
import time

@st.cache
def fonction_coûteuse(param):
    # Simulation d'une fonction coûteuse
    time.sleep(5)
    return param * 10

resultat = fonction_coûteuse(5)
st.write(resultat)
```
# Disposition
## Colonnes :
```bash
col1, col2 = st.columns(2)

with col1:
    st.header('Colonne 1')
    st.write('Quelque chose ici')

with col2:
    st.header('Colonne 2')
    st.write('Quelque chose là')
```
## Expander :
```bash
with st.expander("Voir détails"):
    st.write("Des détails cachés ici.")
```
