#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_SENTENCE 100


/*
Exercice 3 : Comparer deux chaînes de caractères

Énoncé : Écris un programme qui demande à l'utilisateur d'entrer deux chaînes de caractères et vérifie si elles sont égales, sans utiliser la fonction strcmp().
 */



int main(){

    char sentence[TAILLE_SENTENCE] ;
    char sentence2[TAILLE_SENTENCE] ;
    size_t taille_chaine = 0;
    size_t taille_chaine2 = 0;
    // sentence[] = "les carottes sont cuites";


    printf("Entrez une premieres chainbe de caractères sans espace: \n");
    scanf(" %[^\n]", sentence);

    printf("Entrez une premieres chainbe de caractères sans espace: \n");
    scanf(" %[^\n]", sentence2);

    while (sentence[taille_chaine] != '\0' && sentence[taille_chaine] != '\n') {
        taille_chaine++;
    }
    while (sentence2[taille_chaine2] != '\0' && sentence2[taille_chaine2] != '\n') {
        taille_chaine2++;
    }
    printf("taille de la premiere phrase : %zu\n", taille_chaine);
    printf("taille de la deuxieme phrase : %zu\n", taille_chaine2);

    //comparaison des 2 chaines
    if (taille_chaine > taille_chaine2)
    {
        printf("la premiere phrase est plus grande que la deuxieme : %zu\n", taille_chaine);
    }else if (taille_chaine < taille_chaine2)
    {
        printf("la deuxieme phrase est plus grande que la premiere : %zu\n", taille_chaine2);
    }else if (taille_chaine == taille_chaine2){

        printf("les 2 phrases sont identiques :\n");

    }




// // autre solution avec sizeof
//     size_t taille_chaine2=sizeof(sentence)/sizeof(sentence[0]);
// printf("taille de la chaine de caractères: %zu\n", taille_chaine2);
    return 0;
 }
