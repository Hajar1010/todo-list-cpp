#include "../include/TodayView.h"

std::vector<Task*> TodayView::getTodayTasks(const std::vector<Task*>& tasks) {
    std::vector<Task*> result;
    for (Task* t : tasks) {
        if (t->getStatus() == Status::DONE) continue;
        if (!t->getDeadline()) {
            if (t->getStatus() == Status::IN_PROGRESS)
                result.push_back(t);
        } else {
            if (t->getDeadline()->daysLeft() <= 1)
                result.push_back(t);
        }
    }
    return result;
}