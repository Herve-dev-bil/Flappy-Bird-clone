Voici un **README.md** professionnel, structuré pour GitHub, qui met en valeur l'aspect **ingénierie** de ton projet. Il est conçu pour impressionner ton professeur (M. TEUGUIA) et d'éventuels recruteurs.

Copie le contenu ci-dessous dans ton fichier `README.md`.

---

```markdown
# 🐦 Flappy Bird Engine (C++ / SDL3)

![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SDL3](https://img.shields.io/badge/Library-SDL3-FF3D00?style=for-the-badge&logo=sdl&logoColor=white)
![ImGui](https://img.shields.io/badge/GUI-ImGui-88C0D0?style=for-the-badge)
![Build](https://img.shields.io/badge/Build-Python_Automation-3776AB?style=for-the-badge&logo=python&logoColor=white)

> **Projet Académique - ENSPY (École Nationale Supérieure Polytechnique de Yaoundé)**
> *Module : Programmation C++ et Multimédia*

---

## 📋 Présentation

Ce projet n'est pas un simple clone de jeu. C'est un **moteur de jeu 2D modulaire** développé "from scratch" en C++17.
L'objectif était de démontrer une maîtrise approfondie de l'architecture logicielle, de la gestion bas niveau de la mémoire et de la création d'outils de développement (Tooling).

### 🌟 Fonctionnalités Clés
* **Architecture Modulaire :** Séparation stricte entre le Moteur (`Game`), les Entités (`Bird`, `Pipe`) et l'Interface (`UI`).
* **Physique Robuste :** Implémentation du `DeltaTime` pour une indépendance totale du Framerate (le jeu tourne à la même vitesse sur n'importe quel CPU).
* **Gestion Mémoire (RAII) :** Allocation dynamique contrôlée et nettoyage automatique des ressources (Zéro Memory Leak).
* **Outils de Debug :** Intégration d'**ImGui** pour modifier les variables du jeu (gravité, vitesse) en temps réel.
* **Build System Automatisé :** Script Python personnalisé pour la compilation cross-platform sans IDE.

---

## 📂 Architecture du Projet

Le projet respecte une structure standard industrielle, séparant les interfaces des implémentations.

```text
Flappy_Bird_Project/
├── assets/                 # Ressources (Images, Fonts)
├── include/                # En-têtes (.h) - Les contrats d'interface
│   ├── Game.h              # Moteur principal
│   ├── Bird.h              # Physique du joueur
│   ├── Pipe.h              # Gestion des obstacles
│   └── UI.h                # Interface ImGui
├── src/                    # Sources (.cpp) - L'implémentation
│   ├── Game.cpp
│   ├── Bird.cpp
│   ├── Pipe.cpp
│   └── UI.cpp
├── thirdparty/             # Dépendances externes (ImGui)
├── build.py                # Script d'automatisation de la compilation
├── main.cpp                # Point d'entrée
└── README.md               # Documentation

```

---

## ⚙️ Installation et Compilation

Ce projet s'affranchit des fichiers de configuration spécifiques aux IDE (comme `.sln` ou `.vscode`). Il utilise un script Python pour orchestrer la compilation via `g++`.

### Prérequis

* **C++ Compiler :** `g++` (Support C++17 requis).
* **Python 3.x :** Pour lancer le script de build.
* **Librairies :** SDL3 et SDL3_image installées sur le système.

### 🚀 Instructions de Build

1. **Cloner le dépôt :**
```bash
git clone [https://github.com/VOTRE-USER/FlappyBird-CPP.git](https://github.com/VOTRE-USER/FlappyBird-CPP.git)
cd FlappyBird-CPP

```


2. **Lancer le script de build :**
```bash
python build.py

```


*Le script détecte automatiquement votre OS (Windows/Linux), lie les bibliothèques et génère l'exécutable.*
3. **Exécuter le jeu :**
* Windows : `Flappy_Bird_by_Game_Changer.exe`
* Linux/Mac : `./Flappy_Bird_by_Game_Changer`



---

## 🎮 Contrôles et Debug

Le projet intègre deux modes d'interaction :

| Touche | Action |
| --- | --- |
| **ESPACE** | Sauter / Démarrer le jeu |
| **SOURIS** | Interagir avec l'interface ImGui |

### Interface de Debug (ImGui)

Une fenêtre de contrôle permet de :

* Visualiser le Score et le HighScore.
* Redémarrer la partie instantanément.
* *(Dev)* Ajuster la gravité ou la vitesse des tuyaux à la volée.

---

## 🧠 Défis Techniques & Apprentissages

### 1. Gestion de la Mémoire et RAII

Le défi majeur était d'éviter les fuites de mémoire lors du rechargement des niveaux.

* **Solution :** Utilisation stricte des destructeurs (`~Game`, `~Pipe`) pour libérer les textures et les pointeurs `new` avant chaque `reset`.

### 2. Indépendance du Framerate

Pour éviter que le jeu ne soit injouable sur les PC puissants (trop rapide) :

* **Solution :** Toutes les mises à jour physiques sont multipliées par le `deltaTime` (temps écoulé depuis la dernière frame).
```cpp
mVelocity += GRAVITY * deltaTime; // Physique stable

```



### 3. Normes de Codage (Convention ENSPY)

Le code respecte strictement les conventions imposées :

* `PascalCase` pour les méthodes publiques.
* `mCamelCase` pour les membres privés.
* `UPPER_SNAKE_CASE` pour les constantes.
* Documentation style **"Betty Doc"** pour chaque classe.

---

## 👤 Auteur

**[TON NOM ET PRÉNOM]**

* Étudiant Ingénieur - ENSPY
* *Contact :* [TON EMAIL]

---

*Développé avec ❤️ et beaucoup de C++.*

```

### 💡 Dernier conseil pour GitHub :
Pour que ton dépôt soit **parfait**, ajoute une capture d'écran :
1.  Lance ton jeu.
2.  Fais une capture d'écran (avec le menu ImGui visible, ça fait "Tech").
3.  Nomme l'image `screenshot.png` et mets-la dans ton dossier.
4.  Ajoute cette ligne juste après le titre dans le README :
    `![Screenshot du Moteur](screenshot.png)`

```