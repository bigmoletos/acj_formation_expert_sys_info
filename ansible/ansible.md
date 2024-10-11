# installation Ansible
 ## il faut créer un repertoire playbooks
 un fichier hosts.ini avec les ip des vm
 un fichier yml pour indiquer les actions d'update à faire

## Sur débian
```bash
sudo apt update
sudo apt install software-properties-common
sudo add-apt-repository --yes --update ppa:ansible/ansible
sudo apt update
sudo apt install ansible


ansible --version

```

# sur ubuntu

```bash

sudo apt update
sudo apt install software-properties-common
sudo add-apt-repository --yes --update ppa:ansible/ansible
sudo apt install ansible



ansible --version

```

- --ask-pass pour que Ansible te demande le mot de passe lors de l'exécution
```bash
ansible-playbook -i hosts.ini update_creationuser.yml --ask-pass
```

- option suivante lors de l'exécution de ton playbook pour ignorer la vérification de clé SSH :
```bash
ansible-playbook -i hosts.ini update_creationuser.yml --ssh-extra-args="-o StrictHostKeyChecking=no"
```


- pour créer une cle ssh
```bash
ssh-keygen -t ed25519 -C " cle ansible vmw debain Web wordpress vboxuserr@192.168.1.188"
```

- copier la clé ssh

```bash
ssh-copy-id -i ~/.ssh/id_ed25519.pub ton_utilisateur@192.168.X.XXX
```

```bash
ssh-copy-id -i ~/.ssh/id_ed25519.pub vboxuser@192.168.1.155
```

pour teste si on arrive à se connecter aux vm

```bash
ssh vboxuser@192.168.1.189
```
Avec l'option --ask-pass : Lorsque tu lances ton playbook, tu peux ajouter l'option --ask-pass pour que Ansible te demande le mot de passe lors de l'exécution :

```bash
ansible-playbook -i hosts.ini update_creationuser.yml --ask-pass
```

