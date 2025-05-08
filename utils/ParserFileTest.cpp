// ParserFileTest.cpp
#include "ParserFileTest.hpp"

#include <exception>
#include <filesystem>
#include <string>

#include "log_macros.hpp"
#include "logger.hpp"

Parser_file::Parser_file(const std::string& path_to_file)
    : path_to_file_(path_to_file) {
    static bool logger_initialized = []() {
        if (!Logger::GetLogger()) {
            Logger::Init();
            LOG_DEBUG("Default logger initialized");
            return true;
        }
        return false;
    }();

    if (!std::filesystem::exists(path_to_file_) ||
        std::filesystem::is_regular_file(path_to_file_)) {
        LOG_ERROR("File not found or file not regular file: " + path_to_file_);
        throw std::runtime_error("File not found or file not regular file");
    }
}

Parser_file::~Parser_file() {
    if (checkerOpenFile()) file_.close();
}

std::string Parser_file::getPath() const { return path_to_file_; }
void Parser_file::setPath(const std::string& path_to_file) {
    path_to_file_ = path_to_file;
}

bool Parser_file::checkerIsFile() const {
    return std::filesystem::exists(path_to_file_) &&
           std::filesystem::is_regular_file(path_to_file_);
}
bool Parser_file::checkerOpenFile() const { return file_.is_open(); }

// std::ifstream& Parser_file::openFile() {
//     if (!checkerIsFile())

//     if (checkerOpenFile()) file_.close();

//     std::ifstream file(path_to_file_);

//     if ()
//}