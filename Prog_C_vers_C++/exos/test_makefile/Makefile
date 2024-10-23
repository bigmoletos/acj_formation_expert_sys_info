# Variables
CC = g++
CFLAGS = -Wall -Wextra -Wunused-const-variable -Wunused-parameter -Werror

# Règle générique pour compiler n'importe quel fichier .cpp
%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

# Nettoyer les fichiers objets et exécutables
clean:
	rm -f *.o $(wildcard exo*) $(wildcard test*) $(wildcard mon_programme*)
