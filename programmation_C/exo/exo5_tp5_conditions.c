#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* Enoncé

1- Lire la saisie de l'utilisateur:
   - 1er Nombre: Entier
   - Opérateur: char (+, -, *, /, %)
   - 2eme Nombre: Entier
2- En fonction de l'opérateur choisi, effectuer la bonne opération.
3- Afficher le résultat sous la forme suivante: nombre1 opérateur nombre2 =
resultat (ex: 2 + 3 = 5)
III - Instructions


Indiquez l'operation mathematique que je dois resoudre (sans espace)
   -sous la forme [nombre1 opérateur nombre2] par exemple (2+3)
   -operateurs possibles [+, -, *, /]
>2+3
Trop simple! le résultat est: 2 + 3 = 5
- Ajouter la gestion des cas d'erreur de saisie de l'opérateur. Si, l'opérateur saisie, par
l'utilisateur n'est pas compris dans la liste (+, -, *, /).

B- Gérer le cas de la division par 0 !

Opérateur invalide, vous devez utilisez l'un des opérateur (+, -, *, /)

Attention la division par 0 est impossible!


*/


/* SPOIL

1- Utiliser la fonction scanf avec %d%c%d
 2- Il y a une liste précise d’opérateur et donc de cas, le switch est tout indiqué.
 3- Stocker le résultat de l'opération dans une variable pour l’afficher plus loin.
 A- Utiliser le cas “default” du switch
 B- Utilisation du if else

*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées
int nbre1=0 ;
int nbre2=0 ;
int resultat=0 ;
char operateur_type;

int main()
{
    // Affiche le titre du programme
    printf("TP5: Les Conditions\n\n");

    // saisies
    printf("Quelle est votre premier nombre ?\n");
    scanf("%d", &nbre1);
    printf("Quelle est votre opération, opérateurs possibles: (+, -, *, /, %%) ?\n");
    scanf(" %c",  &operateur_type);  // il  faut mettre un espace avant le %c car sinon il considére le \n precedent comme un caractére
    printf("Quelle est votre deuxoime nombre ?\n");
    scanf("%d", &nbre2);
    // scanf("%d%c%d", &nbre1, &operateur_type, &nbre2);



    // calculs
    if (operateur_type == '+'){

        resultat = nbre1 + nbre2;

    }else if (operateur_type == '-'){

        resultat = nbre1 - nbre2;

    }else if (operateur_type== '*')
    {
        resultat = nbre1 * nbre2;

    }else if(operateur_type=='/'){
        if (nbre2 == 0) {
            printf("Attention la division par 0 est impossible!\n");
        } else {
        resultat = nbre1 / nbre2;
        }
    }else if(operateur_type=='%')
    {
        if (nbre2 == 0) {
            printf("Attention le modulo  par 0 est impossible!\n");
        } else {
        resultat = nbre1 % nbre2;
    }
    printf("Trop simple! Le resultat de votre calcul %d %c %d = %0.3f ?\t", nbre1, operateur_type, nbre2, resultat);
    }

    else
    {
        printf("Vous avez fait une erreur de saisie, vous ne pouvez entrer que (+, -, *, /, %%)\n");
    }






}
