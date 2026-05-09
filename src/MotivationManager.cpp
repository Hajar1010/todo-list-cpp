#include "MotivationManager.h"
#include "../include/LanguageManager.h"
#include <cstdlib>
#include <ctime>

extern LanguageManager langManager;
#define T(x) langManager.t(x)

MotivationManager::MotivationManager() {
    std::srand((unsigned)std::time(nullptr));
}

std::string MotivationManager::getRandomQuote() {
    if (quotes.empty()) return "";
    return quotes[std::rand() % quotes.size()];
}

std::string MotivationManager::getQuoteByMood(const std::string& mood) {
    // Compare against translated mood values
    std::string great = T("mood_great");
    std::string okay  = T("mood_okay");
    std::string tired = T("mood_tired");
    std::string sad   = T("mood_sad");

    if (mood == great)
        return T("quote_great");
    else if (mood == okay)
        return T("quote_okay");
    else if (mood == tired)
        return T("quote_tired");
    else if (mood == sad)
        return T("quote_sad");
    else
        return T("quote_default");
}
