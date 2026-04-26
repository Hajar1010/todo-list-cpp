// This class is responsible for saving data.
//
// It will:
// - save tasks into a file (tasks.txt)
// - (later) load tasks from the file
//
// This allows the program to remember tasks
// even after it is closed.

#pragma once
#include <vector>
#include "Task.h"

class FileManager {
public:
    static void save(const std::vector<Task*>& tasks);
};
