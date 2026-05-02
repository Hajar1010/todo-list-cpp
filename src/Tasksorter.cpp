#include "../include/TaskSorter.h"
#include <algorithm>

void TaskSorter::sortByPriority(std::vector<Task*>& tasks) {
    std::sort(tasks.begin(), tasks.end(), [](Task* a, Task* b) {
        return static_cast<int>(a->getPriority()) >
               static_cast<int>(b->getPriority());
    });
}

void TaskSorter::sortByDeadline(std::vector<Task*>& tasks) {
    std::sort(tasks.begin(), tasks.end(), [](Task* a, Task* b) {
        if (!a->getDeadline()) return false;
        if (!b->getDeadline()) return true;
        return a->getDeadline()->daysLeft() < b->getDeadline()->daysLeft();
    });
}