# Scripts d'Installation Kubernetes

Ce répertoire contient des scripts automatisés pour l'installation de Kubernetes sur des machines Ubuntu, avec une configuration master-worker.

## Structure du Projet

```
C:\AJC_formation\docker\kubernetes\script_perso\
├── README.md
├── install_k8s_master.sh
└── install_k8s_worker.sh
```

## Prérequis

- Ubuntu Server (recommandé : 20.04 LTS ou plus récent)
- Minimum 2 GB RAM par machine
- Minimum 2 CPU par machine
- Connexion réseau entre les machines
- Droits sudo
- Ports ouverts :
  - Master : 6443, 2379-2380, 10250, 10251, 10252
  - Worker : 10250, 30000-32767

## Installation

1. Cloner ou copier les scripts sur les machines respectives :
```bash
git clone <url_repo> /tmp/k8s-scripts
cd /tmp/k8s-scripts
chmod +x install_k8s_*.sh
```

2. Sur le nœud master :
```bash
sudo ./install_k8s_master.sh
# ou en mode automatique
sudo ./install_k8s_master.sh -y
```

3. Noter les informations de jointure fournies à la fin de l'installation du master

4. Sur chaque nœud worker :
```bash
sudo ./install_k8s_worker.sh <numero_worker>
# ou en mode automatique avec les informations du master
sudo ./install_k8s_worker.sh -y <numero_worker> <ip_master> <token> <hash>
```

## Options des Scripts

### Script Master (install_k8s_master.sh)
```bash
Options:
    -h, --help      Affiche l'aide
    -y, --yes       Mode automatique (pas de demande de confirmation)
```

### Script Worker (install_k8s_worker.sh)
```bash
Options:
    -h, --help      Affiche l'aide
    -y, --yes       Mode automatique
Arguments:
    worker_number   Numéro du worker (obligatoire)
    master_ip       IP du master (optionnel en mode interactif)
    token          Token de jointure (optionnel en mode interactif)
    discovery_hash  Hash de découverte (optionnel en mode interactif)
```

## Logs et Résumé

Les scripts génèrent deux fichiers :
- `k8s_install.log` : Journal détaillé de l'installation
- `k8s_summary.md` : Résumé des actions effectuées

## Vérification de l'Installation

Sur le nœud master, vérifiez l'état du cluster :
```bash
kubectl get nodes
kubectl get pods --all-namespaces
```

## Dépannage

Si l'installation échoue :

1. Vérifiez les logs :
```bash
cat k8s_install.log
```

2. Reset Kubernetes si nécessaire :
```bash
sudo kubeadm reset
sudo systemctl stop kubelet
sudo systemctl disable kubelet
sudo rm -rf /etc/kubernetes/
```

3. Vérifiez les ports :
```bash
sudo netstat -tulpn | grep -E '6443|2379|2380|10250|10251|10252'
```

## Documentation Supplémentaire

Pour plus d'informations, consultez :
- [Documentation Kubernetes](https://kubernetes.io/docs/home/)
- [Guide d'installation Kubernetes](https://kubernetes.io/docs/setup/)
- Les fichiers dans `C:\AJC_formation\docker\kubernetes\` pour des informations spécifiques à votre environnement

## Contribution

Pour contribuer à l'amélioration de ces scripts :
1. Forkez le projet
2. Créez une branche pour votre fonctionnalité
3. Soumettez une pull request

## Licence

Ces scripts sont fournis "tels quels", sans garantie d'aucune sorte.

## Auteur

[Votre nom]

## Dernière mise à jour

[Date de la dernière mise à jour]