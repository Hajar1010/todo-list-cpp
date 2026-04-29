#pragma once
#include "Task.h"
#include <vector>

class TodayView {
public:
    static std::vector<Task*> getTodayTasks(const std::vector<Task*>& tasks);
};
