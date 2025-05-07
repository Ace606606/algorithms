// ParserEnv.cpp
#include "ParserEnv.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "logger.hpp"

static inline void trim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int ch) { return !std::isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
}

std::string ParserEnv::to_string_status(ParserStatus status) const {
    switch (status) {
        case ParserStatus::OK:
            return "OK";
        case ParserStatus::FILE_OPEN_ERROR:
            return "FILE_OPEN_ERROR";
        case ParserStatus::INVALID_KEY:
            return "INVALID_KEY";
        default:
            return "UNKNOWN_STATUS";
    }
}

ParserEnv::ParserEnv(const std::string& path_to_env)
    : path_to_env_(path_to_env) {
    static bool logger_initialized = []() {
        if (!Logger::GetLogger()) {
            Logger::Init();
            Logger::Debug("Default logger initialized");
            return true;
        }
        return false;
    }();
}
ParserEnv::~ParserEnv() {}

ParserStatus ParserEnv::read_env_file(char token) {
    std::ifstream file(path_to_env_);

    if (!file.is_open()) {
        Logger::Error("File opening error: " + path_to_env_);
        return ParserStatus::FILE_OPEN_ERROR;
    }

    Logger::Debug("Parsing .env file: " + path_to_env_);
    std::string line, key, value;

    for (int idx{}; std::getline(file, line); ++idx) {
        trim(line);

        if (line.empty() || line[0] == '#' || line[0] == ';') {
            Logger::Debug("Skipping line empty/comment: #" +
                          std::to_string(idx + 1));
            continue;
        }

        std::istringstream ss(line);
        std::getline(ss, key, token);
        std::getline(ss, value, token);
        trim(key);
        trim(value);

        if (key.empty()) {
            Logger::Error("Empty key at line: " + std::to_string(idx + 1));
            return ParserStatus::INVALID_KEY;
        }

        auto it = std::find_if(
            env_vars_.begin(), env_vars_.end(),
            [&key](const auto& item) { return item.first == key; });

        if (it != env_vars_.end()) {
            Logger::Warn("Dublicate key [" + key + "] found overwriting...");
            *it = {key, value};
        } else {
            env_vars_.push_back({key, value});
            Logger::Debug("Added env var: " + key + "=" + value);
        }
    }

    return ParserStatus::OK;
}

std::vector<std::pair<std::string, std::string>> ParserEnv::get_env_vars()
    const {
    return env_vars_;
}