# Gestionnaire de Tâches (Application Console en C++)

Une application de gestion de tâches en ligne de commande développée en C++. Elle permet de créer, organiser, filtrer et suivre des tâches avec support multilingue (anglais/français).

---

## Fonctionnalités

### Gestion des tâches

* Ajouter des tâches **professionnelles** et **personnelles**
* Ajouter des tâches **récurrentes** (quotidiennes / hebdomadaires / mensuelles)
* Définir une **date limite**, une **priorité** et un **statut**
* Supprimer ou archiver des tâches

###  Organisation

* Trier les tâches par :

  * Priorité
  * Date limite
* Filtrer les tâches par :

  * Statut
  * Priorité
  * Tâches en retard
  * Tâches du jour

###  Statistiques

* Affichage du nombre total de tâches
* Statistiques générales des tâches

###  Notifications

* Vérification des tâches en retard ou proches de leur échéance

###  Sauvegarde

* Sauvegarde des tâches dans un fichier via `FileManager`

###  Multilingue

* Anglais 🇬🇧
* Français 🇫🇷

---

## Structure du projet

Le projet suit une architecture classique avec séparation entre les fichiers d’en-tête (.h) et les fichiers d’implémentation (.cpp).

```
include/
 ├── TaskManager.h
 ├── Task.h
 ├── RecurringTask.h
 ├── FileManager.h
 ├── TaskFilter.h
 ├── TaskSorter.h
 ├── TaskStats.h
 ├── TodayView.h
 ├── NotificationManager.h
 ├── LanguageManager.h


src/
 ├── TaskManager.cpp
 ├── Task.cpp
 ├── RecurringTask.cpp
 ├── FileManager.cpp
 ├── TaskFilter.cpp
 ├── TaskSorter.cpp
 ├── TaskStats.cpp
 ├── TodayView.cpp
 ├── NotificationManager.cpp
 ├── LanguageManager.cpp
 └── main.cpp

data/
 └── dictionary.json
```

Chaque fichier `.cpp` dans `src/` correspond à un fichier `.h` dans `include/`, ce qui permet une séparation claire entre interface et implémentation.

---

##  Compilation

### Prérequis

* C++17 ou plus
* g++ ou clang++
* Bibliothèque `nlohmann/json`

### Compilation simple

```bash
 g++ src/main.cpp -o taskmanager
```

### Compilation multi-fichiers

```bash
 g++ src/*.cpp -o taskmanager
```

---

##  Exécution

```bash
./taskmanager
```

---

##  Menu principal

```
1  - Afficher les tâches
2  - Ajouter une tâche professionnelle
3  - Ajouter une tâche personnelle
4  - Ajouter une tâche récurrente
5  - Supprimer une tâche
6  - Archiver une tâche
7  - Trier par priorité
8  - Trier par date limite
9  - Filtrer par statut
10 - Filtrer par priorité
11 - Tâches en retard
12 - Vue du jour
13 - Statistiques
14 - Notifications
15 - Sauvegarder dans un fichier
0  - Quitter
```

---

##  Système de langue

Au démarrage, l’utilisateur choisit la langue :

```
1. Anglais
2. Français
```

Les traductions sont chargées depuis :

```
data/dictionary.json
```

---

##  Dépendances

* [nlohmann/json](https://github.com/nlohmann/json)

Installation (Ubuntu) :

```bash
sudo apt install nlohmann-json3-dev

