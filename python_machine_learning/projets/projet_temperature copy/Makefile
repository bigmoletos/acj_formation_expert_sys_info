##
# @file Makefile
# @brief Makefile pour le projet Temperature
# @details Gère les tâches de build, test, documentation et déploiement
##

# Variables de configuration
PYTHON := python3
PIP := $(PYTHON) -m pip
FLASK := $(PYTHON) -m flask
PYTEST := $(PYTHON) -m pytest
DOXYGEN := doxygen
VENV_DIR := venv
VENV_BIN := $(VENV_DIR)/bin
VENV_PYTHON := $(VENV_BIN)/python3
VENV_PIP := $(VENV_PYTHON) -m pip

# Couleurs pour les messages
GREEN := \033[0;32m
RED := \033[0;31m
YELLOW := \033[1;33m
BLUE := \033[0;34m
NC := \033[0m

# Vérification de l'existence des commandes requises
PYTHON_OK := $(shell command -v $(PYTHON) 2> /dev/null)
DOXYGEN_OK := $(shell command -v $(DOXYGEN) 2> /dev/null)

# Définition des cibles qui ne sont pas des fichiers
.PHONY: all help install test run clean docs venv check-venv check-deps check-doxygen

# Cible par défaut
all: help

# Aide
help:
	@echo -e "$(BLUE)Usage:$(NC)"
	@echo -e "  make $(GREEN)<target>$(NC)"
	@echo
	@echo -e "$(BLUE)Targets:$(NC)"
	@echo -e "  $(GREEN)help$(NC)        Affiche ce message d'aide"
	@echo -e "  $(GREEN)install$(NC)     Installe les dépendances dans un environnement virtuel"
	@echo -e "  $(GREEN)test$(NC)        Lance les tests unitaires"
	@echo -e "  $(GREEN)run$(NC)         Lance l'application Flask"
	@echo -e "  $(GREEN)docs$(NC)        Génère la documentation avec Doxygen"
	@echo -e "  $(GREEN)clean$(NC)       Nettoie les fichiers générés"
	@echo -e "  $(GREEN)venv$(NC)        Crée un environnement virtuel"
	@echo
	@echo -e "$(BLUE)Options:$(NC)"
	@echo -e "  PYTHON=$(GREEN)$(PYTHON)$(NC)"
	@echo -e "  VENV_DIR=$(GREEN)$(VENV_DIR)$(NC)"

# Vérifie l'existence de l'environnement virtuel
check-venv:
	@if [ ! -d "$(VENV_DIR)" ]; then \
		echo -e "$(RED)Environnement virtuel non trouvé.$(NC)"; \
		echo -e "$(YELLOW)Création de l'environnement virtuel...$(NC)"; \
		make venv; \
	fi

# Vérifie les dépendances système
check-deps:
ifndef PYTHON_OK
	$(error $(RED)Python3 n'est pas installé$(NC))
endif

# Vérifie l'installation de Doxygen
check-doxygen:
ifndef DOXYGEN_OK
	$(error $(RED)Doxygen n'est pas installé. Installez-le avec: sudo apt-get install doxygen$(NC))
endif

# Crée l'environnement virtuel
venv: check-deps
	@echo -e "$(BLUE)Création de l'environnement virtuel...$(NC)"
	@test -d $(VENV_DIR) || $(PYTHON) -m venv $(VENV_DIR)
	@echo -e "$(GREEN)Environnement virtuel créé dans $(VENV_DIR)$(NC)"

# Installation des dépendances
install: check-venv
	@echo -e "$(BLUE)Installation des dépendances...$(NC)"
	$(VENV_PIP) install --upgrade pip
	$(VENV_PIP) install -r requirements.txt
	@echo -e "$(GREEN)Dépendances installées avec succès$(NC)"

# Lance les tests
test: check-venv
	@echo -e "$(BLUE)Lancement des tests...$(NC)"
	@. $(VENV_BIN)/activate && $(PYTEST) tests/ -v
	@echo -e "$(GREEN)Tests terminés$(NC)"

# Lance l'application
run: check-venv
	@echo -e "$(BLUE)Lancement de l'application...$(NC)"
	@. $(VENV_BIN)/activate && $(FLASK) run

# Génère la documentation
docs: check-doxygen
	@echo -e "$(BLUE)Génération de la documentation...$(NC)"
	@if [ ! -f Doxyfile ]; then \
		echo -e "$(RED)Fichier Doxyfile non trouvé$(NC)"; \
		exit 1; \
	fi
	@$(DOXYGEN) Doxyfile
	@echo -e "$(GREEN)Documentation générée dans docs/$(NC)"

# Nettoie les fichiers générés
clean:
	@echo -e "$(BLUE)Nettoyage des fichiers générés...$(NC)"
	rm -rf docs/
	rm -rf __pycache__/
	rm -rf .pytest_cache/
	rm -rf .coverage
	rm -rf htmlcov/
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type f -name "*.pyc" -delete
	find . -type f -name "*.pyo" -delete
	find . -type f -name "*.pyd" -delete
	find . -type f -name ".coverage" -delete
	find . -type d -name "*.egg-info" -exec rm -rf {} +
	find . -type f -name "*.egg" -delete
	@echo -e "$(GREEN)Nettoyage terminé$(NC)"

# Vérifie l'état du projet
status: check-venv
	@echo -e "$(BLUE)État du projet :$(NC)"
	@echo -e "Python: $(GREEN)$(shell $(PYTHON) --version)$(NC)"
	@echo -e "Pip: $(GREEN)$(shell $(VENV_PIP) --version)$(NC)"
	@echo -e "Flask: $(GREEN)$(shell $(VENV_PIP) show flask | grep Version)$(NC)"
	@if [ -d ".git" ]; then \
		echo -e "Git: $(GREEN)$(shell git --version)$(NC)"; \
		echo -e "Branch: $(GREEN)$(shell git branch --show-current)$(NC)"; \
	fi