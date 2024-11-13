import jax
import jax.numpy as jnp
from jax import random
from jax.nn import sigmoid, tanh

# Étape 1 : Créer une cellule LSTM avec JAX
# Commençons par définir une cellule LSTM simple en JAX :

# Initialisation des poids pour l'unité LSTM
def init_lstm_params(hidden_size, input_size, key):
    k1, k2 = random.split(key)
    W_f = random.normal(k1, (hidden_size, input_size))
    U_f = random.normal(k1, (hidden_size, hidden_size))
    b_f = jnp.zeros(hidden_size)

    W_i = random.normal(k2, (hidden_size, input_size))
    U_i = random.normal(k2, (hidden_size, hidden_size))
    b_i = jnp.zeros(hidden_size)

    W_c = random.normal(k1, (hidden_size, input_size))
    U_c = random.normal(k1, (hidden_size, hidden_size))
    b_c = jnp.zeros(hidden_size)

    W_o = random.normal(k2, (hidden_size, input_size))
    U_o = random.normal(k2, (hidden_size, hidden_size))
    b_o = jnp.zeros(hidden_size)

    return {
        'W_f': W_f,
        'U_f': U_f,
        'b_f': b_f,
        'W_i': W_i,
        'U_i': U_i,
        'b_i': b_i,
        'W_c': W_c,
        'U_c': U_c,
        'b_c': b_c,
        'W_o': W_o,
        'U_o': U_o,
        'b_o': b_o
    }


# Définir une étape LSTM
def lstm_step(params, h, c, x):
    f = sigmoid(
        jnp.dot(params['W_f'], x) + jnp.dot(params['U_f'], h) + params['b_f'])
    i = sigmoid(
        jnp.dot(params['W_i'], x) + jnp.dot(params['U_i'], h) + params['b_i'])
    o = sigmoid(
        jnp.dot(params['W_o'], x) + jnp.dot(params['U_o'], h) + params['b_o'])
    c_ = tanh(
        jnp.dot(params['W_c'], x) + jnp.dot(params['U_c'], h) + params['b_c'])
    c = f * c + i * c_
    h = o * tanh(c)
    return h, c

# Étape 2 : Boucle sur la séquence pour utiliser la cellule LSTM
# Une fois la cellule LSTM définie, nous pouvons l’appliquer sur une séquence d’entrée :

# Définir la fonction de prédiction
def lstm_predict(params, inputs, hidden_size):
    h = jnp.zeros(hidden_size)
    c = jnp.zeros(hidden_size)
    outputs = []

    # Boucle sur chaque pas temporel
    for x in inputs:
        h, c = lstm_step(params, h, c, x)
        outputs.append(h)

    return jnp.array(outputs)


# Étape 3 : Initialisation et prédiction sur vos données météorologiques
# Pour initialiser les paramètres et exécuter une prédiction :

# Taille des entrées et taille de l'état caché
input_size = 10  # à ajuster selon votre jeu de données météo
hidden_size = 20  # taille de l'état caché de l'LSTM



# Génération de données de test
key = random.PRNGKey(0)
params = init_lstm_params(hidden_size, input_size, key)

# Exemple d'entrée aléatoire
inputs = random.normal(key,
                       (50, input_size))  # une séquence de 50 pas de temps

# Prédiction
predictions = lstm_predict(params, inputs, hidden_size)

print(predictions)
