# Makefile pour le projet

# Compilateur et options de compilation
CXX = g++
CXXFLAGS = -Wall -Iinclude

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
TARGET = $(BIN_DIR)/mon_programme.exe

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Création des dossiers
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Nettoyage des fichiers générés
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Affichage de l'aide
help:
	@echo "Utilisation du Makefile :"
	@echo "  make all       : Compile le projet et génère l'exécutable dans $(BIN_DIR)"
	@echo "  make clean     : Supprime les fichiers objets et l'exécutable"
	@echo "  make help      : Affiche cette aide"
	@echo ""
	@echo "Dossiers du projet :"
	@echo "  $(SRC_DIR)     : Contient les fichiers source (.cpp)"
	@echo "  $(INCLUDE_DIR) : Contient les fichiers d'en-tête (.hpp)"
	@echo "  $(BUILD_DIR)   : Contient les fichiers objets générés (.o)"
	@echo "  $(BIN_DIR)     : Contient l'exécutable final"
	@echo "  $(DATA_DIR)    : Contient les fichiers de données"
	@echo "  $(SCRIPT_DIR)  : Contient les scripts auxiliaires"
