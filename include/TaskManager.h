
#pragma once
#include <vector>
#include "Task.h"
#include "ArchiveManager.h"

class TaskManager {
private:
    std::vector<Task*> tasks;
    ArchiveManager archive;

public:
    void addTask(Task* task);
    void displayTasks() const;
    void removeTask(int index);
    void archiveTask(int index);
    std::vector<Task*>& getTasks();
    ArchiveManager& getArchive();

};


