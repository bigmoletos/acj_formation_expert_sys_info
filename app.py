from fastapi import FastAPI
from pydantic import BaseModel
import pickle
import numpy as np
import uvicorn
import os

# Charger tous les objets nécessaires : modèle, encodeurs, scaler.
model_filename = r'C:\AJC_formation\sqlite\projet_banque\projet_api\best_model_RandomForest.pkl'

# # Obtenez le chemin absolu du fichier
# model_filename = os.path.abspath('./best_model_RandomForest.pkl')

# # Charger le modèle
# try:
#     with open(model_filename, 'rb') as f:
#         model = pickle.load(f)
# except FileNotFoundError:
#     raise FileNotFoundError(
#         f"Le fichier modèle '{model_filename}' est introuvable. Vérifiez le chemin et réessayez."
#     )

label_encoder_filename = './label_encoder.pkl'
column_transformer_filename = './column_transformer.pkl'
scaler_filename = './scaler.pkl'
# Charger le modèle
with open(model_filename, 'rb') as f:
    model = pickle.load(f)

# Charger le label encoder
with open(label_encoder_filename, 'rb') as f:
    le = pickle.load(f)

# Charger le column transformer
with open(column_transformer_filename, 'rb') as f:
    ct = pickle.load(f)

# Charger le scaler
with open(scaler_filename, 'rb') as f:
    sc = pickle.load(f)

app = FastAPI(title="API de prédiction de département de résidence",
              version="1.0.0")


# Les colonnes doivent correspondre aux mêmes variables d'entrée que lors de l'entraînement.
class CustomerData(BaseModel):
    CreditScore: float
    Geography: str
    Gender: str
    Age: int
    Tenure: int
    Balance: float
    NumOfProducts: int
    HasCrCard: int
    IsActiveMember: int
    EstimatedSalary: float


@app.post("/predict/")
async def predict(data: CustomerData):
    # Convertir les données entrantes en format numpy array
    # L'ordre doit correspondre à l'ordre d'origine des colonnes
    input_data = np.array([[
        data.CreditScore, data.Geography, data.Gender, data.Age, data.Tenure,
        data.Balance, data.NumOfProducts, data.HasCrCard, data.IsActiveMember,
        data.EstimatedSalary
    ]],
                          dtype=object)

    # Appliquer le LabelEncoder sur la colonne Genre (index 2)
    input_data[:, 2] = le.transform(input_data[:, 2])

    # Appliquer le ColumnTransformer sur la colonne Geography (index 1)
    input_data = ct.transform(input_data)

    # Appliquer le scaler
    input_data = sc.transform(input_data)

    # Retourner la prédiction
    prediction = model.predict(input_data)
    return {"prediction": int(prediction[0])}


if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
