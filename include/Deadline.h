#pragma once
#include <string>
#include <ctime>

class Deadline {
private:
    std::tm date;

public:
    Deadline(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    std::string toString() const;
    int daysLeft() const;
};
