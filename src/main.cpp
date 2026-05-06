#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <cctype>

#include "../include/ProductivityAnalytics.h"
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

// ================= HELPERS =================
void clearInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void pause() {
    std::cout << T("press_enter");
    std::cin.get();
}

// ================= PRIORITY / STATUS =================
Priority choosePriority() {
    int c;
    do {
        std::cout << T("priority_prompt");
        std::cin >> c;
        clearInput();
    } while (c < 1 || c > 3);

    return (c == 3) ? Priority::HIGH :
           (c == 2) ? Priority::MEDIUM :
                      Priority::LOW;
}

Status chooseStatus() {
    int c;
    do {
        std::cout << T("status_prompt");
        std::cin >> c;
        clearInput();
    } while (c < 1 || c > 3);

    return (c == 3) ? Status::DONE :
           (c == 2) ? Status::IN_PROGRESS :
                      Status::TODO;
}

// ================= DEADLINE =================
Deadline* inputDeadline() {
    char c;
    std::cout << T("deadline_prompt");
    std::cin >> c;
    clearInput();

    if (c != 'y' && c != 'Y'  && c != 'O' && c != 'o') return nullptr;

    int d, m, y;
    std::cout << T("deadline_day"); std::cin >> d;
    std::cout << T("deadline_month"); std::cin >> m;
    std::cout << T("deadline_year"); std::cin >> y;
    clearInput();

    return new Deadline(d, m, y);
}

// ================= INPUT TASK =================
void getTaskInfo(std::string& title, std::string& desc, Deadline*& d) {
    std::cout << T("title_prompt");
    std::getline(std::cin, title);

    std::cout << T("desc_prompt");
    std::getline(std::cin, desc);

    d = inputDeadline();
}

// ================= DISPLAY =================
void displayList(const std::vector<Task*>& list) {
    if (list.empty()) {
        std::cout << T("no_tasks") << "\n";
        return;
    }

    for (int i = 0; i < (int)list.size(); i++) {
        std::cout << i << "\n";
        list[i]->display();
        std::cout << "-----------------\n";
    }
}

// ================= REMOVE / ARCHIVE =================
void removeOrArchive(TaskManager& manager, int mode) {
    auto& tasks = manager.getTasks();

    if (tasks.empty()) {
        std::cout << T("no_tasks") << "\n";
        return;
    }

    for (int i = 0; i < (int)tasks.size(); i++) {
        std::cout << "[" << i + 1 << "] " << tasks[i]->getTitle() << "\n";
    }

    clearInput();

    std::string input;
    std::cout << T(mode == 0 ? "title_or_index_remove" : "title_or_index_archive") << ": ";
    std::getline(std::cin, input);

    bool isNumber = !input.empty();
    for (char c : input)
        if (!std::isdigit((unsigned char)c)) isNumber = false;

    if (isNumber) {
        int idx = std::stoi(input) - 1;

        if (idx >= 0 && idx < (int)tasks.size()) {
            if (mode == 0) manager.removeTask(idx);
            else manager.archiveTask(idx);
        }
    } else {
        for (int i = 0; i < (int)tasks.size(); i++) {
            if (tasks[i]->getTitle() == input) {
                if (mode == 0) manager.removeTask(i);
                else manager.archiveTask(i);
                break;
            }
        }
    }
}

// ================= MENU =================
void printMenu() {
    std::cout << "\n========== " << T("menu_title") << " ==========\n";

    std::cout << "1. " << T("display_tasks") << "\n";
    std::cout << "2. " << T("add_work") << "\n";
    std::cout << "3. " << T("add_personal") << "\n";
    std::cout << "4. " << T("add_recurring") << "\n";

    std::cout << "5. " << T("remove_task") << "\n";
    std::cout << "6. " << T("archive_task") << "\n";
    std::cout << "7. " << T("view_archive") << "\n";

    std::cout << "8. " << T("productivity_analytics") << "\n";

    std::cout << "9. " << T("sort_priority") << "\n";
    std::cout << "10. " << T("sort_deadline") << "\n";
    std::cout << "11. " << T("filter_status") << "\n";
    std::cout << "12. " << T("filter_priority") << "\n";
    std::cout << "13. " << T("overdue_tasks") << "\n";
    std::cout << "14. " << T("today_view") << "\n";

    std::cout << "15. " << T("stats") << "\n";
    std::cout << "16. " << T("notifications") << "\n";   
    std::cout << "17. " << T("mark_status") << "\n";   

    std::cout << "0. " << T("exit") << "\n";
    std::cout << "\n==========================\n";
    std::cout << T("choice") << ": ";
}

