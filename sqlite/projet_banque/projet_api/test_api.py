import requests

# URL de l'API (si vous exécutez en local avec Docker, vérifiez que c'est bien accessible sur localhost:8000)
url = "http://localhost:8000/predict"

# Exemple de données client
client_data = {
    "CreditScore": 600,
    "Geography": "France",
    "Gender": "Female",
    "Age": 40,
    "Tenure": 5,
    "Balance": 50000.0,
    "NumOfProducts": 1,
    "HasCrCard": 1,
    "IsActiveMember": 1,
    "EstimatedSalary": 60000.0
}

# Envoyer la requête POST
response = requests.post(url, json=client_data)

# Vérifier le statut de la réponse
if response.status_code == 200:
    # Afficher le résultat renvoyé par l'API
    print("Réponse de l'API :")
    print(response.json())
else:
    print(
        f"Erreur lors de la requête. Code statut HTTP: {response.status_code}")
    print("Détails :")
    print(response.text)
