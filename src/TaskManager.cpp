#include "../include/TaskManager.h"
#include <iostream>

void TaskManager::addTask(Task* task) {
    tasks.push_back(task);
}

void TaskManager::displayTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks found." << std::endl;
        return;
    }
    for (int i = 0; i < (int)tasks.size(); i++) {
        std::cout << "--- Task " << i << " ---" << std::endl;
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
        std::cout << "Task archived." << std::endl;
    } else {
        std::cout << "Invalid index." << std::endl;
    }
}

std::vector<Task*>& TaskManager::getTasks() {
    return tasks;
}

ArchiveManager& TaskManager::getArchive() {
    return archive;
}