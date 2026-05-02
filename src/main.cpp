#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <map>

#include "../include/TaskManager.h"
#include "../include/Task.h"
#include "../include/RecurringTask.h"
#include "../include/FileManager.h"
#include "../include/TaskFilter.h"
#include "../include/TaskSorter.h"
#include "../include/TaskStats.h"
#include "../include/TodayView.h"
#include "../include/NotificationManager.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ---------------- LANGUAGE MANAGER ----------------
class LanguageManager {
private:
    std::map<std::string, std::map<std::string, std::string>> texts;
    std::string currentLang = "fr";

public:
    void load(const std::string& file) {
        std::ifstream f(file);

        if (!f.is_open()) {
            std::cout << "Error loading dictionary!" << std::endl;
            return;
        }

        json j;
        f >> j;

        texts.clear();

        for (auto& [key, value] : j.items()) {
            texts[key]["fr"] = value["fr"];
            texts[key]["ar"] = value["ar"];
        }
    }

    void setLanguage(const std::string& lang) {
        currentLang = lang;
    }

    std::string t(const std::string& key) {
        if (texts.count(key) && texts[key].count(currentLang))
            return texts[key][currentLang];

        return "[" + key + "]";
    }
};

LanguageManager langManager;

// ---------------- INPUT SAFE ----------------
void clearInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

// ---------------- MENU ----------------
void printMenu() {
    std::cout << "\n**************************************\n";
    std::cout << "*      " << langManager.t("menu") << "      *\n";
    std::cout << "**************************************\n";

    std::cout << "* 1.  " << langManager.t("display_tasks") << "\n";
    std::cout << "* 2.  " << langManager.t("add_work") << "\n";
    std::cout << "* 3.  " << langManager.t("add_personal") << "\n";
    std::cout << "* 4.  " << langManager.t("add_recurring") << "\n";
    std::cout << "* 5.  " << langManager.t("remove_task") << "\n";
    std::cout << "* 6.  " << langManager.t("archive_task") << "\n";

    std::cout << "**************************************\n";
    std::cout << "* 0.  " << langManager.t("exit") << "\n";
    std::cout << "**************************************\n";

    std::cout << langManager.t("choice") << " ";
}

// ---------------- HELPERS ----------------
Priority choosePriority() {
    std::cout << "Priority (1=LOW, 2=MEDIUM, 3=HIGH): ";
    int c;

    if (!(std::cin >> c)) {
        clearInput();
        return Priority::LOW;
    }
    clearInput();

    if (c == 3) return Priority::HIGH;
    if (c == 2) return Priority::MEDIUM;
    return Priority::LOW;
}

Status chooseStatus() {
    std::cout << "Status (1=TODO, 2=IN_PROGRESS, 3=DONE): ";
    int c;

    if (!(std::cin >> c)) {
        clearInput();
        return Status::TODO;
    }
    clearInput();

    if (c == 3) return Status::DONE;
    if (c == 2) return Status::IN_PROGRESS;
    return Status::TODO;
}

void getTaskInfo(std::string& title, std::string& desc, Deadline*& d) {
    std::cin.ignore(10000, '\n');

    std::cout << "Title: ";
    std::getline(std::cin, title);

    std::cout << "Description: ";
    std::getline(std::cin, desc);

    d = nullptr;
}

// ---------------- MAIN ----------------
int main() {

    TaskManager manager;

    // 🔥 LOAD DICTIONARY (مرة وحدة فقط)
    langManager.load("data/dictionary.json");

    // 🔥 اختيار اللغة
    int langChoice;
    std::cout << "1. Français\n2. العربية\nChoice: ";

    if (!(std::cin >> langChoice)) {
        clearInput();
        langChoice = 1;
    }
    clearInput();

    if (langChoice == 1)
        langManager.setLanguage("fr");
    else
        langManager.setLanguage("ar");

    // ---------------- SAMPLE DATA ----------------
    manager.addTask(new WorkTask("Finish C++ project", "Complete all classes",
                                 Priority::HIGH, Status::IN_PROGRESS));

    manager.addTask(new PersonalTask("Buy groceries", "Milk, bread",
                                     Priority::LOW, Status::TODO));

    manager.getTasks()[0]->setDeadline(new Deadline(5, 5, 2025));

    int choice = -1;

    do {
        printMenu();

        if (!(std::cin >> choice)) {
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {

        case 1:
            std::cout << "\n=== " << langManager.t("all_tasks") << " ===\n";
            manager.displayTasks();
            pause();
            break;

        case 2:
        case 3: {
            std::string title, desc;
            Deadline* d;

            getTaskInfo(title, desc, d);

            Priority p = choosePriority();
            Status s = chooseStatus();

            Task* t;

            if (choice == 2)
                t = new WorkTask(title, desc, p, s);
            else
                t = new PersonalTask(title, desc, p, s);

            t->setDeadline(d);
            manager.addTask(t);

            std::cout << langManager.t("task_added") << std::endl;
            pause();
            break;
        }

        case 0:
            std::cout << langManager.t("exit") << std::endl;
            break;

        default:
            std::cout << langManager.t("invalid") << std::endl;
        }

    } while (choice != 0);

    return 0;
}