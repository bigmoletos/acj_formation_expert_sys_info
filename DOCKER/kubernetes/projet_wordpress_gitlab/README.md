# Déployer WordPress sur Kubernetes avec GitLab CI/CD

Déployer WordPress sur Kubernetes avec GitLab CI/CD implique de configurer un pipeline CI/CD qui utilise des fichiers de configuration Kubernetes (YAML) pour déployer à la fois l'application web WordPress et la base de données MySQL. Dans cet exemple, nous allons :

1. Configurer GitLab CI/CD avec un fichier `.gitlab-ci.yml`.
2. Créer les manifestes Kubernetes pour déployer WordPress et MySQL en mode haute disponibilité (deux réplicas chacun).
3. Déployer WordPress et MySQL sur un cluster Kubernetes.

## 1. Créer le fichier `.gitlab-ci.yml`

Le fichier `.gitlab-ci.yml` définit le pipeline CI/CD. Ce pipeline construit les images Docker si nécessaire, puis déploie les services sur Kubernetes.

## 2. Configurer les Manifests Kubernetes

Crée un répertoire `k8s/` dans ton dépôt Git pour stocker les fichiers de configuration Kubernetes (`mysql-deployment.yaml` et `wordpress-deployment.yaml`).

### `mysql-deployment.yaml`

Ce fichier de configuration crée un service et un déploiement pour MySQL avec deux réplicas.

```yaml
# Exemple de contenu pour mysql-deployment.yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: mysql
spec:
  replicas: 2
  selector:
    matchLabels:
      app: mysql
  template:
    metadata:
      labels:
        app: mysql
    spec:
      containers:
      - name: mysql
        image: mysql:5.7
        env:
        - name: MYSQL_ROOT_PASSWORD
          value: yourpassword
        ports:
        - containerPort: 3306
---
apiVersion: v1
kind: Service
metadata:
  name: mysql
spec:
  ports:
  - port: 3306
  selector:
    app: mysql
```

### `wordpress-deployment.yaml`

Ce fichier de configuration crée un service et un déploiement pour WordPress avec deux réplicas.

```yaml
# Exemple de contenu pour wordpress-deployment.yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: wordpress
spec:
  replicas: 2
  selector:
    matchLabels:
      app: wordpress
  template:
    metadata:
      labels:
        app: wordpress
    spec:
      containers:
      - name: wordpress
        image: wordpress:latest
        ports:
        - containerPort: 80
        env:
        - name: WORDPRESS_DB_HOST
          value: mysql
        - name: WORDPRESS_DB_USER
          value: root
        - name: WORDPRESS_DB_PASSWORD
          value: yourpassword
---
apiVersion: v1
kind: Service
metadata:
  name: wordpress
spec:
  ports:
  - port: 80
  selector:
    app: wordpress
```

## 3. Définir les Variables GitLab CI/CD

Pour que GitLab CI/CD puisse se connecter au cluster Kubernetes, configure une variable d'environnement appelée `KUBECONFIG_DATA` dans les paramètres du projet. Cette variable contiendra le contenu du fichier kubeconfig encodé en base64.

### Encoder le fichier kubeconfig

Encode ton fichier kubeconfig en base64 :

```shell
base64 < /path/to/your/kubeconfig
```

Ajoute cette chaîne encodée à GitLab CI/CD sous `KUBECONFIG_DATA`.

## 4. Déployer avec le Pipeline GitLab

Lorsque tu pushes ces modifications vers ton dépôt, le pipeline GitLab CI/CD s’exécute et déploie automatiquement WordPress et MySQL sur ton cluster Kubernetes.

## Tester le Déploiement

### Vérifier les Pods et Services

Après le déploiement, tu peux vérifier que les pods et les services sont correctement déployés :

```shell
kubectl get pods
kubectl get services
```

### Accéder à WordPress

Si ton cluster est configuré pour exposer des services externes, tu pourras accéder à WordPress via l’IP de l’un de tes nœuds et le port NodePort du service WordPress.

---

Ce pipeline GitLab CI/CD déploie WordPress et MySQL sur deux nœuds chacun, garantissant la haute disponibilité des services.