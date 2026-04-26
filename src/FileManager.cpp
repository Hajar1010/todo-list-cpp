#include "FileManager.h"
#include <fstream>
#include <iostream>

void FileManager::save(const std::vector<Task*>& tasks) {
    std::ofstream file("tasks.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }
    for (Task* task : tasks) {
        file << task->getTitle() << std::endl;
        file << (int)task->getPriority() << std::endl;
        file << (int)task->getStatus() << std::endl;
        file << "---" << std::endl;
    }
    file.close();
    std::cout << "Tasks saved successfully!" << std::endl;
}