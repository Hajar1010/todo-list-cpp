// This is the MAIN class of the project.
//
// A Task represents one thing the user wants to do.
//
// It contains:
// - title (name of task)
// - description
// - priority
// - status
//
// It also defines important functions:
// - display() → show task info
// - computeUrgency() → calculate how urgent it is (IMPORTANT for polymorphism)
//
// This class is ABSTRACT because computeUrgency() is not implemented here.
// Other classes will inherit from it.

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
