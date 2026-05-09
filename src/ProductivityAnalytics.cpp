#include "../include/ProductivityAnalytics.h"
#include "../include/LanguageManager.h"
#include <iostream>

extern LanguageManager langManager;
#define T(x) langManager.t(x)


void ProductivityAnalytics::showAnalytics(const std::vector<Task*>& tasks) {
    int total = tasks.size();
    int completed = 0;
    int pending = 0;
    int highPriority = 0;

    for (Task* task : tasks) {
        if (task->getStatus() == Status::DONE)
            completed++;
        else
            pending++;

        if (task->getPriority() == Priority::HIGH)
            highPriority++;
    }

    std::cout << "\n===== " << T("analytics_title") << " =====\n";
    std::cout << T("total_tasks") << ": " << total << std::endl;
    std::cout << T("completed_tasks") << ": " << completed << std::endl;
    std::cout << T("pending_tasks") << ": " << pending << std::endl;
    std::cout << T("high_priority_tasks") << ": " << highPriority << std::endl;

    if (total > 0) {
        double rate = (completed * 100.0) / total;
        std::cout << T("completion_rate") << ": " << rate << "%\n";
    }

    std::cout << "==================================\n";
}