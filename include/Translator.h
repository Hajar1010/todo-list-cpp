#pragma once
#include <string>
#include <map>
#include <nlohmann/json.hpp>

class Translator {
private:
    std::map<std::string, std::map<std::string, std::string>> dict;
    std::string currentLang;

public:
    void load(const std::string& file);
    void setLanguage(const std::string& lang);
    std::string t(const std::string& key);
};