#ifndef HEADER_H  // Si la macro HEADER_H n'est pas encore définie
#define HEADER_H  // Définition de la macro

// HEADER types des fonctions
int saisir_entier(int max_valeur);
char demander_quitter();
void affichage(int *valeur);  // Affichage d'une seule valeur
void affichage2valeur(int *valeur1, int *valeur2);  // Affichage de deux valeurs

#endif  // Fin de la protection contre l'inclusion multiple