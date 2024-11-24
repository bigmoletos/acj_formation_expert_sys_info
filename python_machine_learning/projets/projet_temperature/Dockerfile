FROM python:3.12

WORKDIR /app

# Installation de Doxygen
RUN apt-get update && apt-get install -y doxygen graphviz

COPY requirements.txt .

RUN pip install --no-cache-dir -r requirements.txt

COPY . .

# Génération de la documentation (optionnel)
RUN doxygen Doxyfile || true

CMD ["flask", "run", "--host=0.0.0.0"]
