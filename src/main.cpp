#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "../include/TaskManager.h"
#include "../include/Task.h"
#include "../include/RecurringTask.h"
#include "../include/FileManager.h"
#include "../include/TaskFilter.h"
#include "../include/TaskSorter.h"
#include "../include/TaskStats.h"
#include "../include/TodayView.h"
#include "../include/NotificationManager.h"
#include "../include/LanguageManager.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;
extern LanguageManager langManager;
#define T(x) langManager.t(x)

// ---------------- HELPERS ----------------
void clearInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void pause() {
    std::cout << T("press_enter");
    std::cin.get();
}

Priority choosePriority() {
    std::cout << T("priority_prompt");
    int c;
    std::cin >> c;
    clearInput();

    if (c == 3) return Priority::HIGH;
    if (c == 2) return Priority::MEDIUM;
    return Priority::LOW;
}

Status chooseStatus() {
    std::cout << T("status_prompt");
    int c;
    std::cin >> c;
    clearInput();

    if (c == 3) return Status::DONE;
    if (c == 2) return Status::IN_PROGRESS;
    return Status::TODO;
}

void getTaskInfo(std::string& title, std::string& desc, Deadline*& d) {
    std::cin.ignore(10000, '\n');

    std::cout << T("title_prompt");
    std::getline(std::cin, title);

    std::cout << T("desc_prompt");
    std::getline(std::cin, desc);

    char c;
    std::cout << T("deadline_prompt");
    std::cin >> c;

    if (c == 'y' || c == 'Y') {
        int day, month, year;
        std::cout << "Day: "; std::cin >> day;
        std::cout << "Month: "; std::cin >> month;
        std::cout << "Year: "; std::cin >> year;
        d = new Deadline(day, month, year);
    } else {
        d = nullptr;
    }

    clearInput();
}

// ---------------- DISPLAY ----------------
void displayList(const std::vector<Task*>& list) {
    if (list.empty()) {
        std::cout << T("no_tasks") << "\n";
        return;
    }

    for (int i = 0; i < (int)list.size(); i++) {
        std::cout << "[" << i << "]\n";
        list[i]->display();
        std::cout << "-----------------\n";
    }
}

// ---------------- MENU ----------------
void printMenu() {
    std::cout << "\n========== " << T("menu_title") << " ==========\n";

    std::cout << "1. " << T("display_tasks") << "\n";
    std::cout << "2. " << T("add_work") << "\n";
    std::cout << "3. " << T("add_personal") << "\n";
    std::cout << "4. " << T("add_recurring") << "\n";

    std::cout << "5. " << T("remove_task") << "\n";
    std::cout << "6. " << T("archive_task") << "\n";

    std::cout << "7. " << T("sort_priority") << "\n";
    std::cout << "8. " << T("sort_deadline") << "\n";
    std::cout << "9. " << T("filter_status") << "\n";
    std::cout << "10. " << T("filter_priority") << "\n";
    std::cout << "11. " << T("overdue_tasks") << "\n";
    std::cout << "12. " << T("today_view") << "\n";

    std::cout << "13. " << T("stats") << "\n";
    std::cout << "14. " << T("notifications") << "\n";
    std::cout << "15. " << T("save_file") << "\n";

    std::cout << "0. " << T("exit") << "\n";

    std::cout << T("choice") << ": ";
}

// ---------------- MAIN ----------------
int main() {
    TaskManager manager;

    langManager.load("data/dictionary.json");

    int langChoice;
    std::cout << "1. English\n2. French\nChoice: ";
    std::cin >> langChoice;
    clearInput();

    langManager.setLanguage(langChoice == 2 ? "fr" : "en");

    int choice;

    do {
        printMenu();

        std::cin >> choice;
        clearInput();

        switch (choice) {

        case 1:
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

            Task* t = (choice == 2)
                ? (Task*)new WorkTask(title, desc, p, s)
                : (Task*)new PersonalTask(title, desc, p, s);

            t->setDeadline(d);
            manager.addTask(t);

            std::cout << T("task_added") << "\n";
            pause();
            break;
        }

        case 4: {
            std::string title, desc;
            Deadline* d;

            getTaskInfo(title, desc, d);

            Priority p = choosePriority();
            Status s = chooseStatus();

            std::cout << T("recurrence_prompt");
            int r;
            std::cin >> r;
            clearInput();

            Recurrence rec;
            switch (r) {
                case 1: rec = Recurrence::DAILY; break;
                case 2: rec = Recurrence::WEEKLY; break;
                case 3: rec = Recurrence::MONTHLY; break;
                default: rec = Recurrence::DAILY; break;
            }

            Task* t = new RecurringTask(title, desc, p, s, rec);
            t->setDeadline(d);

            manager.addTask(t);

            std::cout << T("rec_added") << "\n";
            pause();
            break;
        }

        case 5: {
            int idx;
            std::cout << T("index_remove") << ": ";
            std::cin >> idx;
            clearInput();

            manager.removeTask(idx);
            std::cout << T("removed") << "\n";
            pause();
            break;
        }

        case 6: {
            int idx;
            std::cout << T("index_archive") << ": ";
            std::cin >> idx;
            clearInput();

            manager.archiveTask(idx);
            std::cout << T("archived") << "\n";
            pause();
            break;
        }

        case 7:
            TaskSorter::sortByPriority(manager.getTasks());
            manager.displayTasks();
            pause();
            break;

        case 8:
            TaskSorter::sortByDeadline(manager.getTasks());
            manager.displayTasks();
            pause();
            break;

        case 9: {
            Status s = chooseStatus();
            auto list = TaskFilter::byStatus(manager.getTasks(), s);
            displayList(list);
            pause();
            break;
        }

        case 10: {
            Priority p = choosePriority();
            auto list = TaskFilter::byPriority(manager.getTasks(), p);
            displayList(list);
            pause();
            break;
        }

        case 11: {
            auto list = TaskFilter::overdue(manager.getTasks());
            displayList(list);
            pause();
            break;
        }

        case 12: {
            auto list = TodayView::getTodayTasks(manager.getTasks());
            displayList(list);
            pause();
            break;
        }

        case 13:
            std::cout << "Total: " << TaskStats::totalTasks(manager.getTasks()) << "\n";
            pause();
            break;

        case 14:
            NotificationManager::checkDeadlines(manager.getTasks());
            pause();
            break;

        case 15:
            FileManager::save(manager.getTasks());
            pause();
            break;

        case 0:
            std::cout << T("exit") << "\n";
            break;

        default:
            std::cout << T("invalid") << "\n";
        }

    } while (choice != 0);

    return 0;
}