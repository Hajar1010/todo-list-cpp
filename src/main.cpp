#include <iostream>
#include "TaskManager.h"
#include "FileManager.h"

int main() {
    TaskManager manager;

    Task* t1 = new WorkTask(
        "Finish C++ project",
        "Complete all classes and test",
        Priority::HIGH,
        Status::IN_PROGRESS
    );

    Task* t2 = new WorkTask(
        "Prepare presentation",
        "Slides and demo video",
        Priority::MEDIUM,
        Status::TODO
    );

    Task* t3 = new PersonalTask(
        "Buy groceries",
        "Milk, bread, eggs",
        Priority::LOW,
        Status::TODO
    );

    Task* t4 = new PersonalTask(
        "Clean room",
        "Vacuum and dust",
        Priority::MEDIUM,
        Status::DONE
    );

    manager.addTask(t1);
    manager.addTask(t2);
    manager.addTask(t3);
    manager.addTask(t4);

    std::cout << "=== All Tasks ===" << std::endl;
    manager.displayTasks();

    std::cout << "\n=== Urgency Levels ===" << std::endl;
    for (Task* task : manager.getTasks()) {
        std::cout << task->getTitle()
                  << " -> Urgency: "
                  << task->computeUrgency()
                  << std::endl;
    }

    std::cout << "\n=== Saving Tasks ===" << std::endl;
    FileManager::save(manager.getTasks());

    std::cout << "\n=== Removing Task 1 ===" << std::endl;
    manager.removeTask(0);
    manager.displayTasks();

    return 0;
}