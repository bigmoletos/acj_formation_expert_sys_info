
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

int main() {

        // Variables pour stocker les noms des fichiers
        string namefichier{"fichiier1.txt"};

        // Vérification d'existence et ouverture des fichiers
        ifstream f1(namefichier);

    cout<<"ouverture fichier "<<namefichier<<endl;


    if(f1.is_open()){
        string line{""};
        /// lecture d'une ligne avec option ws(WhiteSpace) pour supprimer les espaces
        getline(f1 >> ws, line);

        while (getline(f1 >> ws, line))
        {
        // affichage de la ligne
        cout << line << endl;
        }
    }



        // Fermeture des fichiers
        f1.close();

//    if(fichier1.is_open() && fichier2.is_open() &&fichier3.is_open() && fichier4.is_open()&& nom1!=nom2&&nom2!=nom3&&nom1!=nom3 ){
//       while (true)
//       {

//          if (ligne%3==1)         fichier2.get(c);
//          else if(ligne%3==2)     fichier3.get(c);
//          else                    fichier4.get(c);

//          fichier1.write( &c,sizeof(char));
//          if(fichier4.eof()) break;
//          if(c=='\n') ligne+=1;
//       }



//    }else cout<<"l'un des fichier n'existe pas, ou le meme fichier a ete choisi 2 fois"<<endl;





    return 0;
}
