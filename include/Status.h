// This file defines the STATUS of a task.
//
// A task can be:
// - TODO (not started)
// - IN_PROGRESS (currently working on it)
// - DONE (finished)
//
// This helps track progress of tasks.

#pragma once

enum class Status {
    TODO,
    IN_PROGRESS,
    DONE
};

