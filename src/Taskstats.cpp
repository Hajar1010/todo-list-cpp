#include "../include/TaskStats.h"
#include "../include/Task.h"
#include "../include/RecurringTask.h"
#include "../include/LanguageManager.h"
#include <iostream>

extern LanguageManager langManager;
#define T(x) langManager.t(x)


int TaskStats::totalTasks(const std::vector<Task*>& tasks) {
    return (int)tasks.size();
}

int TaskStats::completedTasks(const std::vector<Task*>& tasks) {
    int count = 0;
    for (const Task* t : tasks)
        if (t->getStatus() == Status::DONE) count++;
    return count;
}

int TaskStats::overdueTasks(const std::vector<Task*>& tasks) {
    int count = 0;
    for (const Task* t : tasks)
        if (t->getDeadline() && t->getDeadline()->daysLeft() < 0
            && t->getStatus() != Status::DONE) count++;
    return count;
}

void TaskStats::showDetailedStats(
    const std::vector<Task*>& tasks,
    int archivedCount
) {
    int workCount = 0;
    int personalCount = 0;
    int recurringCount = 0;
    int completedCount = 0;

    for (Task* t : tasks) {
        if (t->getStatus() == Status::DONE)
            completedCount++;

        if (dynamic_cast<WorkTask*>(t)) {
            workCount++;
        }
        else if (dynamic_cast<PersonalTask*>(t)) {
            personalCount++;
        }
        else if (dynamic_cast<RecurringTask*>(t)) {
            recurringCount++;
        }
    }

    int activeCount = tasks.size();
    int totalAll = activeCount + archivedCount;

    std::cout << "\n===== " << T("stats_title") << " =====\n\n";

    std::cout << T("total_all") << ": " << totalAll << "\n";
    std::cout << T("active_tasks") << ": " << activeCount << "\n";
    std::cout << T("archived_tasks") << ": " << archivedCount << "\n\n";

    std::cout << T("work_tasks") << ": " << workCount << "\n";
    std::cout << T("personal_tasks") << ": " << personalCount << "\n";
    std::cout << T("recurring_tasks") << ": " << recurringCount << "\n\n";

    std::cout << T("completed_tasks") << ": " << completedCount << "\n";
}