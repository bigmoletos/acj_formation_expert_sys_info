#ifndef COMPTEBANCAIRE_H
#define COMPTEBANCAIRE_H

class CompteBancaire
{
private:
    double solde;

public:
    CompteBancaire();
    CompteBancaire(double depotinitial=0);
    void deposer(double montant);
    double obtenirSolde();
    void retrait(double montant);
};

#endif // COMPTEBANCAIRE_H


