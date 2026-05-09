#include "../include/Deadline.h"
#include <cstdio>
#include <ctime>
#include <stdexcept>

Deadline::Deadline(int day, int month, int year) {
    if (year < 2026 || year > 2200)
        throw std::invalid_argument("Year must be between 2026 and 2200");

    if (month < 1 || month > 12)
        throw std::invalid_argument("Month must be between 1 and 12");

    int maxDay = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11)
        maxDay = 30;
    else if (month == 2) {
        bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        maxDay = leap ? 29 : 28;
    }

    if (day < 1 || day > maxDay)
        throw std::invalid_argument("Invalid day for given month/year");

    date = {};
    date.tm_mday = day;
    date.tm_mon  = month - 1;
    date.tm_year = year - 1900;
    mktime(&date);
}

int Deadline::getDay()   const { return date.tm_mday; }
int Deadline::getMonth() const { return date.tm_mon + 1; }
int Deadline::getYear()  const { return date.tm_year + 1900; }

std::string Deadline::toString() const {
    char buf[20];
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d",
             date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);
    return std::string(buf);
}

int Deadline::daysLeft() const {
    std::time_t now  = std::time(nullptr);
    std::tm target   = date;
    std::time_t t    = mktime(&target);
    double diff      = difftime(t, now);
    return static_cast<int>(diff / 86400);
}