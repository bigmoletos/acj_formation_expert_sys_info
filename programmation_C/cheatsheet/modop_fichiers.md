# Cheat Sheet: Gestion des Fichiers en C

## Ouverture et Fermeture de Fichier

### `fopen` : Ouvrir un fichier
```c
FILE *fopen(const char *nomFichier, const char *mode);
nomFichier : Nom du fichier à ouvrir.
mode : Mode d'ouverture du fichier :
"r" : Lecture
"w" : Écriture (crée un fichier s'il n'existe pas)
"a" : Ajout (crée un fichier s'il n'existe pas)
"r+" : Lecture/Écriture
"w+" : Écriture/Lecture
"a+" : Ajout/Lecture
Exemple :

c
Copier le code
FILE *fp = fopen("mon_fichier.txt", "r");
fclose : Fermer un fichier
c
Copier le code
int fclose(FILE *fp);
Ferme le fichier ouvert.
Renvoie 0 en cas de succès.
Exemple :

c
Copier le code
fclose(fp);
Lecture de Fichiers
fscanf : Lire du contenu formaté
c
Copier le code
int fscanf(FILE *fp, const char *format, ...);
Lit des données formatées à partir d'un fichier.
Exemple :

c
Copier le code
int age;
fscanf(fp, "%d", &age);
fgets : Lire une ligne
c
Copier le code
char *fgets(char *str, int n, FILE *fp);
Lit une chaîne de caractères de longueur maximale n à partir du fichier fp.
Exemple :

c
Copier le code
char ligne[100];
fgets(ligne, 100, fp);
Écriture dans des Fichiers
fprintf : Écrire du contenu formaté
c
Copier le code
int fprintf(FILE *fp, const char *format, ...);
Écrit des données formatées dans un fichier.
Exemple :

c
Copier le code
fprintf(fp, "Nom: %s, Âge: %d\n", nom, age);
fputs : Écrire une chaîne de caractères
c
Copier le code
int fputs(const char *str, FILE *fp);
Écrit une chaîne de caractères dans un fichier.
Exemple :

c
Copier le code
fputs("Bonjour, monde !", fp);
Autres Fonctions Utiles
fseek : Déplacer le pointeur de fichier
c
Copier le code
int fseek(FILE *fp, long offset, int origine);
offset : Déplacement en octets.
origine :
SEEK_SET : Depuis le début.
SEEK_CUR : Depuis la position actuelle.
SEEK_END : Depuis la fin.
Exemple :

c
Copier le code
fseek(fp, 0, SEEK_SET);  // Retourner au début du fichier
ftell : Obtenir la position actuelle du pointeur de fichier
c
Copier le code
long ftell(FILE *fp);
Renvoie la position actuelle dans le fichier.
Exemple :

c
Copier le code
long pos = ftell(fp);
rewind : Remettre le pointeur au début du fichier
c
Copier le code
void rewind(FILE *fp);
Exemple :

c
Copier le code
rewind(fp);
feof : Vérifier la fin d'un fichier
c
Copier le code
int feof(FILE *fp);
Renvoie une valeur non nulle si la fin du fichier est atteinte.
Exemple :

c
Copier le code
if (feof(fp)) {
    printf("Fin du fichier atteinte.\n");
}
ferror : Vérifier les erreurs
c
Copier le code
int ferror(FILE *fp);
Renvoie une valeur non nulle si une erreur s'est produite.
Exemple :

c
Copier le code
if (ferror(fp)) {
    printf("Erreur lors de la lecture du fichier.\n");
}
Exemples Complet d'Utilisation
Lecture d'un fichier ligne par ligne
c
Copier le code
FILE *fp = fopen("mon_fichier.txt", "r");
if (fp == NULL) {
    perror("Erreur d'ouverture de fichier");
    return 1;
}

char ligne[100];
while (fgets(ligne, sizeof(ligne), fp)) {
    printf("%s", ligne);
}

fclose(fp);
Écriture dans un fichier
c
Copier le code
FILE *fp = fopen("sortie.txt", "w");
if (fp == NULL) {
    perror("Erreur d'ouverture de fichier");
    return 1;
}

fprintf(fp, "Ceci est un exemple de texte.\n");

fclose(fp);