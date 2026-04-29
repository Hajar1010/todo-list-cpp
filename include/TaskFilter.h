#pragma once
#include "Task.h"
#include <vector>

class TaskFilter {
public:
    static std::vector<Task*> byStatus(const std::vector<Task*>& tasks, Status status);
    static std::vector<Task*> byPriority(const std::vector<Task*>& tasks, Priority priority);
    static std::vector<Task*> overdue(const std::vector<Task*>& tasks);
};
