#pragma once
#include "Task.h"
#include <vector>

class TaskStats {
public:
    static int totalTasks(const std::vector<Task*>& tasks);
    static int completedTasks(const std::vector<Task*>& tasks);
    static int overdueTasks(const std::vector<Task*>& tasks);
};
