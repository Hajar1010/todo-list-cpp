#include "../include/RecurringTask.h"
#include <iostream>

std::string recurrenceStr(Recurrence r) {
    switch (r) {
        case Recurrence::DAILY:   return "DAILY";
        case Recurrence::WEEKLY:  return "WEEKLY";
        case Recurrence::MONTHLY: return "MONTHLY";
    }
    return "?";
}

RecurringTask::RecurringTask(std::string title, std::string desc,
                             Priority p, Status s, Recurrence r)
    : Task(title, desc, p, s), recurrence(r) {}

Recurrence RecurringTask::getRecurrence() const {
    return recurrence;
}

void RecurringTask::regenerate() {
    status = Status::TODO;
    std::cout << "[Recurring] Task reset: " << title << std::endl;
}

int RecurringTask::computeUrgency() const {
    int base  = (priority == Priority::HIGH)   ? 9 :
                (priority == Priority::MEDIUM) ? 5 : 2;
    int bonus = (recurrence == Recurrence::DAILY)  ? 2 :
                (recurrence == Recurrence::WEEKLY) ? 1 : 0;
    return base + bonus;
}

std::string RecurringTask::getType() const {
    return "RECURRING(" + recurrenceStr(recurrence) + ")";
}

void RecurringTask::display() const {
    Task::display();
    std::cout << "   Recurrence: " << recurrenceStr(recurrence) << std::endl;
}