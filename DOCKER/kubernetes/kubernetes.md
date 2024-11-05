# installation

https://github.com/kubernetes/minikube/releases


## pre-requis

```bash
sudo apt update

sudo apt install -y docker.io

```

## kubectl : Kubernetes CLI

```bash
curl -LO "https://storage.googleapis.com/kubernetes-release/release/$(curl -s https://storage.googleapis.com/kubernetes-release/release/stable.txt)/bin/linux/amd64/kubectl"
chmod +x kubectl
sudo mv kubectl /usr/local/bin/

```


## Installer Minikube

```bash
curl -LO https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
sudo install minikube-linux-amd64 /usr/local/bin/minikube && rm minikube-linux-amd64



```

## Installer VirtualBox et s'assurer que VBoxManage est dans le PATH

```bash
sudo apt update
sudo apt install virtualbox virtualbox-ext-pack -y

```

## Démarrer Minikube

```bash
minikube start --driver=virtualbox
# vérifier que votre cluster est en cours d'exécution avec
kubectl get nodes


```

## Tester

```bash
kubectl create deployment hello-node --image=k8s.gcr.io/echoserver:1.4
kubectl expose deployment hello-node --type=LoadBalancer --port=8080
minikube service hello-node

```

## Commandes Utiles

### Vérifier les pods

```bash
kubectl get pods -A
```

### Déployer une application

```bash
kubectl create deployment my-app --image=nginx
```

### Exposer une application

```bash
kubectl expose deployment my-app --type=NodePort --port=80
```


```bash

```

```bash

```

```bash

```

```bash

```