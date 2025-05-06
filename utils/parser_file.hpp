//parser_file.hpp
#pragma once
#include <filesystem>
#include <fstream>
#include <string>

class Parser_file {
public:
    explicit Parser_file(const std::string& path_to_file);
    ~Parser_file();

    std::string getPath() const;
    void setPath(const std::string& path_to_file);
    void readAllFile();
    void readLineFile();
private:
    std::string path_to_file_;
    std::ifstream file_;

    std::ifstream& openFile();
    bool checkerOpenFile() const;
    bool checkerIsFile() const;
};