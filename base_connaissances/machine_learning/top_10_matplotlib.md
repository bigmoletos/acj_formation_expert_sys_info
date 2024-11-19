1. **Histogramme**: Un histogramme est un graphique qui représente la distribution des données continues. Les principales métriques utilisées pour un histogramme sont la densité de probabilité et la fréquence.
import matplotlib.pyplot as plt
import numpy as np
# Créer des données aléatoires
data = np.random.randn(1000)
# Créer un histogramme
plt.hist(data, bins=30, density=True)
# Ajouter un titre et des étiquettes d'axe
plt.title('Histogramme')
plt.xlabel('Valeurs')
plt.ylabel('Densité de probabilité')
# Afficher le graphique
plt.show()

2. **Diagramme en boîte**: Un diagramme en boîte est un graphique qui représente la distribution des données continues. Les principales métriques utilisées pour un diagramme en boîte sont la médiane, le premier quartile, le troisième quartile et les valeurs aberrantes.
import matplotlib.pyplot as plt
import numpy as np
# Créer des données aléatoires
data = np.random.randn(1000)
# Créer un diagramme en boîte
plt.boxplot(data)
# Ajouter un titre et des étiquettes d'axe
plt.title('Diagramme en boîte')
plt.ylabel('Valeurs')
# Afficher le graphique
plt.show()

3. **Nuage de points**: Un nuage de points est un graphique qui représente la relation entre deux variables continues. Les principales métriques utilisées pour un nuage de points sont la corrélation et la covariance.
import matplotlib.pyplot as plt
import numpy as np
# Créer des données aléatoires
x = np.random.randn(1000)
y = np.random.randn(1000)
# Créer un nuage de points
plt.scatter(x, y)

# Ajouter un titre et des étiquettes d'axe
plt.title('Nuage de points')
plt.xlabel('Variable X')
plt.ylabel('Variable Y')
# Afficher le graphique
plt.show()

4. **Graphique en barres**: Un graphique en barres est un graphique qui représente la relation entre une variable catégorielle et une variable continue. Les principales métriques utilisées pour un graphique en barres sont la moyenne et l’écart type.
import matplotlib.pyplot as plt
import numpy as np
# Créer des données aléatoires
x = ['A', 'B', 'C', 'D', 'E']
y = np.random.rand(5)
# Créer un graphique en barres
plt.bar(x, y)
# Ajouter un titre et des étiquettes d'axe
plt.title('Graphique en barres')
plt.xlabel('Catégories')
plt.ylabel('Valeurs')
# Afficher le graphique
plt.show()

5. **Graphique à secteurs**: Un graphique à secteurs est un graphique qui représente la relation entre une variable catégorielle et une variable continue. Les principales métriques utilisées pour un graphique à secteurs sont la proportion et le pourcentage.
import matplotlib.pyplot as plt
# Créer des données aléatoires
x = [20, 30, 40, 10]
# Créer un graphique à secteurs
plt.pie(x)
# Ajouter un titre
plt.title('Graphique à secteurs')
# Afficher le graphique
plt.show()

6. **Graphique en aires**: Un graphique en aires est un graphique qui représente la relation entre une variable continue et le temps. Les principales métriques utilisées pour un graphique en aires sont la tendance et la saisonnalité.
import matplotlib.pyplot as plt
import numpy as np
# Créer des données aléatoires
x = np.arange(0, 10, 0.1)
y = np.sin(x)
# Créer un graphique en aires
plt.fill_between(x, y)
# Ajouter un titre et des étiquettes d'axe
plt.title('Graphique en aires')
plt.xlabel('Temps')
plt.ylabel('Valeurs')
# Afficher le graphique
plt.show()