#pragma once
#include "Task.h"

class WorkTask : public Task {
public:
    WorkTask(
        const std::string& title,
        const std::string& description,
        Priority priority,
        Status status
    );

    void display() const override;
};