// ================= MAIN =================
int main() {
    TaskManager manager;

    langManager.load("data/dictionary.json");

    int langChoice;
    std::cout << "1. English\n2. French\nChoice: ";
    std::cin >> langChoice;
    clearInput();

    langManager.setLanguage(langChoice == 2 ? "fr" : "en");

    // LOAD EXISTING TASKS
    std::vector<Task*> savedTasks = FileManager::load();

    for (Task* t : savedTasks) {
        manager.addTask(t);
    }
    std::vector<Task*> archivedTasks = FileManager::loadArchive();

    for (Task* t : archivedTasks) {
        manager.getArchive().addToArchive(t);
    }

    
    Task* lastDeletedTask = nullptr;
    int lastDeletedIndex = -1;

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

            std::cout << T("task_added") <<"\n";
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
            std::cout << T("recurrence_prompt");
            std::cin >> r;
            clearInput();

            Recurrence rec =
                (r == 1) ? Recurrence::DAILY :
                (r == 2) ? Recurrence::WEEKLY :
                           Recurrence::MONTHLY;

            Task* t = new RecurringTask(title, desc, p, s, rec);
            t->setDeadline(d);
            manager.addTask(t);

            pause();
            break;
        }

        case 5: {
            auto& tasks = manager.getTasks();

            if (tasks.empty()) {
            std::cout << T("no_tasks") << "\n";
            pause();
            break;
            }

            // show tasks (1-based)
            for (int i = 0; i < (int)tasks.size(); i++) {
             std::cout << "[" << (i + 1) << "] " << tasks[i]->getTitle() << "\n";       }

            std::cin.ignore(10000, '\n');

            std::string input;
            std::cout << T("index_title_to_delete: ");
            std::getline(std::cin, input);

            bool found = false;

            bool isNumber = !input.empty();
            for (char c : input) {
            if (!std::isdigit((unsigned char)c)) {
                isNumber = false;
                break;  }}
            Task* tempTask = nullptr;
            int tempIndex = -1;

             // ---------------- DELETE BY INDEX ----------------
             if (isNumber) {
                 int index = std::stoi(input);
                index = index - 1;

                if (index >= 0 && index < (int)tasks.size()) {
                    tempTask = manager.removeTask(index);
                    tempIndex = index;
                    found = true;
                }
            }

            // ---------------- DELETE BY TITLE ----------------
            else {
                for (int i = 0; i < (int)tasks.size(); i++) {
                     if (tasks[i]->getTitle() == input) {
                        tempTask = manager.removeTask(i);
                        tempIndex = i;

                        found = true;
                        break;
                    }
                }
            }

            // ---------------- RESULT ----------------
            if (!found) {
                 std::cout << T("task_not_found") << "\n";
                pause();
                break;
            }

            std::cout << T("task_deleted") << "\n";

            // store for undo
            lastDeletedTask = tempTask;
            lastDeletedIndex = tempIndex;

            // ---------------- UNDO PROMPT ----------------
            char choice;
            std::cout << T("undo_prompt");
             std::cin >> choice;
            clearInput();

            if (choice == 'y' || choice == 'Y' || choice == 'o' || choice == 'O') {
                 manager.restoreTask(lastDeletedTask, lastDeletedIndex);
                std::cout << T("undo_success") << "\n";

                lastDeletedTask = nullptr;
                lastDeletedIndex = -1;
            }
            else {
                // permanently discard undo reference
                 lastDeletedTask = nullptr;
                lastDeletedIndex = -1;
            }

            pause();
            break;
             }
        case 6:
            removeOrArchive(manager, 1);
            pause();
            break;

        case 7:
             manager.getArchive().displayArchive();
            pause();
            break;

        case 8:
            ProductivityAnalytics::showAnalytics(manager.getTasks());
            pause();
            break;

        case 9:
            TaskSorter::sortByPriority(manager.getTasks());
            manager.displayTasks();
            pause();
            break;

        case 10:
            TaskSorter::sortByDeadline(manager.getTasks());
            manager.displayTasks();
            pause();
            break;

        case 11: {
            Status s = chooseStatus();
            displayList(TaskFilter::byStatus(manager.getTasks(), s));
            pause();
            break;
        }

        case 12: {
            Priority p = choosePriority();
            displayList(TaskFilter::byPriority(manager.getTasks(), p));
            pause();
            break;
        }

        case 13:
            displayList(TaskFilter::overdue(manager.getTasks()));
            pause();
            break;

        case 14:
            displayList(TodayView::getTodayTasks(manager.getTasks()));
            pause();
            break;

        case 15:
           TaskStats::showDetailedStats(
            manager.getTasks(),
            manager.getArchive().getArchivedTasks().size()
);
            pause();
            break;

        case 16:
            NotificationManager::checkDeadlines(manager.getTasks());
            pause();
            break;

        case 17: {
            auto& tasks = manager.getTasks();

            if (tasks.empty()) {
                std::cout <<  T("no_tasks")<< "\n";
                break;
            }

            for (int i = 0; i < (int)tasks.size(); i++) {
                std::cout << "[" << i + 1 << "] " << tasks[i]->getTitle() << "\n";
            }

            int index;
            std::cout << T("select_number");
            std::cin >> index;
            clearInput();

             if (index < 1 || index > (int)tasks.size()) break;

                    Status s = chooseStatus();

                    tasks[index - 1]->setStatus(s);

                    std::cout << T("status_updated")<< "\n";
             pause();
            break;
        }
        case 0:
            FileManager::save(manager.getTasks());
            FileManager::saveArchive(
            manager.getArchive().getArchivedTasks()
        );
        std::cout << T("exit_message") << "\n";
        break;

    }} while (choice != 0);

    return 0;
}