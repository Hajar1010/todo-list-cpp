#pragma once
#include <vector>
#include "Task.h"

class FileManager {
public:
    static void save(const std::vector<Task*>& tasks);
};
