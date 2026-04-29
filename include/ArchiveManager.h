#pragma once
#include "Task.h"
#include <vector>

class ArchiveManager {
private:
    std::vector<Task*> archivedTasks;

public:
    void archiveTask(Task* task);
    void displayArchive() const;
    const std::vector<Task*>& getArchivedTasks() const;
}
