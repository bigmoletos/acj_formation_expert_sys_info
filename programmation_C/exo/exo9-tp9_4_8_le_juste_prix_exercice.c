#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>


/* Enoncé

Nous allons créer un petit jeu de type “Le juste prix”. Pour les plus jeunes, cela correspond à un ancien jeu télévisé qui consiste à demander, aux participants, de trouver le prix d'un objet. Ils font alors des propositions et le présentateur leur dit simplement "c'est plus" ou "c'est moins", jusqu'à ce que l’un d’entre eux trouve le bon prix.
Mais biensur, il y a une limite de temps!
Nous allons donc demander à l’utilisateur de trouver un nombre entier compris entre 1 et 100. Il vas alors pouvoir faire des propositions et pour chacune d’entre elles, nous allons afficher “c’est plus !” ou “c’est moins !”. lorsque l’utilisateur a trouvé le bon nombre alors on affiche un message de félicitation et on termine le programme.
Le joueur a le droit à 10 tentatives.
...
> 23
c’est plus !
> 30
c’est moin !
> 25
Bravo! le nombre mystère est bien 25

I - Objectifs

Créer la boucle de jeu
   1.1 Demander à l'utilisateur de rentrer un entier pour trouver le nombre mystère.
   1.2 Comparer la valeur saisie avec le nombre a trouver.
   1.3 Gérer la fin de partie (le joueur a trouvé le bon nombre).
2- Ajouter un compteur qui indique combien de tentative a fait le joueur.

...
tentative 3 > 23
c’est plus !
tentative 4 > 30
c’est moin !
tentative 5 > 25
Bravo! le nombre mystère est bien 25
III - Instructions
A- Modifier le code pour rendre le jeu plus difficile. pour cela, ajouter un nombre maximum de tentative.
B- Ajouter un menu à l’utilisateur en fin de partie lui permettant de faire une nouvelle partie ou quitter.
...
tentative 3/10 > 23
c’est plus !
tentative 4/10 > 30
c’est moins !
tentative 5/10 > 25
Bravo! le nombre mystère est bien 25
Voulez-vous faire une nouvelle partie (1-oui, 2-non)
> 2



*/


/* SPOIL

Faire une boucle avec pour condition le fait que la saisie utilisateur corresponde ou non au nombre à trouver.
2- Il faut créer une nouvelle variable initialisé a 0 et l'incrémenter à chaque tentative de l'utilisateur.
A- Créer une nouvelle constante qui comporte le nombre maximum de tentative. quand ce nombre est atteint, utiliser une des instruction suivante pour terminer la partie (break, continue).
B- Mettre la boucle de jeu dans une nouvelle boucle. la condition de cette nouvelle boucle doit vérifier le choix de l’utilisateur.

*/

// Déclaration et intialisation des variables globales avec des valeurs appropriées



int main()
{
    // Affiche le titre du programme
    printf("\n\n====================================\n");
    printf("tp9-4-9\n");
    printf("Le juste prix\n");
    printf("========================================\n\n");

    // Déclaration et initialisation de nos variables
    int nombre_mystere = 0, nombre_utilisateur = 0, max_tentatives = 10, nbre_tentatives = 0, nouvelle_partie=0;
    char quit = 'n';  // Pour quitter ou non le jeu
    const int VALEUR_MIN = 1, VALEUR_MAX = 100;

    // Génération d'un nombre aléatoire entre 1 et 100
    srand(time(NULL));
    nombre_mystere = (rand() % (VALEUR_MAX - VALEUR_MIN + 1)) + VALEUR_MIN;

    printf("Devinez quel est mon nombre mystère.\nIndice: c'est un nombre entre %d et %d\n", VALEUR_MIN, VALEUR_MAX);

    while (nbre_tentatives < max_tentatives && quit == 'n')
    {


        // Saisie clavier des variables
        printf("Quel est votre choix de nombre : ");

        // Contrôle de saisie
        if (scanf("%d", &nombre_utilisateur) != 1 || nombre_utilisateur < VALEUR_MIN || nombre_utilisateur > VALEUR_MAX)
        {
            printf("Veuillez saisir un nombre entre %d et %d.\n", VALEUR_MIN, VALEUR_MAX);
            // Vider le buffer en cas de mauvaise saisie
            while (getchar() != '\n');
            continue;
        }

        if (nombre_utilisateur > nombre_mystere)
        {
            printf("\n-------------------------------------\n");
            printf("C’est moins !\n");
            printf("-------------------------------------\n");
        }
        else if (nombre_utilisateur < nombre_mystere)
        {
            printf("\n-------------------------------------\n");
            printf("C’est plus !\n");
            printf("-------------------------------------\n");
        }
        else
        {
            printf("\n-------------------------------------\n");
            printf("Bravo ! Le juste prix est en effet %d !\n", nombre_mystere);
            printf("-------------------------------------\n");

            // Option pour quitter ou recommencer le jeu
            printf("Souhaitez-vous quitter le jeu (O/N) : ");

            // Contrôle de saisie pour O/N
            if (scanf(" %c", &quit) != 1) {
                printf("Erreur de saisie. Veuillez réessayer. Vous ne pouvez saisir que O ou N.\n");
                while (getchar() != '\n');  // Vider le buffer en cas de mauvaise saisie
                continue;
            }

            // Conversion de la saisie en minuscule
            quit = tolower(quit);

            if (quit == 'o') {
                printf("Vous avez choisi de quitter le jeu.\n");
                break;
            } else if (quit == 'n') {
                printf("Vous continuez le jeu.\n");
                // Réinitialiser les tentatives
                nbre_tentatives = 0;
                // nouveau nombre mystère
                nombre_mystere = (rand() % (VALEUR_MAX - VALEUR_MIN + 1)) + VALEUR_MIN;
                // compteur nouvelle partie
                nouvelle_partie = 1;
                printf("Un nouveau nombre mystère a été généré !\n");
            } else {
                printf("Entrée non valide. Veuillez saisir 'O' pour Oui ou 'N' pour Non.\n");
                continue;
            }
        }
        // test si on rejoue il ne faut pas incrementer le nombres de tentatives
        if (nouvelle_partie==0)
        {
            nbre_tentatives++;
            //reinitialisation
            nouvelle_partie = 0;
          }

        printf("Vous avez joué %d fois, il vous reste encore %d tentatives.\n", nbre_tentatives, max_tentatives - nbre_tentatives);


        if (nbre_tentatives == max_tentatives)
        {
            printf("Vous ne pouvez plus jouer car vous avez fait trop de tentatives !\nAu revoir !\n");
            break;
        }

        printf("\n========================================\n\n");
    }

    return 0;
}
