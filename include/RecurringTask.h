#pragma once
#include "Task.h"

enum class Recurrence {
    DAILY,
    WEEKLY,
    MONTHLY
};

class RecurringTask : public Task {
private:
    Recurrence recurrence;

public:
    RecurringTask(std::string title, std::string desc,
                  Priority p, Status s,
                  Recurrence r);

Recurrence getRecurrence() const;
    void regenerate();
    int computeUrgency() const override;
    std::string getType() const override;
    void display() const override;
};