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
    int c;
    do {
        std::cout << T("priority_prompt");
        std::cin >> c;
        clearInput();
        if (c < 1 || c > 3)
            std::cout << T("invalid_choice_123") << "\n";
    } while (c < 1 || c > 3);

    if (c == 3) return Priority::HIGH;
    if (c == 2) return Priority::MEDIUM;
    return Priority::LOW;
}

Status chooseStatus() {
    int c;
    do {
        std::cout << T("status_prompt");
        std::cin >> c;
        clearInput();
        if (c < 1 || c > 3)
            std::cout << T("invalid_choice_123") << "\n";
    } while (c < 1 || c > 3);

    if (c == 3) return Status::DONE;
    if (c == 2) return Status::IN_PROGRESS;
    return Status::TODO;
}

// ---------------- DEADLINE INPUT ----------------
Deadline* inputDeadline() {
    char c;
    std::cout << T("deadline_prompt");
    std::cin >> c;
    clearInput();

    if (c != 'y' && c != 'Y' && c != 'o' && c != 'O') return nullptr;

    int day, month, year;

    do {
        std::cout << T("deadline_day");
        std::cin >> day;
        clearInput();
        if (day < 1 || day > 31)
            std::cout << T("invalid_day") << "\n";
    } while (day < 1 || day > 31);

    do {
        std::cout << T("deadline_month");
        std::cin >> month;
        clearInput();
        if (month < 1 || month > 12)
            std::cout << T("invalid_month") << "\n";
    } while (month < 1 || month > 12);

    do {
        std::cout << T("deadline_year");
        std::cin >> year;
        clearInput();
        if (year < 2000 || year > 2100)
            std::cout << T("invalid_year") << "\n";
    } while (year < 2000 || year > 2100);

    return new Deadline(day, month, year);
}

void getTaskInfo(std::string& title, std::string& desc, Deadline*& d) {
    std::cin.ignore(10000, '\n');

    std::cout << T("title_prompt");
    std::getline(std::cin, title);

    std::cout << T("desc_prompt");
    std::getline(std::cin, desc);

    d = inputDeadline();
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

// ---------------- REMOVE/ARCHIVE HELPER ----------------
// mode: 0 = remove, 1 = archive
void removeOrArchive(TaskManager& manager, int mode) {
    // Copie locale pour eviter les problemes de reference
    std::vector<Task*> tasks = manager.getTasks();
    if (tasks.empty()) {
        std::cout << T("no_tasks") << "\n";
        return;
    }

    // Afficher la liste avec index commencant a 1
    for (int i = 0; i < (int)tasks.size(); i++) {
        std::cout << "[" << (i + 1) << "] " << tasks[i]->getTitle() << "\n";
    }

    std::cout << T(mode == 0 ? "title_or_index_remove" : "title_or_index_archive") << ": ";

    std::string input;
    std::getline(std::cin, input);

    bool found = false;

    // Verifier si c'est un nombre pur
    bool isNumber = !input.empty();
    for (char ch : input) {
        if (!std::isdigit(ch)) { isNumber = false; break; }
    }

    if (isNumber) {
        // --- par numero de Task (commence a 1) ---
        int idx = std::stoi(input) - 1;
        if (idx >= 0 && idx < (int)tasks.size()) {
            if (mode == 0) manager.removeTask(idx);
            else           manager.archiveTask(idx);
            std::cout << T(mode == 0 ? "removed" : "archived") << "\n";
            found = true;
        }
    } else {
        // --- par titre ---
        const std::vector<Task*>& realTasks = manager.getTasks();
        for (int i = 0; i < (int)realTasks.size(); i++) {
            if (realTasks[i]->getTitle() == input) {
                if (mode == 0) manager.removeTask(i);
                else           manager.archiveTask(i);
                std::cout << T(mode == 0 ? "removed" : "archived") << "\n";
                found = true;
                break;
            }
        }
    }

    if (!found) std::cout << T("task_not_found") << "\n";
}

// ---------------- MENU ----------------
void printMenu() {
    std::cout << "\n========== " << T("menu_title") << " ==========\n";

    std::cout << "1. "  << T("display_tasks")  << "\n";
    std::cout << "2. "  << T("add_work")        << "\n";
    std::cout << "3. "  << T("add_personal")    << "\n";
    std::cout << "4. "  << T("add_recurring")   << "\n";

    std::cout << "5. "  << T("remove_task")     << "\n";
    std::cout << "6. "  << T("archive_task")    << "\n";

    std::cout << "7. "  << T("sort_priority")   << "\n";
    std::cout << "8. "  << T("sort_deadline")   << "\n";
    std::cout << "9. "  << T("filter_status")   << "\n";
    std::cout << "10. " << T("filter_priority") << "\n";
    std::cout << "11. " << T("overdue_tasks")   << "\n";
    std::cout << "12. " << T("today_view")      << "\n";

    std::cout << "13. " << T("stats")           << "\n";
    std::cout << "14. " << T("notifications")   << "\n";
    std::cout << "15. " << T("save_file")       << "\n";

    std::cout << "0. "  << T("exit")            << "\n";

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

            int r;
            do {
                std::cout << T("recurrence_prompt");
                std::cin >> r;
                clearInput();
                if (r < 1 || r > 3)
                    std::cout << T("invalid_choice_123") << "\n";
            } while (r < 1 || r > 3);

            Recurrence rec;
            switch (r) {
                case 1: rec = Recurrence::DAILY;   break;
                case 2: rec = Recurrence::WEEKLY;  break;
                case 3: rec = Recurrence::MONTHLY; break;
                default: rec = Recurrence::DAILY;  break;
            }

            Task* t = new RecurringTask(title, desc, p, s, rec);
            t->setDeadline(d);
            manager.addTask(t);

            std::cout << T("rec_added") << "\n";
            pause();
            break;
        }

        // -------- REMOVE: titre OU index --------
        case 5:
            removeOrArchive(manager, 0);
            pause();
            break;

        // -------- ARCHIVE: titre OU index --------
        case 6:
            removeOrArchive(manager, 1);
            pause();
            break;

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