#include "../include/FileManager.h"
#include "../include/Task.h"
#include "../include/RecurringTask.h"
#include "../include/LanguageManager.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

extern LanguageManager langManager;
#define T(x) langManager.t(x)

using json = nlohmann::json;

// ================= SAVE =================
void FileManager::save(const std::vector<Task*>& tasks) {
    json j = json::array();

    for (Task* task : tasks) {
        if (!task) continue;

        j.push_back({
            {"title", task->getTitle()},
            {"description", task->getDescription()},
            {"priority", (int)task->getPriority()},
            {"status", (int)task->getStatus()},
            {"type", task->getType()}
        });
    }

    std::ofstream file("./data/tasks.json");

    if (!file.is_open()) {
        std::cout << T("error_opening") << std::endl;
        return;
    }

    file << j.dump(4);
    file.close();

    std::cout << T("tasks_saved") << std::endl;
}

// ================= LOAD =================
std::vector<Task*> FileManager::load() {
    std::vector<Task*> tasks;

    std::ifstream file("data/tasks.json");

    if (!file.is_open()) {
        std::cout << "No save file found. Starting fresh.\n";
        return tasks;
    }

    json j;

    try {
        file >> j;
    } catch (...) {
        std::cout << "Error reading JSON file.\n";
        return tasks;
    }

    if (!j.is_array()) {
        std::cout << "Invalid tasks format.\n";
        return tasks;
    }

    for (auto& item : j) {
        
        std::string title = item.value("title", "");
        std::string desc = item.value("description", "");
        int priority = item.value("priority", 0);
        int status = item.value("status", 0);
        std::string type = item.value("type", "work");

        Task* t = nullptr;

        if (type == "WORK") {
            t = new WorkTask(title, desc, (Priority)priority, (Status)status);
        }
        else if (type == "PERSONAL") {
            t = new PersonalTask(title, desc, (Priority)priority, (Status)status);
        }
        else if (type == "RECURRING") {
            t = new RecurringTask(title, desc,
                                  (Priority)priority,
                                  (Status)status,
                                  Recurrence::DAILY);
        }

        if (t) tasks.push_back(t);
    }

    return tasks;
}

// ================= SAVE ARCHIVE =================
void FileManager::saveArchive(const std::vector<Task*>& archivedTasks) {
    json j = json::array();

    for (Task* task : archivedTasks) {
        if (!task) continue;

        j.push_back({
            {"title", task->getTitle()},
            {"description", task->getDescription()},
            {"priority", (int)task->getPriority()},
            {"status", (int)task->getStatus()},
            {"type", task->getType()}
        });
    }

    std::ofstream file("data/archive.json");

    if (!file.is_open()) {
        std::cout << T("error_opening") << std::endl;
        return;
    }

    file << j.dump(4);
    file.close();

    std::cout << T("archive_saved_successfully")<< "\n";
}

std::vector<Task*> FileManager::loadArchive() {
    std::vector<Task*> archivedTasks;

    std::ifstream file("data/archive.json");

    if (!file.is_open()) {
        return archivedTasks;
    }

    json j;

    try {
        file >> j;
    } catch (...) {
        std::cout << "Error reading archive JSON.\n";
        return archivedTasks;
    }

    for (auto& item : j) {
        std::string title = item.value("title", "");
        std::string desc = item.value("description", "");
        int priority = item.value("priority", 0);
        int status = item.value("status", 0);
        std::string type = item.value("type", "WORK");

        Task* t = nullptr;

        if (type == "WORK") {
            t = new WorkTask(title, desc, (Priority)priority, (Status)status);
        }
        else if (type == "PERSONAL") {
            t = new PersonalTask(title, desc, (Priority)priority, (Status)status);
        }
        else if (type == "RECURRING") {
            t = new RecurringTask(
                title,
                desc,
                (Priority)priority,
                (Status)status,
                Recurrence::DAILY
            );
        }

        if (t) {
            archivedTasks.push_back(t);
        }
    }

    return archivedTasks;
}