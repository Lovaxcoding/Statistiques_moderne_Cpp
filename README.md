# 📊 Statistiques Moderne en C++

Un mini-projet en **C++ moderne** permettant de manipuler des variables statistiques et de calculer leurs indicateurs principaux : moyenne, variance, mode, ainsi qu’un produit scalaire entre deux séries de données.
Le programme offre deux modes d’exécution : **tests automatiques** et **mode interactif utilisateur**.

---

## 🚀 Fonctionnalités principales

### 🧮 Classe `VariableStatistique`

Cette classe gère un ensemble de données numériques et propose :

* `moyenne()` : calcul de la moyenne arithmétique
* `variance()` : calcul de la variance
* `mode()` : détection du ou des modes
* `operator*` : calcul du produit scalaire entre deux variables statistiques

### 🔍 Fonctions principales

* **Mode test automatique** : exécute des cas de test internes pour valider les calculs.
* **Mode interactif** : permet à l’utilisateur de saisir ses propres données et de choisir les analyses à effectuer.

---

## 🧰 Technologies utilisées

* **Langage** : C++17
* **Compilateur** : MinGW (g++)
* **IDE conseillé** : Visual Studio Code avec l’extension *C/C++ de Microsoft*
* **Standard Libraries** : `<iostream>`, `<vector>`, `<cmath>`, `<map>`, `<algorithm>`, `<iomanip>`, `<sstream>`, `<limits>`, `<stdexcept>`

---

## 🧪 Exemple de tests automatiques

Lors du lancement du programme en **mode test**, le code exécute automatiquement :

```text
[TEST 1] Variable A : {10, 15, 12, 10, 18, 15, 10, 14}
   Moyenne: 13.00
   Variance: 7.50
   Mode: 10.00

[TEST 2] Produit Scalaire (A * B)
   Produit Scalaire: 276.00
```

---

## 💻 Exécution du programme

### 1️⃣ Compilation

Assure-toi d’être dans le dossier du projet, puis exécute :

```bash
g++ main.cpp -o stats.exe
```

### 2️⃣ Lancement

```bash
./stats.exe
```

### 3️⃣ Choisis le mode d’exécution

```
--- Generateur Statistique C++ ---
1. Executer les Tests Automatiques (Donnees fixes)
2. Mode Interactif (Saisie Utilisateur)
Votre choix (1 ou 2) :
```

---

## 🧠 Exemple d’utilisation (mode interactif)

```
Entrez les observations pour la Variable A :
> 10 15 12 10 18 15 10 14
Entrez les observations pour la Variable B :
> 2 3 1 2 4 3 2 3

Choisissez une action :
1. Moyenne, Variance et Mode de A
2. Produit Scalaire (A * B)
3. Données brutes
4. Quitter
```

---

## 📁 Structure du projet

```
Statistiques_moderne_Cpp/
│
├── main.cpp                 # Code source principal
├── .vscode/                 # Configurations pour VSCode (optionnel)
├── README.md                # Documentation du projet
└── .gitignore               # Fichiers ignorés par Git (exécutables, dossiers temporaires, etc.)
```

---

## 🧾 Licence

Projet open-source sous licence MIT.
Tu es libre de l’utiliser, le modifier et le distribuer à des fins éducatives ou personnelles.

---

## 👤 Auteur

**Lovasoa Nantenaina**
💼 Développeur passionné par le C++ moderne, les statistiques et la programmation scientifique.
🔗 [GitHub – Lovaxcoding](https://github.com/Lovaxcoding)
