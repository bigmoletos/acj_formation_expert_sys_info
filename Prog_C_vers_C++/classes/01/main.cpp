#include <iostream>
#include "first_classe.hpp"

using namespace std;

int main()
{
    CompteBancaire cb1(0); // (solde de cb1)
    cb1.deposer(500);
    cb1.retrait(200);
    double s = cb1.obtenirSolde();

    CompteBancaire cb2(421.56); // (solde de cb2)
    cb2.retrait(200);
}

