#include "../include/TodayView.h"

std::vector<Task*> TodayView::getTodayTasks(const std::vector<Task*>& tasks) {
    std::vector<Task*> result;

    for (Task* t : tasks) {

        // skip completed tasks
        if (t->getStatus() == Status::DONE)
            continue;

        // must have a deadline
        if (!t->getDeadline())
            continue;

        // ONLY tasks due today
        if (t->getDeadline()->daysLeft() == 0) {
            result.push_back(t);
        }
    }

    return result;
}