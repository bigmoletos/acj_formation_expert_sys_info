#include "first_classe.hpp"

// constructeur par defaut
//  on initialise la valeur du solde à 0 à l'intitialisation du compte
CompteBancaire::CompteBancaire() {
   solde = 0;
}

CompteBancaire::CompteBancaire(double depotinitial) {
   solde = depotinitial;
}

CompteBancaire::CompteBancaire() : solde(0) {}

void CompteBancaire::deposer(double montant)
{
    if (montant > 0)
        solde += montant;
}

double CompteBancaire::obtenirSolde()
{
    return solde;
}

void CompteBancaire::retrait(double montant)
{
    if (montant > 0 && montant <= solde)
        solde -= montant;
}
