# ~/.bashrc: executed by bash(1) for non-login shells.

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# Set up Git Bash prompt
PS1='\[\033[01;32m\]\u@\h:\[\033[01;34m\]\w\[\033[00m\]$ '

# Enable colors for ls command
alias ls='ls --color=auto'

# Basic aliases for convenience
alias ll='ls -lh'
alias la='ls -A'
alias l='ls -CF'

# Enable Git command shortcuts
alias gs='git status'
alias ga='git add'
alias gc='git commit'
alias gp='git push'
alias gl='git log'
alias gco='git checkout'

# Set PATH to include custom script directories
export PATH="$HOME/bin:$HOME/.local/bin:$PATH"

# LS_COLORS settings (simplified)
export LS_COLORS='di=01;34:ln=01;36:so=01;35:pi=40;33:ex=01;32'

# Load .bash_aliases if it exists
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi


#----------------------------
##### alias fd ###
#----------------------------

export PATH="$HOME/script_perso:$PATH"

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

# Charger la configuration
alias reload="source ~/.bashrc"

# Accés aux repertoires AJC
alias mnt="cd /mnt/c/AJC_formation"