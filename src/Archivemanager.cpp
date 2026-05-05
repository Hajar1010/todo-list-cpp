#include "../include/ArchiveManager.h"
#include "../include/LanguageManager.h"
#include <iostream>

extern LanguageManager langManager;
#define T(x) langManager.t(x)

ArchiveManager::~ArchiveManager() {
    for (Task* t : archivedTasks) delete t;
}

void ArchiveManager::archiveTask(Task* task) {
    archivedTasks.push_back(task);
}

void ArchiveManager::displayArchive() const {
    if (archivedTasks.empty()) {
        std::cout << T("archive_empty") << std::endl;
        return;
    }
    std::cout << T("archive_title") << std::endl;
    for (int i = 0; i < (int)archivedTasks.size(); ++i) {
        std::cout << "[" << (i + 1) << "] ";
        archivedTasks[i]->display();
    }
}

const std::vector<Task*>& ArchiveManager::getArchivedTasks() const {
    return archivedTasks;
}