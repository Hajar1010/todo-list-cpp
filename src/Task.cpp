#include "../include/Task.h"
#include <iostream>

Task::Task(std::string t, std::string d, Priority p, Status s) {
    title = t;
    description = d;
    priority = p;
    status = s;
    deadline = nullptr;
}

void Task::display() const {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Description: " << description << std::endl;

    std::cout << "Priority: ";
    if (priority == Priority::LOW)         std::cout << "Low";
    else if (priority == Priority::MEDIUM) std::cout << "Medium";
    else                                   std::cout << "High";
    std::cout << std::endl;

    std::cout << "Status: ";
    if (status == Status::TODO)             std::cout << "Todo";
    else if (status == Status::IN_PROGRESS) std::cout << "In Progress";
    else                                    std::cout << "Done";
    std::cout << std::endl;

    if (deadline)
        std::cout << "Deadline: " << deadline->toString()
                  << " (" << deadline->daysLeft() << " days left)" << std::endl;

    std::cout << "Urgency: " << computeUrgency() << std::endl;
}

std::string Task::getTitle()       const { return title; }
Priority    Task::getPriority()    const { return priority; }
Status      Task::getStatus()      const { return status; }
Deadline*   Task::getDeadline()    const { return deadline; }

void Task::setDeadline(Deadline* d) {
    delete deadline;
    deadline = d;
}

bool Task::isOverdue() const {
    return deadline && deadline->daysLeft() < 0 && status != Status::DONE;
}

std::ostream& operator<<(std::ostream& os, const Task& task) {
    task.display();
    return os;
}