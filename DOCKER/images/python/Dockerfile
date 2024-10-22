# Utiliser une image Python officielle
FROM python:3.9-slim

# Définir le répertoire de travail dans le conteneur
WORKDIR /app

# Copier le fichier requirements.txt contenant les dépendances
COPY ./app/requirements.txt /app/requirements.txt
# Installer les dépendances nécessaires
RUN pip install --no-cache-dir -r requirements.txt

# Copier l'application FastAPI dans le conteneur
COPY ./app /app

# Exposer le port 8000 (port par défaut pour FastAPI)
EXPOSE 8000

# Commande pour démarrer l'application FastAPI avec Uvicorn
CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]
