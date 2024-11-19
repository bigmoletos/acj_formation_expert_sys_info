#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;


/**
 * @brief [Description de main]
 *
 * @param argc [Description du param�tre]
 * @param *argv[] [Description du param�tre]
 * @return int [Description du retour]
 */
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        cout << "wrong number of arguments" << endl;
        exit(1);
    }

    const string filename = argv[1];
    long int count = 0;
    int val;

    // Ouvrir le fichier
/**
 * @brief [Description de data_f]
 *
 * @param filename [Description du param�tre]
 * @return ifstream [Description du retour]
 */
    ifstream data_f(filename);
    if (!data_f.is_open())
    {
        cout << "The file " << filename << " could not be opened" << endl;
        exit(2);
    }

    cout << "The file " << filename << " has been opened" << endl;

    // Lire les valeurs du fichier
    while (!data_f.eof())
    {
        if (data_f >> val)
        {
            count++;
        }
    }
    data_f.close();

    const long int nb_elements = count;
    cout << nb_elements << " elements found in: " << filename << endl;

    // Réouvrir le fichier pour charger les valeurs dans un tableau
    data_f.open(filename);
    int *tab_of_ints = new int[nb_elements];
    count = 0;
    while (!data_f.eof())
    {
        if (data_f >> val)
        {
            tab_of_ints[count++] = val;
        }
    }
    data_f.close();

    cout << count << " values read from " << filename << endl;
    cout << "Tab generated from " << filename << endl;

    // Question 2 : Trouver toutes les occurrences d'une valeur
    cout << "*** Question 2: All occurrences ***" << endl;

    int goal = 19; // Valeur à rechercher
    count = 0;

    // Mesure de temps pour la recherche dans le fichier
    auto t1 = high_resolution_clock::now();
    data_f.open(filename);
    cout << "Finding goal in file at position: " << endl;
    while (!data_f.eof())
    {
        if (data_f >> val)
        {
            if (val == goal)
            {
                cout << count << " ";
            }
            count++;
        }
    }
    data_f.close();
    auto t2 = high_resolution_clock::now();

    cout << endl
         << goal << " found at positions (in file)" << endl;

    // Mesure de temps pour la recherche dans le tableau
    auto t3 = high_resolution_clock::now();
    cout << "Finding goal in array at position: " << endl;
    for (long int i = 0; i < nb_elements; i++)
    {
        if (tab_of_ints[i] == goal)
        {
            cout << i << " ";
        }
    }
    auto t4 = high_resolution_clock::now();

    // Calcul du temps de traitement
    auto time_f = duration_cast<microseconds>(t2 - t1).count();
    auto time_a = duration_cast<microseconds>(t4 - t3).count();

    cout << "\nProcessing from file: " << time_f << " µs" << endl;
    cout << "Processing from array: " << time_a << " µs" << endl;
    cout << "Factor of gain: " << static_cast<double>(time_f) / time_a << endl;

    delete[] tab_of_ints; // Libérer la mémoire allouée pour le tableau

    return 0;
}
