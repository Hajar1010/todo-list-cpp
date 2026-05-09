#ifndef MOODTRACKER_H
#define MOODTRACKER_H

#include <string>

class MoodTracker {
private:
    std::string currentMood;

public:
    void askMood();
    void showMood();
    void saveMoodToFile();
    void showMoodHistory();
    void showMoodArchive();
    std::string getCurrentDate();
    std::string getMood();
};

#endif
