#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;



int main(int argc, char **argv){
    int choix = 0;

    if(argc != 3){
        cout << "Nombre d'argument invalide: ./**.exec  FichierSource FichierSortie" << endl;
        return 1;
    }

    const string nomFichierSource = argv[1];
    const string nomFichierDest = argv[2];
    string ligne;
    int tailleLigne = 0;
    int i = 0;

    if(nomFichierDest == nomFichierSource){
        cout << "Nom du fichier source identique au nom du fichier destination" <<  endl;
        exit(1);
    }
    ifstream fileSrc(argv[1]);
    ofstream fileDst(nomFichierDest);
    if(!fileSrc.is_open()){
        cout << "Impossible d'ouvrir le fichier source: " << nomFichierSource <<  endl;
        exit(2);
    }
    if(!fileDst.is_open()){
        cout << "Impossible d'ouvrir le fichier source: " << nomFichierDest <<  endl;
        exit(3);
    }


    cout << "Veuillez faire votre choix:" << endl;
    cout << "\tTapez 1 pour copier le texte" << endl;
    cout << "\tTapez 2 Mettre tout le texte en majuscules" << endl;
    cout << "\tTapez 3 Mettre tout le texte en minuscules" << endl;
    cout << "\tTapez 4 Capitaliser ce qui commence par une majuscule" << endl;
    cout << "\tTapez 5 Changement de casse des caractères alphabétiques" << endl;
    cout << "\tTapez 6 Justification à droite du contenu sur 85 caractères" << endl;
    cout << "\tTapez 7 Justification à gauche du contenu sur 85 caractères" << endl;
    cout << "\tTapez 8 ON VEUT CENTRER !!" << endl;

    cout << "Votre choix est:" << endl;
    cin >> choix;

    cout << "Vous avez fait le choix " << choix << endl;
    switch (choix){
        case 1:
            while(getline(fileSrc, ligne)){
                fileDst << ligne << endl;
            }
            break;
        case 2:
            while(getline(fileSrc, ligne)){
                for(char c:ligne)
                    fileDst << (char)toupper(c);
                fileDst << endl;
            }
            break;
        case 3:
            while(getline(fileSrc, ligne)){
                for(char c:ligne)
                    fileDst << (char)tolower(c);
                fileDst << endl;
            }
            break;
        case 4:

            break;
        case 6:
            while(getline(fileSrc, ligne)){
                fileDst << setw(85) << right << ligne << endl;
            }
            break;
        case 7:
            while(getline(fileSrc, ligne)){
                size_t first = ligne.find_first_not_of(" \t\n\r\v");
                if(first != string::npos)
                    ligne = ligne.substr(first);
                // cout << "First dans dest: " << first << endl;
                tailleLigne = ligne.size();
                if(tailleLigne < 85){
                    ligne += (string(85 - tailleLigne, ' '));
                }
                fileDst << ligne << endl;
            }
            break;
            case 8:
                while(getline(fileSrc, ligne)){
                    size_t first = ligne.find_first_not_of(" \t\n\r\v");
                    size_t last = ligne.find_last_not_of(" \t\n\r\v");
                    if(first != string::npos)
                        ligne = ligne.substr(first);
                    if(last != string::npos)
                        cout << "ligne dans dest: " << last << " " << i << endl;
                        // ligne = ligne.substr(last);
                    int ajout = (85 - (last))/2;


                    if(last < 85){
                        ligne = (string(ajout, ' ')) + ligne + (string(ajout, ' '));
                        // ligne += (string(ajout, ))
                    }
                    fileDst << ligne << endl;
                    i++;
                }
                break;
        default:
            break;
    }
    return 0;
}