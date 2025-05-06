#include "parser_file.hpp"

#include <filesystem>
#include <string>

Parser_file::Parser_file(const std::string& path_to_file)
    : path_to_file_(path_to_file) {}
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