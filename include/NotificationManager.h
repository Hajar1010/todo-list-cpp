#pragma once
#include "Task.h"
#include <vector>

class NotificationManager {
public:
    static void checkDeadlines(const std::vector<Task*>& tasks);
};
