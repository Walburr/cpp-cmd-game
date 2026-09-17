# Aventure Textuelle — RPG en C++

Petit jeu de rôle textuel jouable dans le terminal, écrit en C++ pur (sans dépendances externes). Le joueur avance vers un château en évitant ou en affrontant des ennemis aléatoires, avec un système de combat au tour par tour (attaque / soin / esquive) et une progression par niveaux.

## Fonctionnalités

- Déplacement progressif vers l'objectif final (le château), avec un risque de rencontre à chaque avancée
- Combats au tour par tour :
  - Attaquer l'ennemi
  - Se soigner
  - Esquiver l'attaque ennemie en devinant un nombre
- Système de PV, de dégâts et de vie ennemie, calculés aléatoirement et mis à l'échelle selon le niveau du joueur
- Système d'expérience et de montée de niveau
- Stats générées aléatoirement à chaque combat (vie ennemie, dégâts, soin, esquive)

## Prérequis

- Un compilateur C++ supportant C++17 (`g++` ou `clang++`)
- Un système Linux/macOS (le jeu utilise `system("clear")` et `<unistd.h>` pour `sleep`, non portables tels quels sur Windows)

## Compilation

```bash
g++ -std=c++17 main.cpp -o jeu
```

## Lancer le jeu

```bash
./jeu
```

## Comment jouer

- À chaque étape, répondez `y` pour avancer ou `n` pour rester où vous êtes
- En avançant, un nombre aléatoire (1 ou 2) détermine si vous croisez un ennemi ; devinez-le pour tenter d'éviter le combat
- En combat :
  - Tapez `a` pour attaquer, `h` pour vous soigner
  - Lors du tour de l'ennemi, devinez un nombre entre 1 et 8 pour esquiver son attaque
- Atteignez 15 avancées réussies pour gagner la partie

## Limitations connues / pistes d'amélioration

- Le jeu est entièrement en boucle console (`cin`/`cout`), sans interface graphique
- La logique de combat est concentrée dans quelques fonctions globales (`fight()`, `EnemieTour()`) plutôt que dans des classes dédiées — une passe de refactorisation (classes `Player`/`Enemy`, séparation logique/affichage) est une prochaine étape naturelle
- Les commandes système (`system("clear")`, `sleep()`) limitent la portabilité à Linux/macOS
- Pas de tests automatisés à ce jour

## Auteur

Walbur — [portfolio](https://walblur.vercel.app) · [GitHub](https://github.com/Walburr)
