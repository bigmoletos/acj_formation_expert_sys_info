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

## Infrastructure

Pour un déploiement haute disponibilité de WordPress avec MySQL sur Kubernetes, voici la configuration d'infrastructure recommandée. Cette configuration garantit que les services sont répartis sur plusieurs nœuds pour assurer la résilience et la disponibilité.

### Configuration de l'Infrastructure

#### Nœud Maître Kubernetes : 1 VM

- **Rôle** : Gère le plan de contrôle Kubernetes, incluant les composants API server, scheduler, controller manager, etcd.
- **Ressources** : Minimum 2 vCPU et 4 Go de RAM.
- **Détails** : Le nœud maître orchestre les déploiements et gère l’état du cluster. Il ne doit pas exécuter d’applications pour éviter toute surcharge.

#### Nœuds Workers Kubernetes : 4 VM

- **Rôle** : Héberger les pods d'applications, comme WordPress et MySQL.
- **Ressources par VM** : Minimum 2 vCPU et 4 Go de RAM (à ajuster selon les besoins de charge).
- **Détails** :
  - 2 VM pour WordPress : Pour héberger l'application WordPress et répartir la charge de manière redondante.
  - 2 VM pour MySQL : Pour héberger la base de données MySQL en configuration de réplication (ou cluster si nécessaire) pour assurer la haute disponibilité.

#### Stockage Persistant : 2 volumes de stockage externe (ou persistent volumes si le stockage est intégré au cluster)

- **Rôle** : Fournir un stockage persistant pour MySQL et WordPress.
- **Détails** : Utilisé pour conserver les données de la base MySQL et les fichiers de WordPress même en cas de redémarrage des pods.

#### Réseau

- **Ingress ou Load Balancer** : Pour exposer WordPress de manière sécurisée en externe.
- **IP Statique** : Associe une IP statique au service Ingress pour un accès constant à l’application.

### Résumé de l'Infrastructure

| Type de VM | Rôle                | Quantité | CPU | RAM  | Exemple de Pods Hébergés         |
|------------|---------------------|----------|-----|------|-----------------------------------|
| Maître     | Nœud de contrôle    | 1        | 2+  | 4G+  | Aucun (plan de contrôle)          |
| Worker     | Nœud applicatif     | 2        | 2+  | 4G+  | WordPress pods (2 réplicas)      |
| Worker     | Nœud applicatif     | 2        | 2+  | 4G+  | MySQL pods (2 réplicas)          |

### Points Clés pour le Déploiement

- **Stockage Persistant** : Configure un stockage persistant (Persistent Volume Claims - PVC) pour MySQL et WordPress pour ne pas perdre les données en cas de redémarrage des pods.
- **Réplication MySQL** : Si nécessaire, configure MySQL en mode réplication pour assurer la haute disponibilité et la synchronisation des données entre les instances.
- **Service Ingress** : Utilise un Ingress Controller pour gérer l’accès public de manière sécurisée et centralisée.
- **Surveillance et Résilience** : Utilise des outils comme Prometheus et Grafana pour surveiller la santé du cluster, et configure des stratégies de redémarrage pour les pods pour qu’ils redémarrent en cas de panne.

Avec cette infrastructure, tu pourras garantir la haute disponibilité de WordPress et MySQL, en assurant une répartition des services sur plusieurs nœuds pour la résilience et l’évolutivité.

## Installation des Paquets sur Chaque VM

### Installation de Docker

Pour installer Docker sur chaque VM, utilise les commandes suivantes :

```shell
# Ajouter la clé GPG officielle de Docker
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Ajouter le dépôt à la liste des sources Apt
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

# Mettre à jour les paquets et installer Docker
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose-plugin
```

### Installation de Kubernetes

Pour installer Kubernetes, tu peux utiliser `snap`. Voici les commandes à exécuter sur chaque VM :

```shell
# Installer snapd si ce n'est pas déjà fait
sudo apt update
sudo apt install snapd

# Installer Kubernetes
sudo snap install kubectl --classic
```

### Configuration de Kubernetes

Après l'installation, tu devras configurer Kubernetes sur chaque nœud worker. Assure-toi que les nœuds peuvent communiquer entre eux et que le nœud maître est configuré correctement.

---

Avec ces étapes, tu devrais être en mesure de déployer WordPress et MySQL sur Kubernetes avec GitLab CI/CD, tout en garantissant une infrastructure robuste et hautement disponible.