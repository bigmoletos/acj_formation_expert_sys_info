#include "voiture.hpp"
#include "first_classe.hpp"

#include <string>


// //constructeur par defaut
Voiture::Voiture() {
  cb = nullptr;
}

// Constructeur avec paramètres
Voiture::Voiture(const std::string& marque, const std::string& modele, int annee) : marque(marque), modele(modele), annee(annee) {
    cb = new CompteBancaire();
    // pointeur null
}
// Constructeur avec paramètres 2 écriture possbie
// Voiture::Voiture(const std::string& marque, const std::string& modele, int annee) :{
//  marque(marque);
//  modele(modele);
//  annee(annee);
// }
// destructeur
Voiture::~Voiture(){
   if (cb) delete cb;
}

// Setter pour marque
void Voiture::setMarque(const std::string& marqueV) {
    marque = marqueV;
}

// Setter pour modele
void Voiture::setModele(const std::string& modeleV) {
    modele = modeleV;
}

// Setter pour annee
void Voiture::setAnnee(int anneeV) {
    annee = anneeV;
}

// Getter pour marque
std::string Voiture::getMarque() const {
    return marque;
}

// Getter pour modele
std::string Voiture::getModele() const {
    return modele;
}

// Getter pour annee
int Voiture::getAnnee() const {
    return annee;
}