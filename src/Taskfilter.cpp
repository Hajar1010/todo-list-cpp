#include "../include/TaskFilter.h"

std::vector<Task*> TaskFilter::byStatus(const std::vector<Task*>& tasks, Status s) {
    std::vector<Task*> result;
    for (Task* t : tasks)
        if (t->getStatus() == s) result.push_back(t);
    return result;
}

std::vector<Task*> TaskFilter::byPriority(const std::vector<Task*>& tasks, Priority p) {
    std::vector<Task*> result;
    for (Task* t : tasks)
        if (t->getPriority() == p) result.push_back(t);
    return result;
}

std::vector<Task*> TaskFilter::overdue(const std::vector<Task*>& tasks) {
    std::vector<Task*> result;
    for (Task* t : tasks)
        if (t->getDeadline() && t->getDeadline()->daysLeft() < 0
            && t->getStatus() != Status::DONE)
            result.push_back(t);
    return result;
}