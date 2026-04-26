// This class manages ALL tasks.
//
// Think of it like the "brain" of the application.
//
// It stores a list (vector) of tasks and allows:
// - adding tasks
// - removing tasks
// - displaying all tasks
//
// It does NOT care about how tasks work internally.
// It just manages them.



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
