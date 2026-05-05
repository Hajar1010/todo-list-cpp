#include "../include/TaskManager.h"
#include "../include/LanguageManager.h"
#include <iostream>

extern LanguageManager langManager;
#define T(x) langManager.t(x)

void TaskManager::addTask(Task* task) {
    tasks.push_back(task);
}

void TaskManager::displayTasks() const {
    if (tasks.empty()) {
        std::cout << T("no_tasks") << std::endl;
        return;
    }
    for (int i = 0; i < (int)tasks.size(); i++) {
        std::cout << "--- Task " << (i + 1) << " ---" << std::endl;
        tasks[i]->display();
    }
}

void TaskManager::removeTask(int index) {
    if (index >= 0 && index < (int)tasks.size()) {
        delete tasks[index];
        tasks.erase(tasks.begin() + index);
    }
}

void TaskManager::archiveTask(int index) {
    if (index >= 0 && index < (int)tasks.size()) {
        archive.archiveTask(tasks[index]);
        tasks.erase(tasks.begin() + index);
    } else {
        std::cout << T("task_not_found") << std::endl;
    }
}

std::vector<Task*>& TaskManager::getTasks() {
    return tasks;
}

ArchiveManager& TaskManager::getArchive() {
    return archive;
}