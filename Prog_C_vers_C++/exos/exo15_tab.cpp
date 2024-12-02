#include <array>
#include <iostream>
using namespace std;

/**
 * @brief [Description de main]
 *
 * @param void [Description du param�tre]
 * @return int [Description du retour]
 */
int main(void)
{
    const int array_size(11); // Déclaration de la taille du tableau

    // Déclaration des arrays avec std::array
    array<int, array_size> a_1 = {};                   // Initialisation par défaut à 0
    array<int, array_size> a_2 = {1, 3, 5, 7, 11, 13}; // Initialisation partielle

    // Initialisation avec une autre syntaxe
    array<int, array_size> a_3 = {1, 3, 5, 7, 11, 13};
    array<int, array_size> a_4 = {1, 3, 5, 7, 11, 13};

    // Affichage des tailles et des éléments des tableaux
    cout << "res_01 : " << a_1.size() << " " << a_1[3] << endl;
    cout << "res_02 : " << a_2.size() << " " << a_2[3] << endl;
    cout << "res_03 : " << a_3.size() << " " << a_3[3] << endl;
    cout << "res_04 : " << a_4.size() << " " << a_4[3] << endl;

    // Accès sécurisé avec .at()
    cout << "res_05 : " << a_2.at(0) << endl;
    cout << "res_06 : " << a_2.at(1) << endl;

    // Vérifier les indices avant d'y accéder (éviter les accès hors limites)
    if (array_size > 9)
    {
        cout << "res_09 : " << a_2[9] << endl;
    }
    else
    {
        cout << "Index 9 hors limites!" << endl;
    }

    cout << "max_size de a_1 : " << a_1.max_size() << " (max size of int array)" << endl;

    return 0;
}

// int main(void)
// {

//     const int array_size(11);

//     array<int, array_size> a_1;
//     array<int, array_size> a_2 = {1, 3, 5, 7, 11, 13};

//     /* second way may not be working with some compilers */
//     array<int, array_size> a_3({1, 3, 5, 7, 11, 13});
//     array<int, array_size> a_4 = {1, 3, 5, 7, 11, 13};

//     cout << "res_01 : " << a_1.size() << " " << a_1[3] << endl;
//     cout << "res_02 : " << a_2.size() << " " << a_2[3] << endl;
//     cout << "res_03 : " << a_3.size() << " " << a_3[3] << endl;
//     cout << "res_04 : " << a_4.size() << " " << a_4[3] << endl;

//     cout << "res_05 : " << a_2[0] << endl;
//     cout << "res_06 : " << a_2[1] << endl;
//     cout << "res_07 : " << a_2[123] << endl;
//     cout << "res_08 : " << a_2[-1] << endl;
//     cout << "res_09 : " << a_2[9] << endl;
//     cout << "res_10 : " << a_2[99] << endl;

//     cout << a_1.max_size() << " maxsize int array " << endl;

//     return 0;
// }

// int main(void)
// {

//     const int array_size(11);

//     int a_1[array_size];
//     int a_2[array_size] a_2 = {1, 3, 5, 7, 11, 13};

//     /* may not be working with some compilers */
//     int a_2[array_size] a_3({1, 3, 5, 7, 11, 13});
//     int a_2[array_size] a_4 = {1, 3, 5, 7, 11, 13};

//     cout << "res_01 : " << a_1.size() << " " << a_1[3] << endl;
//     cout << "res_02 : " << a_2.size() << " " << a_2[3] << endl;
//     cout << "res_03 : " << a_3.size() << " " << a_3[3] << endl;
//     cout << "res_04 : " << a_4.size() << " " << a_4[3] << endl;

//     cout << "res_05 : " << a_2[0] << endl;
//     cout << "res_06 : " << a_2[1] << endl;
//     cout << "res_07 : " << a_2[123] << endl;
//     cout << "res_08 : " << a_2[-1] << endl;
//     cout << "res_09 : " << a_2[9] << endl;
//     cout << "res_10 : " << a_2[99] << endl;

//     cout << a_1.max_size() << " maxsize int array " << endl;

//     return 0;
// }

// int main(void)
// {

//     int s_x(13), s_y(11), val(1);

//     vector<vector<int>> v_2_tab(s_x, vector<int>(s_y, 1));

//     /* initialization */
//     for (auto l_line : v_2_tab)
//     {
//         s_y += 11;
//         for (auto &l_pixel : l_line)
//             l_pixel = i++;
//     }

//     for (int i = 0; i < s_x; ++i)
//         for (int j = 0; j < s_y; ++j)
//             v_2_tab[i][j] = val++;

//     cout << "val: " << val << endl;
//     cout << "dimX: " << s_x << " -- dimY: " << s_y << endl;
//     cout << "best: " << v_2_tab[11][13] << endl;
// }

// int main(void)
// {

//     const int array_size(11);

//     array<int, array_size> a_1;
//     array<int, array_size> a_2 = {1, 3, 5, 7, 11, 13};

//     /* second way may not be working with some compilers */
//     array<int, array_size> a_3({1, 3, 5, 7, 11, 13});
//     array<int, array_size> a_4 = {1, 3, 5, 7, 11, 13};

//     cout << "res_01 : " << a_1.size() << " " << a_1[3] << endl;
//     cout << "res_02 : " << a_2.size() << " " << a_2[3] << endl;
//     cout << "res_03 : " << a_3.size() << " " << a_3[3] << endl;
//     cout << "res_04 : " << a_4.size() << " " << a_4[3] << endl;

//     cout << "res_05 : " << a_2[0] << endl;
//     cout << "res_06 : " << a_2[1] << endl;
//     cout << "res_07 : " << a_2[123] << endl;
//     cout << "res_08 : " << a_2[-1] << endl;
//     cout << "res_09 : " << a_2[9] << endl;
//     cout << "res_10 : " << a_2[99] << endl;

//     cout << a_1.max_size() << " maxsize int array " << endl;

//     return 0;
// }

// int main(void)
// {

//     vector<int> vect_01;

//     /* second way may not be working with some compilers */
//     vector<int> vect_02({1, 3, 5, 7, 11, 13});
//     vector<int> vect_03 = {1, 3, 5, 7, 11, 13};

//     vector<int> vect_04(25);

//     vector<int> vect_05(13, -13);

//     vector<int> vect_06(vect_05);

//     cout << "res_01 : " << vect_01.size() << endl;
//     cout << "res_02 : " << vect_02.size() << endl;
//     cout << "res_03 : " << vect_03.size() << endl;
//     cout << "res_04 : " << vect_04.size() << endl;
//     cout << "res_05 : " << vect_05.size() << endl;
//     cout << "res_06 : " << vect_06.size() << endl;

//     cout << "res_07 : " << vect_01[0] << endl;
//     cout << "res_08 : " << vect_02[1] << endl;
//     cout << "res_09 : " << vect_03[123] << endl;
//     cout << "res_10 : " << vect_04[-1] << endl;
//     cout << "res_11 : " << vect_06[9] << endl;

//     return 0;
// }
