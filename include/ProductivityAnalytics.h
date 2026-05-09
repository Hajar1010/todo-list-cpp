#ifndef PRODUCTIVITY_ANALYTICS_H
#define PRODUCTIVITY_ANALYTICS_H

#include <vector>
#include "Task.h"

class ProductivityAnalytics {
public:
    static void showAnalytics(const std::vector<Task*>& tasks);
};

#endif