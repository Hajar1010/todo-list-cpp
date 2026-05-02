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

#include "json.hpp"

using json = nlohmann::json;

// ---------------- LANGUAGE MANAGER ----------------

class LanguageManager {
private:
    std::map<std::string, std::string> texts;

public:
    void load(const std::string& lang) {
        std::ifstream file("lang/" + lang + ".json");
        json j;
        file >> j;

        texts.clear();
        for (auto& [key, value] : j.items()) {
            texts[key] = value;
        }
    }

    std::string t(const std::string& key) {
        return texts[key];
    }
};

LanguageManager langManager;

// ---------------- UTIL ----------------

void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

// ---------------- MENU ----------------

void printMenu() {
    std::cout << "\n**************************************\n";
    std::cout << "*        " << langManager.t("menu") << "           *\n";
    std::cout << "**************************************\n";

    std::cout << "*  1.  Display all tasks             *\n";
    std::cout << "*  2.  Add WorkTask                  *\n";
    std::cout << "*  3.  Add PersonalTask              *\n";
    std::cout << "*  4.  Add RecurringTask             *\n";
    std::cout << "*  5.  Remove task                   *\n";
    std::cout << "*  6.  Archive task                  *\n";

    std::cout << "**************************************\n";

    std::cout << "*  7.  Show urgency levels           *\n";
    std::cout << "*  8.  Sort by priority              *\n";
    std::cout << "*  9.  Sort by deadline              *\n";

    std::cout << "**************************************\n";

    std::cout << "* 10.  Filter by status              *\n";
    std::cout << "* 11.  Filter by priority            *\n";
    std::cout << "* 12.  Show overdue tasks            *\n";
    std::cout << "* 13.  Today's view                  *\n";

    std::cout << "**************************************\n";

    std::cout << "* 14.  Show stats                    *\n";
    std::cout << "* 15.  Check deadline notifications  *\n";
    std::cout << "* 16.  Display archive               *\n";
    std::cout << "* 17.  Save tasks to file            *\n";

    std::cout << "**************************************\n";
    std::cout << "*  0.  " << langManager.t("exit") << "                          *\n";
    std::cout << "**************************************\n";

    std::cout << "Choice: ";
}

// ---------------- INPUT HELPERS ----------------

Priority choosePriority() {
    std::cout << "Priority (1=LOW, 2=MEDIUM, 3=HIGH): ";
    int c; std::cin >> c; clearInput();
    if (c == 3) return Priority::HIGH;
    if (c == 2) return Priority::MEDIUM;
    return Priority::LOW;
}

Status chooseStatus() {
    std::cout << "Status (1=TODO, 2=IN_PROGRESS, 3=DONE): ";
    int c; std::cin >> c; clearInput();
    if (c == 3) return Status::DONE;
    if (c == 2) return Status::IN_PROGRESS;
    return Status::TODO;
}

void getTaskInfo(std::string& title, std::string& desc, Deadline*& d) {
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Description: ";
    std::getline(std::cin, desc);
    d = nullptr; // keep your logic (or replace with real deadline input)
}

void displayList(const std::vector<Task*>& list) {
    if (list.empty()) {
        std::cout << "No tasks found." << std::endl;
        return;
    }
    for (int i = 0; i < (int)list.size(); ++i) {
        std::cout << "[" << i << "] ";
        list[i]->display();
    }
}

// ---------------- MAIN ----------------

int main() {
    TaskManager manager;

    // ---------------- LANGUAGE SELECT ----------------
    int langChoice;
    std::cout << "1. Français\n2. English\nChoice: ";
    std::cin >> langChoice;
    clearInput();

    if (langChoice == 1)
        langManager.load("fr");
    else
        langManager.load("en");

    // ---------------- SAMPLE DATA ----------------
    manager.addTask(new WorkTask("Finish C++ project", "Complete all classes", Priority::HIGH, Status::IN_PROGRESS));
    manager.addTask(new PersonalTask("Buy groceries", "Milk, bread", Priority::LOW, Status::TODO));

    manager.getTasks()[0]->setDeadline(new Deadline(5, 5, 2025));

    int choice;

    do {
        printMenu();
        std::cin >> choice;
        clearInput();

        switch (choice) {

        case 1:
            std::cout << "\n=== " << langManager.t("all_tasks") << " ===\n";
            manager.displayTasks();
            pause();
            break;

        case 2: case 3: {
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

        case 4: {
            std::string title, desc;
            Deadline* d;

            getTaskInfo(title, desc, d);
            Priority p = choosePriority();
            Status s = chooseStatus();

            std::cout << "Recurrence (1=DAILY, 2=WEEKLY, 3=MONTHLY): ";
            int r; std::cin >> r; clearInput();

            Recurrence rec = (r == 1) ? Recurrence::DAILY :
                             (r == 2) ? Recurrence::WEEKLY : Recurrence::MONTHLY;

            Task* t = new RecurringTask(title, desc, p, s, rec);
            t->setDeadline(d);

            manager.addTask(t);

            std::cout << langManager.t("rec_added") << std::endl;
            pause();
            break;
        }

        case 5:
            manager.displayTasks();
            if (!manager.getTasks().empty()) {
                std::cout << "Index: ";
                int idx; std::cin >> idx; clearInput();
                manager.removeTask(idx);

                std::cout << langManager.t("task_removed") << std::endl;
            }
            pause();
            break;

        case 6:
            manager.displayTasks();
            if (!manager.getTasks().empty()) {
                std::cout << "Index: ";
                int idx; std::cin >> idx; clearInput();
                manager.archiveTask(idx);
            }
            pause();
            break;

        case 7:
            for (Task* t : manager.getTasks())
                std::cout << t->getTitle() << " -> " << t->computeUrgency() << std::endl;
            pause();
            break;

        case 8:
            TaskSorter::sortByPriority(manager.getTasks());
            manager.displayTasks();
            pause();
            break;

        case 9:
            TaskSorter::sortByDeadline(manager.getTasks());
            manager.displayTasks();
            pause();
            break;

        case 10: {
            Status s = chooseStatus();
            auto f = TaskFilter::byStatus(manager.getTasks(), s);
            displayList(f);
            pause();
            break;
        }

        case 11: {
            Priority p = choosePriority();
            auto f = TaskFilter::byPriority(manager.getTasks(), p);
            displayList(f);
            pause();
            break;
        }

        case 12:
            displayList(TaskFilter::overdue(manager.getTasks()));
            pause();
            break;

        case 13:
            displayList(TodayView::getTodayTasks(manager.getTasks()));
            pause();
            break;

        case 14:
            std::cout << "Total: " << TaskStats::totalTasks(manager.getTasks()) << std::endl;
            std::cout << "Completed: " << TaskStats::completedTasks(manager.getTasks()) << std::endl;
            std::cout << "Overdue: " << TaskStats::overdueTasks(manager.getTasks()) << std::endl;
            pause();
            break;

        case 15:
            NotificationManager::checkDeadlines(manager.getTasks());
            pause();
            break;

        case 16:
            manager.getArchive().displayArchive();
            pause();
            break;

        case 17:
            FileManager::save(manager.getTasks());
            pause();
            break;

        case 0:
            std::cout << langManager.t("exit") << std::endl;
            break;

        default:
            std::cout << "Invalid choice." << std::endl;
        }

    } while (choice != 0);

    return 0;
}
