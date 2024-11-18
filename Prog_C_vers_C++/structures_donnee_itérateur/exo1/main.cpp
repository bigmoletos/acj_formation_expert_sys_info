#include <vector>
#include <iostream>
#include <list>
using namespace std;

// Fonction pour afficher les éléments d'un std::vector
void afficher_vector(const vector<int>& vec) {
    cout << "Contenu du vector : ";
    for (int x : vec) {
        cout << x << " ";
    }
    cout << endl;
}

// Fonction pour afficher les éléments d'une std::list
void afficher_list(const list<int>& lst) {
    cout << "Contenu de la list : ";
    for (int x : lst) {
        cout << x << " ";
    }
    cout << endl;
}

// Fonction pour calculer la somme des éléments d'un std::vector
int somme_vector(const vector<int>& vec) {
    int somme = 0;
    for (int x : vec) {
        somme += x;
    }
    return somme;
}

// Fonction pour multiplier chaque élément d'un std::vector par 2
void multiplier_vector_par_2(vector<int>& vec) {
    for (auto& x : vec) {
        x *= 2;
    }
}

// Fonction pour ajouter 5 à chaque élément d'une std::list
void ajouter_5_list(list<int>& lst) {
    for (auto& x : lst) {
        x += 5;
    }
}

int main() {
    // ----- VECTOR -----
    // 1. Créez un std::vector qui contient les nombres pairs de 2 à 10.
    vector<int> myVector = {2, 4, 6, 8, 10};
    cout << "Vector initial : ";
    afficher_vector(myVector);

    // Ajouter 6, 7, 8 au vector
    myVector.push_back(6);
    myVector.push_back(7);
    myVector.push_back(8);
    afficher_vector(myVector);

    // Supprimer le dernier élément
    myVector.pop_back();
    cout << "Après suppression du dernier élément : ";
    afficher_vector(myVector);

    // Calculer la somme des éléments
    int somme = somme_vector(myVector);
    cout << "Somme des éléments du vector : " << somme << endl;

    // Multiplier chaque élément par 2
    multiplier_vector_par_2(myVector);
    cout << "Après multiplication par 2 : ";
    afficher_vector(myVector);

    // ----- LIST -----
    // 1. Créez une std::list qui contient les nombres impairs de 1 à 9.
    list<int> myList = {1, 3, 5, 7, 9};
    afficher_list(myList);

    // Ajouter un élément à la fin et au début
    myList.push_back(15);
    myList.push_front(0);
    afficher_list(myList);

    // Ajouter 5 à chaque élément de la liste
    ajouter_5_list(myList);
    cout << "Après ajout de 5 à chaque élément : ";
    afficher_list(myList);

    return 0;
}
