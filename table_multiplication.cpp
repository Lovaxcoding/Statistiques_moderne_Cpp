#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>

// La fonction de multiplication elle-même (le moteur)
void afficherTableMultiplication(int base, int debut = 1, int fin = 10) {
    // S'assurer que le début est inférieur ou égal à la fin
    if (debut > fin) {
        std::swap(debut, fin); 
    }

    std::cout << "\n--- Table de multiplication de " << base 
              << " (de " << debut << " à " << fin << ") ---" << std::endl;

    for (int i = debut; i <= fin; ++i) {
        std::cout << base << " x " << i << " = " << (base * i) << std::endl;
    }
    std::cout << "---------------------------------------------------------\n" << std::endl;
}

// Fonction de Test Automatique pour la logique d'appel
void executerTestsAutomatiques() {
    std::cout << "--- EXECUTION DES TESTS AUTOMATIQUES ---\n";
    
    // CAS 1 : Appel avec 1 argument (doit utiliser debut=1, fin=10 par défaut)
    std::cout << "TEST 1/3 : Base seule (4).\n";
    afficherTableMultiplication(4);

    // CAS 2 : Appel avec 2 arguments (base et debut, doit utiliser fin=10 par défaut)
    std::cout << "TEST 2/3 : Base (9) et Debut (5).\n";
    afficherTableMultiplication(9, 5);
    
    // CAS 3 : Appel avec 3 arguments (base, debut, fin)
    std::cout << "TEST 3/3 : Base (13), Debut (10) et Fin (15).\n";
    afficherTableMultiplication(13, 10, 15);
    
    // Bonus : Test de la robustesse (debut > fin)
    std::cout << "BONUS : Base (6), Debut (20) et Fin (15) [Les bornes doivent s'inverser].\n";
    afficherTableMultiplication(6, 20, 15);

    std::cout << "--- FIN DES TESTS AUTOMATIQUES ---\n";
}

// Nouvelle fonction principale interactive
int main() {
    std::cout << "Choisissez le mode d'execution :\n";
    std::cout << "1. Executer les Tests Automatiques\n";
    std::cout << "2. Mode Interactif (Saisie Utilisateur)\n";
    std::cout << "Votre choix (1 ou 2) : ";

    int choix;
    std::cin >> choix;
    
    // Vider le buffer après la lecture de 'choix'
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (choix == 1) {
        executerTestsAutomatiques();
        return 0;
    } 
    
    if (choix != 2) {
        std::cerr << "\nChoix invalide. Arret du programme.\n";
        return 1;
    }
    
    // --- Début du Mode Interactif (Code original) ---
    
    std::cout << "\n--- Generateur de Table de Multiplication Interactive ---\n";
    std::cout << "Entrez les arguments, separes par des espaces (Base [Debut] [Fin]):\n";
    std::cout << "Exemples : '5', ou '5 3', ou '5 15 20' : ";

    std::string ligne_entree;
    if (!std::getline(std::cin, ligne_entree)) {
        return 0;
    }

    std::stringstream ss(ligne_entree);
    std::vector<int> arguments;
    int valeur;

    while (ss >> valeur) {
        arguments.push_back(valeur);
    }
    
    if (arguments.empty()) {
        std::cerr << "\nERREUR: Aucune valeur n'a ete entree. Arret du programme.\n";
        return 1;
    }

    int base = arguments[0];
    int debut, fin;

    switch (arguments.size()) {
        case 1:
            std::cout << "\n-> Un argument detecte (Base).";
            afficherTableMultiplication(base);
            break;
        case 2:
            debut = arguments[1];
            std::cout << "\n-> Deux arguments detectes (Base, Debut).";
            afficherTableMultiplication(base, debut);
            break;
        case 3:
            debut = arguments[1];
            fin = arguments[2];
            std::cout << "\n-> Trois arguments detectes (Base, Debut, Fin).";
            afficherTableMultiplication(base, debut, fin);
            break;
        default:
            std::cerr << "\nERREUR: Nombre d'arguments invalide (" << arguments.size() << "). 1, 2 ou 3 arguments sont requis.\n";
            return 1;
    }

    return 0;
}