# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
#[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    #alias grep='grep --color=auto'
    #alias fgrep='fgrep --color=auto'
    #alias egrep='egrep --color=auto'
fi

# colored GCC warnings and errors
#export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# some more ls aliases
#alias ll='ls -l'
#alias la='ls -A'
#alias l='ls -CF'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi
# ajouts fd
#export PATH="/usr/local/openssl/bin:$PATH"
#export LD_LIBRARY_PATH="/usr/local/openssl/lib:$LD_LIBRARY_PATH"
#export PATH="/usr/local/bin:$PATH"

#----------------------------
##### alias fd ###
#----------------------------
export PATH="$HOME/script_perso:$PATH"

# Alias de navigation
alias ..="cd .."
alias ...="cd ../.."
alias ....="cd ../../.."
alias ~="cd ~"          # Aller rapidement au répertoire personnel
alias c="clear"         # Effacer l'écran
alias ll="ls -lahF --color=auto"     # Liste détaillée avec des tailles lisibles
alias la="ls -A"        # Liste tous les fichiers, y compris les cachés
alias l="ls -CF"        # Liste basique
alias home="cd ~"       # Aller au répertoire personnel

# Alias pour lister les fichiers
alias ls="ls --color=auto"  # Colorer les fichiers et dossiers
alias lsd="ls -l | grep '^d'"  # Lister uniquement les répertoires
alias lt="ls -ltr"  # Liste les fichiers triés par date de modification (le plus récent à la fin)


# Alias pour les opérations sur les fichiers
alias cp="cp -i"  # Copier avec confirmation (évite d'écraser accidentellement des fichiers)
alias mv="mv -i"  # Déplacer avec confirmation
alias rm="rm -i"  # Supprimer avec confirmation
alias mkdir="mkdir -pv"  # Créer des répertoires de manière récursive avec confirmation

# Alias pour les archives
alias untar="tar -xvf"  # Décompresser des fichiers tar
alias tgz="tar -czvf"  # Créer une archive tar.gz
alias untgz="tar -xzvf"  # Décompresser une archive tar.gz
alias zipf="zip -r"  # Créer un fichier ZIP
alias unzipf="unzip"  # Extraire un fichier ZIP

# Alias pour grep
alias grep="grep --color=auto"  # Colorer les résultats des recherches
alias findtext="grep -rnw ."  # Rechercher du texte dans les fichiers du répertoire courant

# Alias pour la gestion des paquets (exemples pour Debian/Ubuntu)
alias update="sudo apt update && sudo apt upgrade"  # Mettre à jour le système
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

# Alias pour le réseau
alias myip="curl ifconfig.me"  # Obtenir l'adresse IP publique
alias ports="netstat -tulanp"  # Afficher les ports ouverts
alias ping="ping -c 5"  # Limiter le nombre de pings à 5

# Alias pour la gestion des processus
alias psg="ps aux | grep -v grep | grep -i -e VSZ -e"  # Rechercher un processus
alias kill9="kill -9"  # Forcer l'arrêt d'un processus
alias meminfo="free -m -l -t"  # Afficher les informations sur la mémoire

# Charger la configuration
alias reload="source ~/.bashrc"


