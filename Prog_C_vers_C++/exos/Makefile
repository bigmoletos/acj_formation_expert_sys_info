# Variables
CC = g++
CFLAGS = -Wall -Wextra -Wunused-const-variable -Wunused-parameter -Werror

# Règle générique pour compiler n'importe quel fichier .cpp
%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

# Nettoyer un fichier spécifique
clean:
	@if [ "$(TARGET)" ]; then \
		rm -f $(TARGET); \
		echo "$(TARGET) supprimé."; \
	else \
		echo "Spécifiez un fichier à supprimer, par exemple : make clean-exo5"; \
		echo "Ne pas oublier le - entre clean et le nom du fichier"; \
	fi

# Pour spécifier la cible du nettoyage via un argument
clean-%:
	$(MAKE) clean TARGET=$*
