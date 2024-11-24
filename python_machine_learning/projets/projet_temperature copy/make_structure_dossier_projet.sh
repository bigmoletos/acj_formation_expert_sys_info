language:python_machine_learning/projets/projets2/make_structure_dossier_projet.sh
#!/bin/bash

##
# @file make_structure_dossier_projet.sh
# @brief Script de création de la structure du projet Temperature
# @details Crée l'arborescence complète du projet avec tous les fichiers nécessaires
# Vérifie l'existence des fichiers/dossiers avant création
##

# Couleurs pour les messages
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Variables pour les chemins
APP_DIR="app"
TEMPLATES_DIR="$APP_DIR/templates"
STATIC_DIR="$APP_DIR/static"
CSS_DIR="$STATIC_DIR/css"
JS_DIR="$STATIC_DIR/js"
DOCS_DIR="docs"
LOGS_DIR="logs"
TESTS_DIR="tests"

# Fichiers à créer
FILES=(
    "$APP_DIR/__init__.py"
    "$APP_DIR/routes.py"
    "$APP_DIR/models.py"
    "$APP_DIR/forms.py"
    "$APP_DIR/logging_config.py"
    "$TEMPLATES_DIR/index.html"
    "$TEMPLATES_DIR/weather.html"
    "$CSS_DIR/style.css"
    "$JS_DIR/main.js"
    ".env"
    # ".env.example"
    ".gitignore"
    "Dockerfile"
    "docker-compose.yml"
    "requirements.txt"
    "Makefile"
    "Doxyfile"
    "README.md"
    "ci-cd.yml"
    "$TESTS_DIR/__init__.py"
    "$TESTS_DIR/test_routes.py"
    "$TESTS_DIR/test_models.py"
    "$TESTS_DIR/conftest.py"
)

# Fonction d'aide
show_help() {
    echo -e "${BLUE}Usage${NC}: $0 [OPTIONS]"
    echo
    echo "Script de création de la structure du projet Temperature"
    echo
    echo -e "${BLUE}Options${NC}:"
    echo "  -h, --help     Affiche ce message d'aide"
    echo "  -f, --force    Force l'écrasement des fichiers existants"
    echo "  -y, --yes      Répond oui à toutes les questions"
    echo
    echo -e "${BLUE}Exemple${NC}:"
    echo "  $0 --force     Crée la structure en écrasant les fichiers existants"
    echo "  $0 --yes       Crée la structure en répondant oui à tout"
    exit 0
}

# Traitement des arguments
FORCE=false
AUTO_YES=false

for arg in "$@"; do
    case $arg in
        -h|--help)
            show_help
            ;;
        -f|--force)
            FORCE=true
            ;;
        -y|--yes)
            AUTO_YES=true
            ;;
    esac
done

# Fonction pour créer un dossier et afficher un message
create_dir() {
    local dir="$1"
    if [ -d "$dir" ]; then
        echo -e "${YELLOW}Le dossier existe déjà${NC}: $dir"
    else
        if $AUTO_YES; then
            mkdir -p "$dir"
            echo -e "${GREEN}Création du dossier${NC}: $dir"
        else
            read -p "Créer le dossier $dir ? (o/N) " response
            if [[ "$response" =~ ^[oO]$ ]]; then
                mkdir -p "$dir"
                echo -e "${GREEN}Création du dossier${NC}: $dir"
            else
                echo -e "${YELLOW}Ignoré${NC}: $dir"
            fi
        fi
    fi
}

# Fonction pour créer un fichier vide et afficher un message
create_file() {
    local file="$1"
    if [ -f "$file" ]; then
        if $FORCE; then
            touch "$file"
            echo -e "${YELLOW}Fichier écrasé${NC}: $file"
        else
            echo -e "${YELLOW}Le fichier existe déjà${NC}: $file"
            if ! $AUTO_YES; then
                read -p "Écraser le fichier $file ? (o/N) " response
                if [[ "$response" =~ ^[oO]$ ]]; then
                    touch "$file"
                    echo -e "${GREEN}Fichier écrasé${NC}: $file"
                else
                    echo -e "${YELLOW}Ignoré${NC}: $file"
                fi
            fi
        fi
    else
        touch "$file"
        echo -e "${GREEN}Création du fichier${NC}: $file"
    fi
}

# Vérification avant de commencer
if ! $AUTO_YES; then
    echo -e "${BLUE}Ce script va créer la structure du projet Temperature.${NC}"
    read -p "Voulez-vous continuer ? (o/N) " response
    if [[ ! "$response" =~ ^[oO]$ ]]; then
        echo -e "${RED}Opération annulée${NC}"
        exit 1
    fi
fi

# Création de la structure principale
create_dir "$APP_DIR"
create_dir "$TEMPLATES_DIR"
create_dir "$STATIC_DIR"
create_dir "$CSS_DIR"
create_dir "$JS_DIR"
create_dir "$DOCS_DIR"
create_dir "$LOGS_DIR"
create_dir "$TESTS_DIR"

# Création des fichiers
for file in "${FILES[@]}"; do
    create_file "$file"
done

echo -e "\n${GREEN}Structure du projet créée avec succès !${NC}"

# Affichage de l'arborescence si tree est installé
if command -v tree &> /dev/null; then
    echo -e "\n${BLUE}Arborescence du projet :${NC}"
    tree -a
else
    echo -e "\n${YELLOW}Pour voir l'arborescence, installez tree :${NC} sudo apt-get install tree"
fi

# Résumé des opérations
echo -e "\n${BLUE}Résumé des opérations :${NC}"
echo "Utilisez les commandes suivantes pour commencer :"
echo -e "${GREEN}cd $(pwd)${NC}"
echo -e "${GREEN}python -m venv venv${NC}"
echo -e "${GREEN}source venv/bin/activate${NC}"
echo -e "${GREEN}pip install -r requirements.txt${NC}"