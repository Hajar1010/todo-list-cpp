
#pragma once
#include <vector>
#include "Task.h"

class TaskManager {
private:
    std::vector<Task*> tasks;
    std::vector<Task*> archivedTasks; 

public:
    void addTask(Task* task);
    void displayTasks() const;
    void removeTask(int index);

    std::vector<Task*>& getTasks();

    void archiveDoneTasks();

};


