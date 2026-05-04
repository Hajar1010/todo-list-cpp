#pragma once
#include <string>
#include <map>

class LanguageManager {
private:
    std::map<std::string, std::map<std::string, std::string>> texts;
    std::string currentLang = "en";

public:
    void load(const std::string& file);
    void setLanguage(const std::string& lang);
    std::string t(const std::string& key);
};

extern LanguageManager langManager;