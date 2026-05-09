#ifndef MOTIVATIONMANAGER_H
#define MOTIVATIONMANAGER_H

#include <vector>
#include <string>

class MotivationManager {

private:
    std::vector<std::string> quotes;

public:

    MotivationManager();

    std::string getRandomQuote();

    std::string getQuoteByMood(const std::string& mood);
};

#endif