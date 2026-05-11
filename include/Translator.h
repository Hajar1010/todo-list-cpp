#pragma once

#include <string>
#include <map>

class Translator {
private:
    std::map<std::string, std::map<std::string, std::string>> dict;
    std::string currentLang = "en";

public:
    void load(const std::string& file);
    void setLanguage(const std::string& lang);
    std::string t(const std::string& key);
};