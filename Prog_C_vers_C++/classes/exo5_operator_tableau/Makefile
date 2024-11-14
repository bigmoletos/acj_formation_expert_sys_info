# Makefile pour le projet
#
# Ce Makefile permet de compiler un projet C++ en utilisant g++.
# Il gère la compilation des fichiers source, la création des
# dossiers nécessaires, et fournit des règles pour nettoyer
# les fichiers générés et afficher de l'aide.
#
# Usage principal :
# - make all         : Compile le projet et génère l'exécutable
# - make all dg      : Compile le projet en mode debug avec le flag -g
# - make clean       : Supprime les fichiers objets et l'exécutable
# - make help        : Affiche cette aide
# - make move_files  : Déplace les fichiers sources, en-têtes et objets dans leurs dossiers respectifs
#
# Variables utilisées :
# - PROGRAM_NAME : Nom de l'exécutable généré
# - CXX          : Définit le compilateur C++
# - CXXFLAGS     : Définit les options de compilation par défaut
# - DEBUGFLAGS   : Définit l'option de compilation en mode debug (-g)
#
# Structure des dossiers :
# - src       : Contient les fichiers source (.cpp)
# - include   : Contient les fichiers d'en-tête (.hpp)
# - build     : Contient les fichiers objets générés (.o)
# - bin       : Contient l'exécutable final
# - data      : Contient les fichiers de données
# - script_perso : Contient les scripts auxiliaires personnalisés


# Nom du programme
PROGRAM_NAME = prog

# Compilateur et options de compilation
CXX = g++
CXXFLAGS = -Wall -Iinclude
DEBUGFLAGS = -g

# Dossiers
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin
DATA_DIR = data
SCRIPT_DIR = script_perso

# Fichiers source et objets
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Nom de l'exécutable
TARGET = $(BIN_DIR)/$(PROGRAM_NAME).exe

# Règle par défaut : compile et lance le programme
# Commande : make all ou make all dg
# Si le flag "dg" est présent, la compilation inclura les options de debug
all: init move_files $(TARGET) run

# Activer le mode debug si le flag "dg" est passé en argument
ifeq ($(findstring dg, $(MAKECMDGOALS)), dg)
    CXXFLAGS += $(DEBUGFLAGS)
endif

# Règle pour exécuter le programme
# Commande : make run
run: $(TARGET)
	./$(TARGET)

# Compilation de l'exécutable
# $(TARGET) dépend de tous les fichiers objets générés dans $(OBJS)
# Commande : make $(TARGET)
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des fichiers objets à partir des sources
# Commande : make $(BUILD_DIR)/%.o
# Compile chaque fichier source .cpp en fichier objet .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Initialisation : création des dossiers nécessaires si absents
# Commande : make init
init:
	mkdir -p $(SRC_DIR) $(INCLUDE_DIR) $(BUILD_DIR) $(BIN_DIR) $(DATA_DIR)

# Ajout d'une dépendance pour s'assurer que le dossier bin existe
# Commande : make $(BIN_DIR)
$(BIN_DIR):
	sudo mkdir -p $(BIN_DIR)

# Nettoyage des fichiers générés
# Commande : make clean
# Supprime les fichiers objets dans $(BUILD_DIR) et l'exécutable dans $(BIN_DIR)
clean:
	sudo rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Affichage de l'aide pour l'utilisation du Makefile
# Commande : make help
help:
	@echo "Utilisation du Makefile :"
	@echo "  make all         : Compile le projet et génère l'exécutable dans $(BIN_DIR)"
	@echo "  make all dg      : Compile le projet en mode debug avec le flag -g"
	@echo "  make clean       : Supprime les fichiers objets et l'exécutable"
	@echo "  make help        : Affiche cette aide"
	@echo ""
	@echo "Dossiers du projet :"
	@echo "  $(SRC_DIR)       : Contient les fichiers source (.cpp)"
	@echo "  $(INCLUDE_DIR)   : Contient les fichiers d'en-tête (.hpp)"
	@echo "  $(BUILD_DIR)     : Contient les fichiers objets générés (.o)"
	@echo "  $(BIN_DIR)       : Contient l'exécutable final"
	@echo "  $(DATA_DIR)      : Contient les fichiers de données"
	@echo "  $(SCRIPT_DIR)    : Contient les scripts auxiliaires"

# Déplacement des fichiers dans les dossiers appropriés
# Commande : make move_files
# Déplace les fichiers .cpp, .hpp, .o, l'exécutable et les fichiers .data dans leurs dossiers respectifs
move_files: init
	mv *.cpp $(SRC_DIR)/ || true
	mv *.hpp $(INCLUDE_DIR)/ || true
	mv *.o $(BUILD_DIR)/ || true
	mv $(TARGET) $(BIN_DIR)/ || true
	mv *.data $(DATA_DIR)/ || true
