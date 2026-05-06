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

    for (int i = 0; i < tasks.size(); i++) {
        std::cout << "--- Task " << (i + 1) << " ---" << std::endl;
        tasks[i]->display();
    }
}

Task* TaskManager::removeTask(int index) {
    if (index >= 0 && index < (int)tasks.size()) {
        Task* removed = tasks[index];
        tasks.erase(tasks.begin() + index);
        return removed;
    }
    return nullptr;
}

void TaskManager::archiveTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        archive.archiveTask(tasks[index]);
        tasks.erase(tasks.begin() + index);
    } 
    else {
        std::cout << T("task_not_found") << std::endl;
    }
}

std::vector<Task*>& TaskManager::getTasks() {
    return tasks;
}

ArchiveManager& TaskManager::getArchive() {
    return archive;
}

void TaskManager::restoreTask(Task* task, int index) {
    if (!task) return;

    if (index >= 0 && index <= tasks.size()) {
        tasks.insert(tasks.begin() + index, task);
    } 
    else {
        tasks.push_back(task);
    }
}