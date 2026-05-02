#include "../include/Translator.h"
#include <fstream>
#include <nlohmann/json.hpp>
 

using json = nlohmann::json;

void Translator::load(const std::string& file) {
    std::ifstream f(file);
    json j;
    f >> j;

    dict.clear();

    for (auto& [key, value] : j.items()) {
        dict[key] = {
            {"fr", value["fr"].get<std::string>()},
            {"ar", value["ar"].get<std::string>()}
        };
    }
}

void Translator::setLanguage(const std::string& lang) {
    currentLang = lang;
}

std::string Translator::t(const std::string& key) {
    if (dict.count(key) && dict[key].count(currentLang))
        return dict[key][currentLang];

    return key;
}