// This file defines the PRIORITY of a task.
//
// Instead of using numbers like 1, 2, 3,
// we use names:
// - LOW
// - MEDIUM
// - HIGH
//
// This makes the code easier to read and safer.
#pragma once
enum class Priority {
    LOW,
    MEDIUM,
    HIGH
};
