#include "MoodTracker.h"
#include "../include/LanguageManager.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

extern LanguageManager langManager;
#define T(x) langManager.t(x)

void MoodTracker::askMood() {
    int choice;

    cout << "\n========= " << T("mood_title") << " =========\n";
    cout << T("mood_question") << "\n";
    cout << "1. " << T("mood_great") << "\n";
    cout << "2. " << T("mood_okay") << "\n";
    cout << "3. " << T("mood_tired") << "\n";
    cout << "4. " << T("mood_sad") << "\n";
    cout << "\n" << T("choice") << ": ";

    cin >> choice;
    cin.ignore(10000, '\n');

    switch (choice) {
        case 1: currentMood = T("mood_great"); break;
        case 2: currentMood = T("mood_okay");  break;
        case 3: currentMood = T("mood_tired"); break;
        case 4: currentMood = T("mood_sad");   break;
        default: currentMood = T("mood_unknown");
    }

    cout << "\n" << T("mood_saved") << "\n";
    saveMoodToFile();
}

void MoodTracker::showMood() {
    cout << "\n" << T("mood_current") << ": " << currentMood << endl;
}

string MoodTracker::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(1900 + ltm->tm_year) + "-"
         + to_string(1 + ltm->tm_mon) + "-"
         + to_string(ltm->tm_mday);
}

void MoodTracker::saveMoodToFile() {
    // Save to txt
    ofstream fileTxt("data/mood_history.txt", ios::app);
    if (fileTxt.is_open()) {
        fileTxt << getCurrentDate() << " -> " << currentMood << "\n";
        fileTxt.close();
    }

    // Save to JSON archive
    json j = json::array();

    ifstream fileIn("data/mood_archive.json");
    if (fileIn.is_open()) {
        try { fileIn >> j; } catch (...) { j = json::array(); }
        fileIn.close();
    }

    j.push_back({
        {"date", getCurrentDate()},
        {"mood", currentMood}
    });

    ofstream fileOut("data/mood_archive.json");
    if (fileOut.is_open()) {
        fileOut << j.dump(4);
        fileOut.close();
    }
}

void MoodTracker::showMoodHistory() {
    ifstream file("data/mood_history.txt");
    string line;

    cout << "\n========= " << T("mood_history") << " =========\n";

    if (file.is_open()) {
        bool empty = true;
        while (getline(file, line)) {
            cout << line << "\n";
            empty = false;
        }
        if (empty) cout << T("mood_no_history") << "\n";
        file.close();
    } else {
        cout << T("mood_no_history") << "\n";
    }
}

void MoodTracker::showMoodArchive() {
    ifstream file("data/mood_archive.json");

    cout << "\n========= " << T("mood_archive") << " =========\n";

    if (!file.is_open()) {
        cout << T("mood_no_history") << "\n";
        return;
    }

    json j;
    try {
        file >> j;
    } catch (...) {
        cout << T("mood_no_history") << "\n";
        return;
    }

    if (!j.is_array() || j.empty()) {
        cout << T("mood_no_history") << "\n";
        return;
    }

    for (auto& entry : j) {
        string date = entry.value("date", "?");
        string mood = entry.value("mood", "?");
        cout << date << " -> " << mood << "\n";
    }
}

string MoodTracker::getMood() {
    return currentMood;
}
