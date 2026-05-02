#include <iostream>
#include <limits>
#include <string>
#include "../include/TaskManager.h"
#include "../include/Task.h"
#include "../include/RecurringTask.h"
#include "../include/FileManager.h"
#include "../include/TaskFilter.h"
#include "../include/TaskSorter.h"
#include "../include/TaskStats.h"
#include "../include/TodayView.h"
#include "../include/NotificationManager.h"
 
void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
 
void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}
 
void printMenu() {
    std::cout << "\n╔══════════════════════════════════════╗" << std::endl;
    std::cout << "║         TODO LIST MANAGER            ║" << std::endl;
    std::cout << "╠══════════════════════════════════════╣" << std::endl;
    std::cout << "║  1.  Display all tasks               ║" << std::endl;
    std::cout << "║  2.  Add WorkTask                    ║" << std::endl;
    std::cout << "║  3.  Add PersonalTask                ║" << std::endl;
    std::cout << "║  4.  Add RecurringTask               ║" << std::endl;
    std::cout << "║  5.  Remove task                     ║" << std::endl;
    std::cout << "║  6.  Archive task                    ║" << std::endl;
    std::cout << "╠══════════════════════════════════════╣" << std::endl;
    std::cout << "║  7.  Show urgency levels             ║" << std::endl;
    std::cout << "║  8.  Sort by priority                ║" << std::endl;
    std::cout << "║  9.  Sort by deadline                ║" << std::endl;
    std::cout << "╠══════════════════════════════════════╣" << std::endl;
    std::cout << "║  10. Filter by status                ║" << std::endl;
    std::cout << "║  11. Filter by priority              ║" << std::endl;
    std::cout << "║  12. Show overdue tasks              ║" << std::endl;
    std::cout << "║  13. Today's view                    ║" << std::endl;
    std::cout << "╠══════════════════════════════════════╣" << std::endl;
    std::cout << "║  14. Show stats                      ║" << std::endl;
    std::cout << "║  15. Check deadline notifications    ║" << std::endl;
    std::cout << "║  16. Display archive                 ║" << std::endl;
    std::cout << "║  17. Save tasks to file              ║" << std::endl;
    std::cout << "╠══════════════════════════════════════╣" << std::endl;
    std::cout << "║  0.  Exit                            ║" << std::endl;
    std::cout << "╚══════════════════════════════════════╝" << std::endl;
    std::cout << "Choice: ";
}
 
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
 
void getTaskInfo(std::string& title, std::string& desc) {
    std::cout << "Title: ";       std::getline(std::cin, title);
    std::cout << "Description: "; std::getline(std::cin, desc);
}
 
void displayList(const std::vector<Task*>& list) {
    if (list.empty()) { std::cout << "No tasks found." << std::endl; return; }
    for (int i = 0; i < (int)list.size(); ++i) {
        std::cout << "[" << i << "] ";
        list[i]->display();
    }
}
 
