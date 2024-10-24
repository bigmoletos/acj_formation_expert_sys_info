
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// vérification d'existence d'un fichier
// deux fichiers ont-ils des contenus identiques
// programme de copie d'un fichier et vérification
// séparer infos.txt en identity.txt, contact_infos.txt, service.txt
// fusion des informations, vérification du résultat par comparaison à infos.txt

using namespace std;

int main(int argc, char** argv) {
    // Variables pour lire les caractères
    char i, j;

    // Vérification des arguments d'entrée
    if (argc != 3) {
        if (argc < 3) {
            cout << "Il manque le nom d'un fichier." << endl;
        } else {
            cout << "Il y a trop d'arguments." << endl;
        }
        exit(1);
    }

    // Variables pour stocker les noms des fichiers
    string namefichier = argv[1];
    string namefichier2 = argv[2];
    string namefichier3 = argv[3];
    string namefichier4 = argv[1];

    // Vérification d'existence et ouverture des fichiers
    ifstream f1(namefichier);
    ifstream f2(namefichier2);
    ifstream f3(namefichier3);
    ifstream f4(namefichier4);


    if (!f1.is_open()) {
        cout << "Erreur : Impossible d'ouvrir le fichier " << namefichier << endl;
        exit(2);
    }

    if (!f2.is_open()) {
        cout << "Erreur : Impossible d'ouvrir le fichier " << namefichier2 << endl;
        exit(2);
    }

    if (!f3.is_open()) {
        cout << "Erreur : Impossible d'ouvrir le fichier " << namefichier2 << endl;
        exit(2);
    }

    if (!f4.is_open()) {
        cout << "Erreur : Impossible d'ouvrir le fichier " << namefichier2 << endl;
        exit(2);
    }

    // Vérifier si les deux fichiers sont les mêmes (au niveau du chemin)
    if (namefichier == namefichier2) {
        cout << "Les fichiers sont identiques (même chemin) !" << endl;
        f1.close();
        f2.close();
        exit(4);
    }

    // Comparaison des contenus des fichiers
    bool sontIdentiques = true;
    while ((f1.get(i)) && (f2.get(j))) {
        if (i != j) {
            cout << "Les fichiers " << namefichier << " et " << namefichier2 << " sont différents." << endl;
            sontIdentiques = false;
            break;
        }
    }

    // Vérification que les deux fichiers ont la même taille
    if (sontIdentiques && (f1.get() != EOF || f2.get() != EOF)) {
        cout << "Les fichiers " << namefichier << " et " << namefichier2 << " ont des tailles différentes." << endl;
        sontIdentiques = false;
    }

    // Résultat final
    if (sontIdentiques) {
        cout << "Les fichiers " << namefichier << " et " << namefichier2 << " sont identiques." << endl;
    }


    //copie du fichier1 dans fichier3.txt et vérification

    // Ouverture du fichier destination en mode ajout (append)
    fstream file2(namefichier2, fstream::out | fstream::app);
    if (!file2.is_open()) {
        cout << "Erreur : Impossible d'ouvrir " << namefichier2 << " pour l'écriture." << endl;
        namefichier2.close();  // Fermer file1 si file2 échoue à s'ouvrir
        return 1;
    }



    // Fermeture des fichiers
    f1.close();
    f2.close();
    f3.close();
    f4.close();

    return 0;
}
