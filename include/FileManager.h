
#pragma once
#include <vector>
#include "Task.h"



class FileManager {
public:
    static void save(const std::vector<Task*>& tasks);
    static void saveArchive(const std::vector<Task*>& archivedTasks);
    static std::vector<Task*> load();
    static std::vector<Task*> loadArchive();
};
