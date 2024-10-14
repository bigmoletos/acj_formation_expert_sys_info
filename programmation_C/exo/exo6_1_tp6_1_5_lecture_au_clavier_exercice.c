#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* Enoncé

1-Faire en sorte de demander à l'utilisateur de rentrer son âge et sa taille au
clavier.
2- Demander en plus deux caractères pour symboliser ses initiales.
3- Afficher les informations dans un terminal.
Objectifs
Donnez votre age et taille en mettre: 23 1.72
Donnez vos initiales: AM
Vous avez 23 ans et vous mesurez 1.72 m
Vos initiales sont A.M



*/


/* SPOIL

1- Utiliser la fonction scanf. Attention, il faut donner les adresses des variables
“&ma_variable”
2- Attention, le ‘\n’ est considéré comme un caractère par la fonction scanf. Avant de lire les
initiales, il faut utiliser la fonction fflush(stdin) pour vider le buffer de lecture. Sinon vous
allez lire le \n du point 1.
Aide
Type Taille (octets) Valeur min Valeur max Affichage
int 2 / 4
-32768 /
-214748364
8
32767 /
2147483647 %d
char 1 -128 127 %c
float 4 -3.4e38 3.4e38 %f
double 8 -1.7e308 1.7e308 %f

*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées


int main()
{
    // Affiche le titre du programme
    printf("\n\n================================\n");
    printf("TP 6-1 Saisi des variables au clavier\n");
    printf("Saises au clavier\n");
    printf("================================\n\n");

    // declaration et intialisation de nos variables
    int age=0 ;
    float taille=0.0 ;

    char initiale[3] = "X"; // 3 caractéres le dernier étant le \0 de fin de chaine

// saisie claiver des variables
    printf("Donnez votre age: ");
    // scanf("%d",&age);
// Controles de saisie
        //  controle de la saisie de l'age
    if (scanf("%d", &age) != 1 || age <= 0 || age>125) {
        printf("Erreur: veuillez entrer un âge valide (nombre entier positif).\n");
        // vide le buffer
        fflush(stdin);  // Vider le tampon d'entrée en cas d'erreur
        exit(1) ;
    }

// saisie claiver de la taille
    printf("Donnez taille en mettre: ");
    // scanf("%f",&taille);
// Controles de saisie
        //  controle de la saisie de la taille
    if (scanf("%f", &taille) != 1 || taille < 1.3 || taille>2.3) {
        printf("Erreur: veuillez entrer une taille en m valide (nombre entier positif entre 1.3 et 2.3 ).\n");
        // vide le buffer
        fflush(stdin);  // Vider le tampon d'entrée en cas d'erreur
        exit(1) ;
    }

    // vide le buffer
    fflush(stdin);
// saise des initiales

    printf("Donnez vos initiales (2 lettres max):\n");
    // on peut choisir de ne prednre que les 2 premiers caractéres avec un %2s
    // scanf(" %2s",&initiale);
    scanf(" %s",&initiale);
//  controle le nombre de caractères saisies pour les initiales, 2 max autorisées
    if (strlen(initiale)>2)
    {
        printf("veuillez ne saisir que 2 lettres!!\n");
    } else {
            // Conversion des initiales en majuscules
        for (int i = 0; i < strlen(initiale); i++) {
            initiale[i] = toupper(initiale[i]);
        }
        printf("Vous avez %d ans et vous mesurez %0.2f m \nVos initiales sont %s\n", age, taille, initiale);

}

    // scanf("%d%d %c",age,taille, initiale);

    return 0;
}
