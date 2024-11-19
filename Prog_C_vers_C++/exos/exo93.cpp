#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Vérification d'existence d'un fichier
// Deux fichiers ont-ils des contenus identiques
// Programme de copie d'un fichier et vérification

using namespace std;

/**
 * @brief [Description de main]
 *
 * @param argc [Description du param�tre]
 * @param argv [Description du param�tre]
 * @return int [Description du retour]
 */
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

    // Vérification d'existence et ouverture des fichiers
/**
 * @brief [Description de f1]
 *
 * @param namefichier [Description du param�tre]
 * @return ifstream [Description du retour]
 */
    ifstream f1(namefichier);
/**
 * @brief [Description de f2]
 *
 * @param namefichier2 [Description du param�tre]
 * @return ifstream [Description du retour]
 */
    ifstream f2(namefichier2);

    if (!f1.is_open()) {
        cout << "Erreur : Impossible d'ouvrir le fichier " << namefichier << endl;
        exit(2);
    }

    if (!f2.is_open()) {
        cout << "Erreur : Impossible d'ouvrir le fichier " << namefichier2 << endl;
        exit(3);
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

    // Fermeture des fichiers
    f1.close();
    f2.close();

    return 0;
}