int main() {
    TaskManager manager;
 
    manager.addTask(new WorkTask("Finish C++ project", "Complete all classes and test",
                                  Priority::HIGH, Status::IN_PROGRESS));
    manager.addTask(new WorkTask("Prepare presentation", "Slides and demo video",
                                  Priority::MEDIUM, Status::TODO));
    manager.addTask(new PersonalTask("Buy groceries", "Milk, bread, eggs",
                                     Priority::LOW, Status::TODO));
    manager.addTask(new PersonalTask("Clean room", "Vacuum and dust",
                                     Priority::MEDIUM, Status::DONE));
    manager.addTask(new RecurringTask("Daily standup", "Team meeting",
                                      Priority::HIGH, Status::TODO,
                                      Recurrence::DAILY));
 
    // setDeadline yqbel Deadline* — 3la hssab Task.h dyalek
    manager.getTasks()[0]->setDeadline(new Deadline(5, 5, 2025));
 
    int choice;
    do {
        printMenu();
        std::cin >> choice; clearInput();
 
        switch (choice) {
 
        case 1:
            std::cout << "\n=== All Tasks ===" << std::endl;
            manager.displayTasks();
            pause();
            break;
 
        case 2: case 3: {
            std::string title, desc;
            getTaskInfo(title, desc);
            Priority p = choosePriority();
            Status   s = chooseStatus();
            if (choice == 2)
                manager.addTask(new WorkTask(title, desc, p, s));
            else
                manager.addTask(new PersonalTask(title, desc, p, s));
            std::cout << "Task added!" << std::endl;
            pause();
            break;
        }
 
        case 4: {
            std::string title, desc;
            getTaskInfo(title, desc);
            Priority p = choosePriority();
            Status   s = chooseStatus();
            std::cout << "Recurrence (1=DAILY, 2=WEEKLY, 3=MONTHLY): ";
            int r; std::cin >> r; clearInput();
            Recurrence rec = (r == 1) ? Recurrence::DAILY :
                             (r == 2) ? Recurrence::WEEKLY : Recurrence::MONTHLY;
            manager.addTask(new RecurringTask(title, desc, p, s, rec));
            std::cout << "Recurring task added!" << std::endl;
            pause();
            break;
        }
 
        case 5:
            std::cout << "\n=== All Tasks ===" << std::endl;
            manager.displayTasks();
            if (!manager.getTasks().empty()) {
                std::cout << "Index to remove: ";
                int idx; std::cin >> idx; clearInput();
                manager.removeTask(idx);
                std::cout << "Task removed!" << std::endl;
            }
            pause();
            break;
 
        case 6:
            std::cout << "\n=== All Tasks ===" << std::endl;
            manager.displayTasks();
            if (!manager.getTasks().empty()) {
                std::cout << "Index to archive: ";
                int idx; std::cin >> idx; clearInput();
                manager.archiveTask(idx);
            }
            pause();
            break;
 
        case 7:
            std::cout << "\n=== Urgency Levels ===" << std::endl;
            for (Task* t : manager.getTasks())
                std::cout << t->getTitle()
                          << " -> " << t->computeUrgency() << std::endl;
            pause();
            break;
 
        case 8:
            TaskSorter::sortByPriority(manager.getTasks());
            std::cout << "Sorted by priority." << std::endl;
            manager.displayTasks();
            pause();
            break;
 
        case 9:
            TaskSorter::sortByDeadline(manager.getTasks());
            std::cout << "Sorted by deadline." << std::endl;
            manager.displayTasks();
            pause();
            break;
 
        case 10: {
            Status s = chooseStatus();
            auto filtered = TaskFilter::byStatus(manager.getTasks(), s);
            std::cout << "\n=== Filtered by Status ===" << std::endl;
            displayList(filtered);
            pause();
            break;
        }
 
        case 11: {
            Priority p = choosePriority();
            auto filtered = TaskFilter::byPriority(manager.getTasks(), p);
            std::cout << "\n=== Filtered by Priority ===" << std::endl;
            displayList(filtered);
            pause();
            break;
        }
 
        case 12: {
            auto od = TaskFilter::overdue(manager.getTasks());
            std::cout << "\n=== Overdue Tasks ===" << std::endl;
            displayList(od);
            pause();
            break;
        }
 
        case 13: {
            auto today = TodayView::getTodayTasks(manager.getTasks());
            std::cout << "\n=== Today's Tasks ===" << std::endl;
            displayList(today);
            pause();
            break;
        }
 
        case 14:
            std::cout << "\n=== Stats ===" << std::endl;
            std::cout << "Total:     " << TaskStats::totalTasks(manager.getTasks())     << std::endl;
            std::cout << "Completed: " << TaskStats::completedTasks(manager.getTasks()) << std::endl;
            std::cout << "Overdue:   " << TaskStats::overdueTasks(manager.getTasks())   << std::endl;
            pause();
            break;
 
        case 15:
            std::cout << "\n=== Deadline Notifications ===" << std::endl;
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
            std::cout << "Goodbye!" << std::endl;
            break;
 
        default:
            std::cout << "Invalid choice." << std::endl;
        }
 
    } while (choice != 0);
 
    return 0;
}/ /   s r c   f i l e s   a d d e d  
 