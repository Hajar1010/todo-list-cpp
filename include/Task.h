
#pragma once
#include <string>
#include <iostream>
#include "Priority.h"
#include "Status.h"

class Task {
protected:
    std::string title;
    std::string description;
    Priority priority;
    Status status;

public:
    Task(std::string t, std::string d, Priority p, Status s);

    virtual void display() const;
    virtual int computeUrgency() const = 0;
    std::string getTitle() const;
    Priority getPriority() const;
    Status getStatus() const;

    virtual ~Task() {}

    friend std::ostream& operator<<(std::ostream& os, const Task& task);
};


class WorkTask : public Task {
public:
    WorkTask(std::string t, std::string d, Priority p, Status s)
        : Task(t, d, p, s) {}

    int computeUrgency() const override {
        if (priority == Priority::HIGH)   return 10;
        if (priority == Priority::MEDIUM) return 5;
        return 1;
    }
};

class PersonalTask : public Task {
public:
    PersonalTask(std::string t, std::string d, Priority p, Status s)
        : Task(t, d, p, s) {}

    int computeUrgency() const override {
        if (priority == Priority::HIGH)   return 8;
        if (priority == Priority::MEDIUM) return 4;
        return 2;
    }
};

