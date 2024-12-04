import numpy as np
import gymnasium as gym
import time

# Initialisation de la graine et de l'environnement
seed_value = 42
np.random.seed(seed_value)
env = gym.make("Taxi-v3", render_mode="human")  # Mode human pour affichage
env.reset(seed=seed_value)

# Initialisation de la Q-Table
q_table = np.zeros([env.observation_space.n, env.action_space.n])

# Hyperparamètres
alpha = 0.1  # Taux d'apprentissage
gamma = 0.99  # Facteur de réduction
epsilon = 0.1  # Facteur d'exploration
num_episodes = 100  # Limité pour la démonstration
results = []

# Boucle d'entraînement sur plusieurs épisodes
for episode in range(num_episodes):
    print(f"Épisode {episode + 1}/{num_episodes}")
    state = env.reset()[0]  # Réinitialisation de l'environnement
    done = False

    while not done:
        # Choix de l'action (exploration vs exploitation)
        if np.random.uniform(0, 1) < epsilon:
            action = env.action_space.sample()  # Exploration
        else:
            action = np.argmax(q_table[state])  # Exploitation

        # Exécution de l'action et obtention du nouvel état
        next_state, reward, done, truncated, _ = env.step(action)

        # Calcul et mise à jour de la Q-Table
        old_value = q_table[state, action]
        next_max = np.max(q_table[next_state])
        q_table[state,
                action] = old_value + alpha * (reward + gamma * next_max -
                                               old_value)

        # Transition vers le nouvel état
        state = next_state

        # Affichage dans Pygame
        env.render()
        time.sleep(0.1)  # Pause pour ralentir l'animation

        if truncated:  # En cas de tronquage, considérer comme un échec
            done = True

        # Enregistrement du succès ou de l'échec de l'épisode
        if reward == 20:  # Succès si la récompense finale est 20
            results.append(1)
        else:
            results.append(0)

# Résumé de l'entraînement
print("\nEntraînement terminé.")
print(f"Taux de succès : {sum(results) / num_episodes:.2%}")

# Fermeture de l'environnement
env.close()
