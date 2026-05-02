#include "../include/NotificationManager.h"
#include <iostream>

void NotificationManager::checkDeadlines(const std::vector<Task*>& tasks) {
    bool any = false;
    for (const Task* t : tasks) {
        if (t->getDeadline()) {
            int days = t->getDeadline()->daysLeft();
            if (days <= 3 && t->getStatus() != Status::DONE) {
                std::cout << "[!] URGENT: \"" << t->getTitle()
                          << "\" deadline in " << days << " day(s)!" << std::endl;
                any = true;
            }
        }
    }
    if (!any)
        std::cout << "No urgent deadlines." << std::endl;
}