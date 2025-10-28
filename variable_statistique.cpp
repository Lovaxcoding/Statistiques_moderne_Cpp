#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <limits> 
#include <stdexcept> // Pour des exceptions de test plus propres

// -------------------------------------------------------------------------
// CLASSE VariableStatistique (inchangée)
// -------------------------------------------------------------------------

class VariableStatistique {
private:
    std::vector<double> donnees;

public:
    VariableStatistique(const std::vector<double>& obs) : donnees(obs) {}

    const std::vector<double>& getDonnees() const {
        return donnees;
    }
    
    double moyenne() const {
        if (donnees.empty()) return 0.0;
        double somme = 0.0;
        for (double val : donnees) {
            somme += val;
        }
        return somme / donnees.size();
    }

    double variance() const {
        if (donnees.size() < 1) return 0.0;
        double mu = moyenne();
        double sommeCarresEcarts = 0.0;
        for (double val : donnees) {
            sommeCarresEcarts += std::pow(val - mu, 2);
        }
        return sommeCarresEcarts / donnees.size(); 
    }

    std::vector<double> mode() const {
        std::map<double, int> frequences;
        for (double val : donnees) {
            frequences[val]++;
        }
        int maxFreq = 0;
        for (const auto& pair : frequences) {
            if (pair.second > maxFreq) {
                maxFreq = pair.second;
            }
        }
        std::vector<double> modes;
        if (maxFreq <= 1 && donnees.size() > 1) { 
            return {};
        }
        for (const auto& pair : frequences) {
            if (pair.second == maxFreq) {
                modes.push_back(pair.first);
            }
        }
        return modes;
    }
    
    double operator*(const VariableStatistique& autre) const {
        if (this->donnees.size() != autre.donnees.size()) {
            std::cerr << "Erreur: Les variables doivent avoir la même taille pour le produit scalaire." << std::endl;
            return 0.0;
        }
        double produitScalaire = 0.0;
        for (size_t i = 0; i < donnees.size(); ++i) {
            produitScalaire += this->donnees[i] * autre.donnees[i];
        }
        return produitScalaire;
    }
};


// -------------------------------------------------------------------------
// FONCTION UTILITAIRE POUR LA SAISIE (du mode interactif)
// -------------------------------------------------------------------------

std::vector<double> saisirDonnees(const std::string& nomVariable) {
    // ... La fonction saisirDonnees est la même ...
    std::vector<double> data;
    std::string ligne_entree;

    std::cout << "\nEntrez les observations pour la Variable " << nomVariable << " (separees par des espaces) :\n> ";
    std::getline(std::cin, ligne_entree);

    std::stringstream ss(ligne_entree);
    double valeur;

    while (ss >> valeur) {
        data.push_back(valeur);
    }

    if (data.empty()) {
        std::cout << "Attention : Aucune donnee valide n'a ete saisie.\n";
    } else {
        std::cout << data.size() << " donnees lues pour la Variable " << nomVariable << ".\n";
    }

    return data;
}

// -------------------------------------------------------------------------
// FONCTION D'AFFICHAGE ET DE VÉRIFICATION POUR LES TESTS
// -------------------------------------------------------------------------

/**
 * @brief Exécute une série de tests prédéfinis pour valider la classe VariableStatistique.
 */
void executerTestsAutomatiques() {
    std::cout << "\n--- EXECUTION DES TESTS AUTOMATIQUES DE LA CLASSE STATISTIQUE ---\n";
    std::cout << std::fixed << std::setprecision(2);

    // Données de test (identiques à celles de l'exercice original)
    std::vector<double> dataA = {10, 15, 12, 10, 18, 15, 10, 14};
    std::vector<double> dataB = {2, 3, 1, 2, 4, 3, 2, 3};
    
    VariableStatistique A(dataA);
    VariableStatistique B(dataB);

    // --- TEST 1 : Moyenne, Variance et Mode (Variable A) ---
    std::cout << "\n[TEST 1] Analyse de la Variable A : {10, 15, 12, 10, 18, 15, 10, 14}\n";
    
    double moyenne_attendue = 13.00;
    double variance_attendue = 7.50;
    std::vector<double> mode_attendu = {10.00}; // Le mode est 10.00 (3 fois)
    
    if (std::abs(A.moyenne() - moyenne_attendue) < 0.01) {
        std::cout << "   Moyenne: " << A.moyenne() << " (Attendu: 13.00)\n";
    } else {
        std::cerr << "   Moyenne: Echec! Obtenu " << A.moyenne() << " (Attendu: 13.00)\n";
    }
    
    if (std::abs(A.variance() - variance_attendue) < 0.01) {
        std::cout << "   Variance: " << A.variance() << " (Attendu: 7.50)\n";
    } else {
        std::cerr << "   Variance: Echec! Obtenu " << A.variance() << " (Attendu: 7.50)\n";
    }

    if (!A.mode().empty() && A.mode()[0] == mode_attendu[0]) {
        std::cout << "   Mode: " << A.mode()[0] << " (Attendu: 10.00)\n";
    } else {
        std::cerr << "   Mode: Echec! Obtenu un autre mode ou vide.\n";
    }

    // --- TEST 2 : Produit Scalaire (A * B) ---
    std::cout << "\n[TEST 2] Produit Scalaire (A * B) : \n";
    
    double produit_attendu = 276.00; 
    double produit_calcule = A * B;
    
    if (std::abs(produit_calcule - produit_attendu) < 0.01) {
        std::cout << "   Produit Scalaire: " << produit_calcule << " (Attendu: 276.00)\n";
    } else {
        std::cerr << "   Produit Scalaire: Echec! Obtenu " << produit_calcule << " (Attendu: 276.00)\n";
    }

    std::cout << "\n--- FIN DES TESTS AUTOMATIQUES ---\n";
}

