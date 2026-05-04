#include "../include/LanguageManager.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

LanguageManager langManager;

void LanguageManager::load(const std::string& file) {
    std::ifstream f(file);
    if (!f.is_open()) {
        std::cout << "Error loading dictionary!" << std::endl;
        return;
    }

    json j;
    f >> j;

    texts.clear();

    for (auto& [key, value] : j.items()) {
        texts[key]["en"] = value["en"];
        texts[key]["fr"] = value["fr"];
    }
}

void LanguageManager::setLanguage(const std::string& lang) {
    currentLang = lang;
}

std::string LanguageManager::t(const std::string& key) {
    if (texts.count(key) && texts[key].count(currentLang))
        return texts[key][currentLang];
    return "[" + key + "]";
}