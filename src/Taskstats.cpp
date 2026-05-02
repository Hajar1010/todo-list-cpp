#include "../include/TaskStats.h"

int TaskStats::totalTasks(const std::vector<Task*>& tasks) {
    return (int)tasks.size();
}

int TaskStats::completedTasks(const std::vector<Task*>& tasks) {
    int count = 0;
    for (const Task* t : tasks)
        if (t->getStatus() == Status::DONE) count++;
    return count;
}

int TaskStats::overdueTasks(const std::vector<Task*>& tasks) {
    int count = 0;
    for (const Task* t : tasks)
        if (t->getDeadline() && t->getDeadline()->daysLeft() < 0
            && t->getStatus() != Status::DONE) count++;
    return count;
}