// -------------------------------------------------------------------------
// NOUVEAU MAIN AVEC CHOIX DU MODE
// -------------------------------------------------------------------------

int main() {
    std::cout << "--- Generateur Statistique C++ ---\n";
    std::cout << "Choisissez le mode d'execution :\n";
    std::cout << "1. Executer les Tests Automatiques (Donnees fixes)\n";
    std::cout << "2. Mode Interactif (Saisie Utilisateur)\n";
    std::cout << "Votre choix (1 ou 2) : ";

    int choix;
    if (!(std::cin >> choix)) {
        std::cerr << "Erreur de lecture du choix. Arret.\n";
        return 1;
    }
    
    // Vider le buffer après la lecture de 'choix' pour les prochaines saisies
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (choix == 1) {
        // Exécution du mode Test
        executerTestsAutomatiques();
        return 0;
    } 
    
    if (choix == 2) {
        // Exécution du mode Interactif (code original)
        std::cout << std::fixed << std::setprecision(2); 

        // Saisie des Variables
        std::vector<double> dataA = saisirDonnees("A");
        if (dataA.empty()) return 0;
        VariableStatistique A(dataA);

        std::vector<double> dataB = saisirDonnees("B");
        VariableStatistique B(dataB);

        // Menu d'Analyse
        int action = 0;
        while (action != 4) {
            std::cout << "\n======================================================\n";
            std::cout << "Choisissez une action :\n";
            std::cout << "1. Afficher Moyenne, Variance et Mode de la Variable A\n";
            std::cout << "2. Calculer le Produit Scalaire (A * B)\n";
            std::cout << "3. Afficher les donnees brutes (A et B)\n";
            std::cout << "4. Quitter\n";
            std::cout << "Votre choix : ";

            if (!(std::cin >> action)) {
                // Gérer les erreurs de saisie (non-entier)
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                action = 0; 
            }
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (action) {
                case 1: {
                    std::cout << "\n--- Resultats Statistiques pour la Variable A ---\n";
                    std::cout << "Moyenne (mu) : " << A.moyenne() << "\n";
                    std::cout << "Variance     : " << A.variance() << "\n";
                    std::vector<double> modesA = A.mode();
                    std::cout << "Mode(s)      : ";
                    if (modesA.empty()) {
                        std::cout << "Non trouve.\n";
                    } else {
                        for (size_t i = 0; i < modesA.size(); ++i) {
                            std::cout << modesA[i] << (i < modesA.size() - 1 ? ", " : "");
                        }
                        std::cout << "\n";
                    }
                    break;
                }
                case 2: {
                    if (dataB.empty()) {
                        std::cerr << "Impossible: La Variable B n'a pas de donnees.\n";
                    } else if (dataA.size() != dataB.size()) {
                        std::cerr << "Impossible: Les Variables A et B doivent avoir le meme nombre d'observations.\n";
                    } else {
                        double produit = A * B;
                        std::cout << "\n-> Produit Scalaire (A * B) : " << produit << "\n";
                    }
                    break;
                }
                case 3: {
                    std::cout << "\n--- Donnees Brutes ---\n";
                    std::cout << "Variable A (" << dataA.size() << " elements) : ";
                    for (double val : dataA) std::cout << val << " ";
                    std::cout << "\nVariable B (" << dataB.size() << " elements) : ";
                    for (double val : dataB) std::cout << val << " ";
                    std::cout << "\n";
                    break;
                }
                case 4:
                    std::cout << "\nAu revoir. \n";
                    break;
                default:
                    std::cerr << "Choix invalide. Veuillez reessayer.\n";
                    break;
            }
        }
        return 0;
    }

    // Choix non 1 ni 2
    std::cerr << "\nChoix invalide. Arret du programme.\n";
    return 1;
}