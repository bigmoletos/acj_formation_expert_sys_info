#
#
# # sur la vm il faut creer un fichier  
# sudo touch ~/.bash_aliases
# #coller tout ce script dedans puis le loader depuis le 
# sudo nano ~/.bashrc
# # pour appeler ce bash il faut copier les lignes suivantes à la fin du bashrc
# # Charger les alias
# if [ -f ~/.bash_aliases ]; then
       # . ~/.bash_aliases
# fi 
#----------------------------
##### alias fd ###
#----------------------------

# export PATH="$HOME/script_perso:$PATH"
export PATH="/script_perso:$PATH"

# Ajouter /script_perso au PATH globalement si ce n'est pas déjà fait
if ! grep -Fxq 'export PATH="/script_perso:$PATH"' /etc/profile; then
    echo 'export PATH="/script_perso:$PATH"' | sudo tee -a /etc/profile
fi

# Alias de navigation
alias ..="cd .."
alias ...="cd ../.."
alias ....="cd ../../.."
alias ~="cd ~"          # Aller rapidement au repertoire personnel
alias c="clear"         # Effacer l'ecran
alias ll="ls -lahF"     # Liste detaillee avec des tailles lisibles
alias la="ls -A"        # Liste tous les fichiers, y compris les caches
alias l="ls -CF"        # Liste basique
alias home="cd ~"       # Aller au repertoire personnel
alias sdn="sudo nano "  # alias pous lancer un nano en mode sudo
alias sdc="sudo cat "  # alias pous lancer un cat en mode sudo
alias sd="sudo  "  # alias pous lancer un sudo
alias his="history  "  # alias pous avoir l'historique

# Alias pour lister les fichiers
alias ls="ls --color=auto"  # Colorer les fichiers et dossiers
alias lsd="ls -l | grep '^d'"  # Lister uniquement les repertoires
alias lt="ls -ltr"  # Liste les fichiers tries par date de modification (le plus recent a la fin)


# Alias pour les operations sur les fichiers
alias cp="cp -i"  # Copier avec confirmation (evite d'ecraser accidentellement des fichiers)
alias mv="mv -i"  # Deplacer avec confirmation
alias rm="rm -i"  # Supprimer avec confirmation
alias mkdir="mkdir -pv"  # Creer des repertoires de maniere recursive avec confirmation

# Alias pour les archives
alias untar="tar -xvf"  # Decompresser des fichiers tar
alias tgz="tar -czvf"  # Creer une archive tar.gz
alias untgz="tar -xzvf"  # Decompresser une archive tar.gz
alias zipf="zip -r"  # Creer un fichier ZIP
alias unzipf="unzip"  # Extraire un fichier ZIP

# Alias pour grep
alias grep="grep --color=auto"  # Colorer les resultats des recherches
alias findtext="grep -rnw ."  # Rechercher du texte dans les fichiers du repertoire courant

# Alias pour la gestion des paquets (exemples pour Debian/Ubuntu)
alias update="sudo apt update && sudo apt upgrade"  # Mettre a jour le systeme
alias install="sudo apt install"  # Installer un paquet
alias remove="sudo apt remove"  # Supprimer un paquet
alias search="apt search"  # Rechercher un paquet

# Alias pour Git
alias gts="git status"
alias gck="git checkout"
alias ga="git add"
alias gaa="git add ."
alias gcmsg="git commit -m"
alias gps="git push"
alias gpl="git pull"
alias glog="git log --oneline --graph --all --decorate"
alias gbr="git branch"

# Alias pour le reseau
alias myip="curl ifconfig.me"  # Obtenir l adresse IP publique
alias ports="netstat -tulanp"  # Afficher les ports ouverts
alias ping="ping -c 5"  # Limiter le nombre de pings a 5

# Alias pour la gestion des processus
alias psg="ps aux | grep -v grep | grep -i -e VSZ -e"  # Rechercher un processus
alias kill9="kill -9"  # Forcer l arret d un processus
alias meminfo="free -m -l -t"  # Afficher les informations sur la memoire


# Alias pour Docker
alias d='docker'  # Utiliser 'd' au lieu de 'docker'
alias dps='docker ps'  # Afficher les conteneurs en cours d'exécution
alias dpsa='docker ps -a'  # Afficher tous les conteneurs
alias di='docker images'  # Afficher les images Docker
alias dr='docker run'  # Exécuter un conteneur
alias drt='docker run -it'  # Exécuter un conteneur en mode interactif
alias dexec='docker exec -it'  # Exécuter une commande dans un conteneur en cours d'exécution
alias drm='docker rm'  # Supprimer un conteneur
alias rmi='docker rmi'  # Supprimer une image
alias dlogs='docker logs'  # Afficher les logs d'un conteneur
alias dstop='docker stop'  # Arrêter un conteneur
alias dstart='docker start'  # Démarrer un conteneur
alias dprune='docker system prune'  # Nettoyer les ressources inutilisées


# Alias pour Kubernetes
alias k='kubectl'  # Utiliser 'k' au lieu de 'kubectl'
alias kget='kubectl get'  # Obtenir des ressources
alias kgetp='kubectl get pods'  # Obtenir les pods
alias kgetd='kubectl get deployments'  # Obtenir les déploiements
alias kgetsvc='kubectl get services'  # Obtenir les services
alias kdesc='kubectl describe'  # Décrire une ressource
alias kdel='kubectl delete'  # Supprimer une ressource
alias kapply='kubectl apply -f'  # Appliquer un fichier de configuration
alias klogs='kubectl logs'  # Afficher les logs d'un pod
alias kexec='kubectl exec -it'  # Exécuter une commande dans un pod
alias kns='kubectl config set-context --current --namespace='  # Changer de namespace






# Charger la configuration
alias reload="source ~/.bashrc"

# Accés aux repertoires AJC
alias mnt="cd /mnt/c/AJC_formation"

# utilisation de sudo apt install bash-completion
# Activer bash-completion
if [ -f /etc/bash_completion ]; then
   . /etc/bash_completion
fi


