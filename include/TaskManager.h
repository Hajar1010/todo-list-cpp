
#pragma once
#include <vector>
#include "Task.h"

class TaskManager {
private:
    std::vector<Task*> tasks;

public:
    void addTask(Task* task);
    void displayTasks() const;
    void removeTask(int index);

    std::vector<Task*>& getTasks();

};


