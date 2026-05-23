# Gestionnaire de Tâches (Application Console en C++)

Une application de gestion de tâches en ligne de commande développée en **C++** en utilisant les principes de la **programmation orientée objet (POO)**.

Cette application permet de créer, organiser, filtrer et suivre des tâches avec gestion des priorités, deadlines, statistiques, notifications et support multilingue (**français / anglais**).

---

# Fonctionnalités

## Gestion des tâches
- Ajouter des tâches professionnelles
- Ajouter des tâches personnelles
- Ajouter des tâches récurrentes (quotidiennes / hebdomadaires / mensuelles)
- Définir une priorité
- Définir un statut
- Ajouter une deadline
- Supprimer une tâche
- Archiver une tâche
- Consulter les tâches archivées

---

## Organisation des tâches
- Trier par priorité
- Trier par date limite
- Filtrer par statut
- Filtrer par priorité
- Afficher les tâches en retard
- Afficher les tâches du jour

---

## Analyse & Statistiques
- Productivité analytique
- Statistiques détaillées
- Nombre total de tâches

---

## Notifications
- Vérification des deadlines proches
- Détection des tâches en retard

---

## Sauvegarde des données
Les données sont sauvegardées dans :

- `tasks.json`
- `archive.json`
- `dictionary.json`

Utilisation de :contentReference[oaicite:0]{index=0}

---
## Suivi d’humeur & Motivation
- Enregistrement de l’humeur quotidienne
- Historique des humeurs
- Génération de citations motivationnelles selon l’humeur de l’utilisateur
---
# Structure du projet

```bash
todo-list-cpp/
│
├── include/
│   ├── ArchiveManager.h
│   ├── Deadline.h
│   ├── FileManager.h
│   ├── LanguageManager.h
│   ├── MoodTracker.h
│   ├── MotivationManager.h
│   ├── NotificationManager.h
│   ├── PersonalTask.h
│   ├── Priority.h
│   ├── ProductivityAnalytics.h
│   ├── RecurringTask.h
│   ├── Status.h
│   ├── Task.h
│   ├── TaskFilter.h
│   ├── TaskManager.h
│   ├── TaskSorter.h
│   ├── TaskStats.h
│   ├── TodayView.h
│   ├── Translator.h
│   └── WorkTask.h

├── src/
│   ├── ArchiveManager.cpp
│   ├── Deadline.cpp
│   ├── FileManager.cpp
│   ├── LanguageManager.cpp
│   ├── MoodTracker.cpp
│   ├── MotivationManager.cpp
│   ├── NotificationManager.cpp
│   ├── PersonalTask.cpp
│   ├── ProductivityAnalytics.cpp
│   ├── RecurringTask.cpp
│   ├── Task.cpp
│   ├── TaskFilter.cpp
│   ├── TaskManager.cpp
│   ├── TaskSorter.cpp
│   ├── TaskStats.cpp
│   ├── TodayView.cpp
│   ├── Translator.cpp
│   ├── WorkTask.cpp
│   └── main.cpp
data/
├── archive.json
├── dictionary.json
├── tasks.json
└── mood_history.txt
│
├── docs/
│   ├── Rapport_TaskManager.pdf
│
├── README.md
└── Makefile
```

---

# Compilation

### Prérequis
- C++17 ou version supérieure
- g++
- Bibliothèque :contentReference[oaicite:1]{index=1}

---

### Compiler le projet

```bash
g++ src/*.cpp -o taskmanager
```

Ou avec Makefile :

```bash
make
```

---

# Exécution

```bash
./taskmanager
```

---

# Menu principal

```plaintext
1. Afficher les tâches
2. Ajouter une tâche professionnelle
3. Ajouter une tâche personnelle
4. Ajouter une tâche récurrente
5. Supprimer une tâche
6. Archiver une tâche
7. Voir les archives
8. Productivité Analytics
9. Trier par priorité
10. Trier par deadline
11. Filtrer par statut
12. Filtrer par priorité
13. Tâches en retard
14. Vue du jour
15. Statistiques
16. Notifications
17. Marquer le statut d'une tâche
18. Historique d'humeur
0. Quitter
```

---

# Système multilingue

Au lancement :

```plaintext
1. English
2. Français
```

Les traductions sont chargées depuis :

```plaintext
data/dictionary.json
```

---

# Concepts POO utilisés

- Héritage (`Task → WorkTask / PersonalTask / RecurringTask`)
- Polymorphisme
- Encapsulation
- Modularité

---

# Technologies utilisées

- C++
- STL (`vector`, `map`, `algorithm`)
- JSON
- Gestion de fichiers
- Interface console

---

# Auteur

- **Hajar1010**
- **RomaSd4120**
- **faragimarwa-stack**


Projet académique réalisé en C++.

---
