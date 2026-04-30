# Gestionnaire de Tâches (Todo List)
Une application console performante conçue en C++ pour gérer efficacement vos tâches quotidiennes. Ce projet met en œuvre les principes de la programmation orientée objet (POO) et assure la persistance des données via un système de fichiers.

## Fonctionnalités
- Gestion complète des tâches : Ajouter, modifier ou supprimer des tâches en toute simplicité.
- Organisation avancée : Définition de priorités (Basse, Moyenne, Haute) et suivi du statut (À faire, En cours, Terminé).

- Persistance des données : Sauvegarde automatique et chargement des tâches depuis un fichier local pour ne jamais perdre vos informations.
- Interface Intuitive : Navigation simplifiée via une interface en ligne de commande (CLI).

## Technologies utilisées
- C++
- CMake
- Git & GitHub

## Fonctionnalités

- Gestion des tâches : ajouter, supprimer, modifier et afficher des tâches  
- Priorités (enum `Priority`) : Basse, Moyenne, Haute  
- Statuts (enum `Status`) : À faire, En cours, Terminé  
- Sauvegarde des données dans un fichier (`FileManager::save`)  
- Dates limites (deadlines)  
- Filtrage et tri  
  *(ex : afficher uniquement les tâches de priorité HIGH, trier par urgence)*  
- Système de notification simulée  
  *(ex : "Tâche bientôt due")*  
- Statistiques  
  *(ex : nombre de tâches DONE / TODO / IN PROGRESS)*  
- Archivage des tâches terminées  
  *(déplacer les tâches DONE vers un fichier ou une liste séparée)*  
- Tâches récurrentes  
  *(répétition quotidienne / hebdomadaire)*  
- Mode Aujourd’hui  
  *(afficher uniquement les tâches dont la date limite est aujourd’hui)*

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

```include/ ```: Contient les fichiers d'en-tête (.h).

```CMakeLists.txt``` : Configuration du projet pour CMake.

```data/``` : Répertoire de stockage pour les fichiers de sauvegarde.

## Contribution
Les contributions sont les bienvenues ! N'hésitez pas à ouvrir une issue ou à soumettre une pull request pour améliorer ce gestionnaire de tâches.
