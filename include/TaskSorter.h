#pragma once
#include "Task.h"
#include <vector>

class TaskSorter {
public:
    static void sortByPriority(std::vector<Task*>& tasks);
    static void sortByDeadline(std::vector<Task*>& tasks);
};
