#include "../include/Task.h"
#include "../include/LanguageManager.h"
#include <iostream>

extern LanguageManager langManager;
#define T(x) langManager.t(x)

// constructor
Task::Task(std::string t, std::string d, Priority p, Status s) {
    title = t;
    description = d;
    priority = p;
    status = s;
    deadline = nullptr;
}

// display task
void Task::display() const {
    std::cout << T("title") << ": " << title << "\n";
    std::cout << T("description") << ": " << description << "\n";

    std::cout << T("priority") << ": ";
    if (priority == Priority::LOW)
        std::cout << T("low");
    else if (priority == Priority::MEDIUM)
        std::cout << T("medium");
    else
        std::cout << T("high");
    std::cout << "\n";

    std::cout << T("status") << ": ";
    if (status == Status::TODO)
        std::cout << T("todo");
    else if (status == Status::IN_PROGRESS)
        std::cout << T("in_progress");
    else
        std::cout << T("done");
    std::cout << "\n";

    if (deadline) {
        std::cout << T("deadline") << ": "
                  << deadline->toString()
                  << " (" << deadline->daysLeft()
                  << " " << T("days_left") << ")\n";
    }

    std::cout << T("urgency") << ": " << computeUrgency() << "\n";
}

// getters
std::string Task::getTitle() const {
    return title;
}

Priority Task::getPriority() const {
    return priority;
}

Status Task::getStatus() const {
    return status;
}

Deadline* Task::getDeadline() const {
    return deadline;
}

// setter
void Task::setDeadline(Deadline* d) {
    delete deadline;
    deadline = d;
}

// overdue check
bool Task::isOverdue() const {
    return deadline && deadline->daysLeft() < 0 && status != Status::DONE;
}

// operator overload
std::ostream& operator<<(std::ostream& os, const Task& task) {
    task.display();
    return os;
}
std::string Task::getDescription() const {
    return description;
}

void Task::setStatus(Status s) {
    status = s;
}