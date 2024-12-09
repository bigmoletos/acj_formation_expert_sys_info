import numpy as np
import pickle

# Chemins vers les fichiers sauvegardés
model_filename = 'best_model_RandomForest.pkl'  # Par exemple, si c'est votre meilleur modèle
label_encoder_filename = 'label_encoder.pkl'
column_transformer_filename = 'column_transformer.pkl'
scaler_filename = 'scaler.pkl'

# Charger le modèle
with open(model_filename, 'rb') as f:
    model = pickle.load(f)

# Charger le label encoder (pour la colonne Genre, par ex.)
with open(label_encoder_filename, 'rb') as f:
    le = pickle.load(f)

# Charger le column transformer (pour la colonne Geography)
with open(column_transformer_filename, 'rb') as f:
    ct = pickle.load(f)

# Charger le scaler
with open(scaler_filename, 'rb') as f:
    sc = pickle.load(f)

# Supposons que lors de l'entraînement, la structure de X était :
# ['CreditScore', 'Geography', 'Gender', 'Age', 'Tenure', 'Balance',
#  'NumOfProducts', 'HasCrCard', 'IsActiveMember', 'EstimatedSalary']

# Exemple de données hypothétiques pour un client
input_data = np.array(
    [[600, "France", "Female", 40, 5, 50000.0, 1, 1, 1, 60000.0]],
    dtype=object)

# Le LabelEncoder s'appliquait sur le Genre (colonne 2 avant OneHot)
# On encode donc la colonne 2 (Gender)
input_data[:, 2] = le.transform(input_data[:, 2])

# Appliquer le ColumnTransformer (OneHotEncoder pour Geography)
input_data = ct.transform(input_data)

# Appliquer le scaler sur les données numériquement transformées
input_data = sc.transform(input_data)

# Une fois toutes les transformations faites, on peut prédire :
prediction = model.predict(input_data)

# Afficher le résultat
if prediction[0] == 1:
    print("Ce client est prédit comme quittant le service (churn).")
else:
    print("Ce client est prédit comme restant client.")
