#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

// Vérification d'existence d'un fichier
// Deux fichiers ont-ils des contenus identiques
// Programme de copie d'un fichier et vérification

using namespace std;

// int main(int argc, char* argv[]) {
/**
 * @brief [Description de main]
 *
 * @param argc [Description du param�tre]
 * @param argv [Description du param�tre]
 * @return int [Description du retour]
 */
int main(int argc, char** argv) {
    //vzariables pour lire les caractéres
    char i, j;
    // controle des arguments d'entrée de la fonction main

    if (argc < 3)
    {
        cout << "il manque le nom du fcihier" << endl;
        exit(1);
    }
    if (argc != 3){
        cout << "the command is not well formed" << endl;
        exit(2);
    }
    if (argc > 3){
        cout << "il y a trop d'argumlents" << endl;
        exit(3);
    }

    // Variables pour stocker les données correspond à la 2 éme valeur du tableau des argv
    string namefichier=argv[1];
    string namefichier2=argv[2];

    namefichier = "fichierTest.txt";
    namefichier2 = "fichierTest2.txt";

    // déclare une variale objet  de type flux de fichier en entrée sur lequel on a le droit de lire
    ifstream f1 (namefichier);
    ifstream f2 (namefichier2);

    // déclare une variale objet de type flux de fichier en entrée sur laquelle on a le droit d'ecrire attention si on les ouvre cela va supprimer tout ce qu'il y a dedans !!!!! Car cela crée le fichier
        // ofstream of1 (namefichier);
        // ofstream of2 (namefichier2);


    if(namefichier2 ==namefichier){
            cout << "  \nles fichiers sont identiques!\n";
            exit(6);

    }
    //varaible pour tester l'ouverture du fichier
    int f1_open=f1.is_open();
    int f2_open=f2.is_open();

    if (f1_open) {
        cout << namefichier << "  \nouverture du fichier 1 ok!\n";
        exit(4);
    }

    if (f2_open) {

        cout << namefichier2 << "  \nouverture du fichier 2 ok!\n";
        exit(5);

    }

    cout << argv[1]<<"le fichier existe\n";
    cout << argv[2]<<"le fichier existe\n";


    while ((f1 >> i) && (f2 >> j))
    {
        if (i !=j ){
        cout << namefichier << " et " << namefichier2 << "différent"<< endl;
        f1.close();
        f2.close();
        return 0 ;
        }
    }





f1.close();
f2.close();

return 0;
}

// #include <iostream>
// #include <fstream>
// #include <string>

// using namespace std ;

// int main (int argc, char** argv) {

//   if (argc < 3) {
//     cout << "no enough arguments" << endl ;
//     exit(1);
//   }

//   if (argc > 3) {
//     cout << "too much arguments" << endl ;
//     exit(2);
//   }

//   string name1 = argv[1] ;
//   string name2 = argv[2] ;

//   ifstream file1 (name1) ;
//   ifstream file2 (name2) ;

//   char x, y ;

//   if (!file1.is_open()) {
//     cout << name1 << " doesn't exist" << endl;
//     exit(3) ;
//   }

//   if (name1 == name2){
//     cout << "same file twice." << endl;
//     file1.close();
//     return 0;
//   }

//   if (!file2.is_open()) {
//     cout << name2 << " doesn't exist" << endl;
//     exit(3) ;
//   }

//   while ( (file1 >> x) and (file2 >> y) ) {
//     if (x != y) {
//       cout << name1 << " & " << name2
//            << " differs" << endl;
//       file1.close();
//       file2.close();
//       return 0 ;
//     }
//   }

//     cout << name1 << " & " << name2
//          << " identical" << endl;

//     file1.close();
//     file2.close();

//     return 0 ;
// }