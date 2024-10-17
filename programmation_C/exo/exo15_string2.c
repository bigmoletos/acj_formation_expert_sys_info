#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_SENTENCE 100


/*
 Exercice 1 : Calculer la longueur d'une chaîne de caractères

Énoncé : Écris un programme qui demande à l'utilisateur d'entrer une chaîne de caractères, puis calcule et affiche sa longueur sans utiliser la fonction strlen().
 */



int main(){

    char sentence[TAILLE_SENTENCE] ;
    size_t taille_chaine = 0;
    // sentence[] = "les carottes sont cuites";


    printf("Entrez une chainbe de caractères sans espace: \n");
    scanf(" %s", sentence);


    while (sentence[taille_chaine] != '\0' && sentence[taille_chaine] != '\n') {
        taille_chaine++;
    }
    printf("taille de la chainer de caractères, sans espace: %zu\n", taille_chaine);


// // autre solution avec sizeof
//     size_t taille_chaine2=sizeof(sentence)/sizeof(sentence[0]);
// printf("taille de la chaine de caractères: %zu\n", taille_chaine2);


 }
