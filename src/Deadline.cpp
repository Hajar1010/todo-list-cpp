#include "../include/Deadline.h"
#include <cstdio>
#include <ctime>

Deadline::Deadline(int day, int month, int year) {
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