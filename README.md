# Todo List Manager (C++)
Une application console performante conçue en C++ pour gérer efficacement vos tâches quotidiennes. Ce projet met en œuvre les principes de la programmation orientée objet (POO) et assure la persistance des données via un système de fichiers.

## Fonctionnalités
- Gestion complète des tâches : Ajouter, modifier ou supprimer des tâches en toute simplicité.hg

- Organisation avancée : Définition de priorités (Basse, Moyenne, Haute) et suivi du statut (À faire, En cours, Terminé).

- Persistance des données : Sauvegarde automatique et chargement des tâches depuis un fichier local pour ne jamais perdre vos informations.
- Interface Intuitive : Navigation simplifiée via une interface en ligne de commande (CLI).

## Technologies utilisées
- C++
- CMake
- Git & GitHub


## Features
- Add / delete / modify tasks
- Priority and status management
- File saving/loading


## Installation et Utilisation
Prérequis: 
- Un compilateur C++ (GCC, Clang ou MSVC)
- CMake (version 3.10 ou supérieure)

Compilation:
Pour compiler le projet, exécutez les commandes suivantes dans votre terminal :

```Bash
# Créer le répertoire de build
mkdir build
cd build

# Générer les fichiers de build avec CMake
cmake ..

# Compiler le projet
make
```
Exécution:
Une fois la compilation terminée, lancez l'application :

```Bash
./todo_list_cpp
```
## Structure du Projet
```src/ ```: Contient les fichiers sources (.cpp).

```include/ ```: Contient les fichiers d'en-tête (.hpp ou .h).

```CMakeLists.txt``` : Configuration du projet pour CMake.

```data/``` : Répertoire de stockage pour les fichiers de sauvegarde.

## Contribution
Les contributions sont les bienvenues ! N'hésitez pas à ouvrir une issue ou à soumettre une pull request pour améliorer ce gestionnaire de tâches.
