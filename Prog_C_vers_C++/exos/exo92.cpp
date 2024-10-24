#include <iostream>
#include <fstream>
#include <string>

using namespace std ;

int main (int argc, char** argv) {

  if (argc < 3) {
    cout << "no enough arguments" << endl ;
    exit(1);
  }

  if (argc > 3) {
    cout << "too much arguments" << endl ;
    exit(2);
  }

  string name1 = argv[1] ;
  string name2 = argv[2] ;

  ifstream file1 (name1) ;
  ifstream file2 (name2) ;

  char x, y ;

  if (!file1.is_open()) {
    cout << name1 << " doesn't exist" << endl;
    exit(3) ;
  }

  if (name1 == name2){
    cout << "same file twice." << endl;
    file1.close();
    return 0;
  }

  if (!file2.is_open()) {
    cout << name2 << " doesn't exist" << endl;
    exit(3) ;
  }
//comparaison des fichiers
  while ( (file1 >> x) && (file2 >> y) ) {
    if (x != y) {
        cout << name1 << " et " << name2 << " sont différents " << endl;
        // file1.close();
        // file2.close();
        exit (5) ;
    }
    else if (x == y)
    {
        cout << name1 << " et " << name2 << " sont identical" << endl;
        file1.close();
        file2.close();

        return 0 ;
    /* code */
    }



    file1.close();
    file2.close();

    return 0 ;
}
}