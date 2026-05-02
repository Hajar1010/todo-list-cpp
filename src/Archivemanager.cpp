#include "../include/ArchiveManager.h"
 
ArchiveManager::~ArchiveManager() {
    for (Task* t : archivedTasks) delete t;
}
 
void ArchiveManager::archiveTask(Task* task) {
    archivedTasks.push_back(task);
}
 
void ArchiveManager::displayArchive() const {
    if (archivedTasks.empty()) {
        std::cout << "Archive is empty." << std::endl;
        return;
    }
    std::cout << "=== Archived Tasks ===" << std::endl;
    for (int i = 0; i < (int)archivedTasks.size(); ++i) {
        std::cout << "[" << i << "] ";
        archivedTasks[i]->display();
    }
}
 
const std::vector<Task*>& ArchiveManager::getArchivedTasks() const {
    return archivedTasks;
}