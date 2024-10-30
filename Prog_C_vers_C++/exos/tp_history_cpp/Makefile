# Variables
CC = g++
CFLAGS = -Wall -Wextra -Wunused-const-variable -Wunused-parameter -Werror
TARGET = prog.exe
SRC = $(wildcard *.cpp)  # Trouver tous les fichiers .cpp dans le répertoire
OBJ = $(SRC:.cpp=.o)     # Convertir les noms de fichiers .cpp en .o

# Règle principale pour compiler tous les fichiers en un exécutable
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Règle générique pour compiler les fichiers .cpp en .o
%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage de tous les fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(TARGET)
	@echo "Nettoyage des fichiers objets et de $(TARGET) terminé."

# Nettoyer un fichier spécifique
clean-%:
	@if [ "$*" ]; then \
		rm -f $*; \
		echo "$* supprimé."; \
	else \
		echo "Spécifiez un fichier à supprimer, par exemple : make clean-fichier.o"; \
	fi
