#include "CVehicule.hpp"
#include "CMoto.hpp"
#include "CVoiture.hpp"
#include <vector>
#include <iostream>

int main() {
    // SOLUTION AVEC TABLEAU STATIQUE
    CVehicule veh;
    CVoiture voit("Voiture");
    CMoto moto("Moto");

    // Tableau statique de type CVehicule
    // Attention : cette solution ne permet pas de bénéficier du polymorphisme
    CVehicule tabStatique[3];
    tabStatique[0] = veh;
    tabStatique[1] = voit;  // Les objets dérivés seront "troncés" vers la classe de base CVehicule
    tabStatique[2] = moto;   // Le polymorphisme ne fonctionne pas correctement ici

    for (int i = 0; i < 3; i++) {
        tabStatique[i].afficher();  // Appelle afficher() de CVehicule pour tous
    }
    // SOLUTION AVEC TABLEAU STATIQUE avec POINTERS
    CVehicule* pVeh = new CVehicule();
    CVoiture* pVoit = new CVoiture("Citroen");
    CMoto* pMoto = new CMoto("Aprilia");

    // Tableau statique de type CVehicule
    // Attention : cette solution ne permet pas de bénéficier du polymorphisme
        CVehicule* tabDynamique[3];
    tabDynamique[0] = pVeh;
    tabDynamique[1] = pVoit;// Les objets dérivés seront "troncés" vers la classe de base CVehicule
    tabDynamique[2] = pMoto;// Le polymorphisme ne fonctionne pas correctement ici

    for (int i = 0; i < 3; i++) {
        tabDynamique[i]->afficher();  // Appelle afficher() de CVehicule pour tous
    }

    // SOLUTION AVEC TABLEAU PAR POINTEURS (POLYMORPHISME)
    std::cout << "\nSolution avec tableau de pointeurs :\n";
    CVehicule* vehicules[] = { new CVehicule(), new CMoto("Piaggio"), new CVoiture("Volvo") };

    for (auto vehicule : vehicules) {
        vehicule->afficher();  // Appelle la version redéfinie de afficher() dans chaque classe
    }

    // SOLUTION AVEC std::vector POUR PLUS DE FLEXIBILITÉ
    std::cout << "\nSolution avec std::vector de pointeurs :\n";
    std::vector<CVehicule*> tableauVehicules;

    // Ajout des véhicules spécifiques au vecteur
    tableauVehicules.push_back(new CVoiture("Volvo"));
    tableauVehicules.push_back(new CVoiture("Toyota"));
    tableauVehicules.push_back(new CMoto("Piaggio"));
    tableauVehicules.push_back(new CMoto("Honda"));

    // Affichage des éléments du vecteur
    for (auto vehicule : tableauVehicules) {
        vehicule->afficher();
    }

    // Libération de la mémoire pour éviter les fuites mémoire
    std::cout << "\nLibération de la mémoire :\n";
    for (auto vehicule : tableauVehicules) {
        std::cout << "Destruction du pointeur : " << vehicule << std::endl;
        delete vehicule;  // Appelle le destructeur approprié pour chaque objet
    }

    // Libération de la mémoire pour le tableau de pointeurs statique
    for (auto vehicule : vehicules) {
        delete vehicule;
    }

    return 0;
}
