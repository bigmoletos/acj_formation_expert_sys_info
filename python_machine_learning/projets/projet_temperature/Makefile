##
# @file Makefile
# @brief Makefile pour le projet Temperature
# @details Gère les tâches de build, test, documentation et déploiement
##

# Variables
PYTHON := python3
FLASK := flask
PYTEST := pytest
COVERAGE := coverage
PIP := pip

# Couleurs pour les messages
GREEN := \033[0;32m
RED := \033[0;31m
YELLOW := \033[1;33m
BLUE := \033[0;34m
NC := \033[0m

.PHONY: all help install test run clean docs venv

# Cible par défaut
all: help

help:
	@echo "$(BLUE)Usage:$(NC)"
	@echo "  make $(GREEN)<target>$(NC)"
	@echo
	@echo "$(BLUE)Targets:$(NC)"
	@echo "  $(GREEN)install$(NC)    Installe les dépendances"
	@echo "  $(GREEN)test$(NC)       Lance les tests"
	@echo "  $(GREEN)run$(NC)        Lance l'application"
	@echo "  $(GREEN)clean$(NC)      Nettoie les fichiers générés"
	@echo "  $(GREEN)docs$(NC)       Génère la documentation"

install:
	@echo "$(BLUE)Installation des dépendances...$(NC)"
	$(PIP) install -r requirements.txt
	@echo "$(GREEN)Installation terminée$(NC)"

test:
	@echo "$(BLUE)Lancement des tests...$(NC)"
	$(PYTEST) tests/ -v --cov=app --cov-report=html
	@echo "$(GREEN)Tests terminés$(NC)"

run:
	@echo "$(BLUE)Lancement de l'application...$(NC)"
	$(PYTHON) -m flask run --host=localhost

clean:
	@echo "$(BLUE)Nettoyage...$(NC)"
	rm -rf __pycache__/
	rm -rf .pytest_cache/
	rm -rf htmlcov/
	rm -rf .coverage
	rm -rf docs/build/
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type f -name "*.pyc" -delete
	@echo "$(GREEN)Nettoyage terminé$(NC)"

docs:
	@echo "$(BLUE)Génération de la documentation...$(NC)"
	doxygen Doxyfile
	@echo "$(GREEN)Documentation générée dans app/templates/docs/html/$(NC)"

venv:
	@echo "$(BLUE)Création de l'environnement virtuel...$(NC)"
	python -m venv venv
	@echo "$(GREEN)Environnement virtuel créé$(NC)"
	@echo "$(YELLOW)Activez l'environnement avec:$(NC)"
	@echo "source venv/bin/activate (Linux/Mac)"
	@echo "venv\\Scripts\\activate (Windows)"