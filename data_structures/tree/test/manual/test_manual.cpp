#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>
#include <utility>
#include <vector>

#include "ParserEnv.hpp"
#include "ParserFileTest.hpp"
#include "logger.hpp"

void parser_env(std::string& path_project_root,
                std::string& path_test_data_bst) {
    std::string env_path = std::filesystem::current_path() / ".env";
    Logger::Debug("Path to .env: " + env_path);

    ParserEnv parser_env(env_path);

    Logger::Debug("Status: " +
                  parser_env.to_string_status(parser_env.read_env_file()));
    std::vector<std::pair<std::string, std::string>> env_vars =
        parser_env.get_env_vars();

    Logger::Debug("Current env_vars:");

    for (const auto& obj : env_vars) {
        Logger::Debug(obj.first + "=" + obj.second);
        if (!obj.first.compare("PROJECT_ROOT")) path_project_root = obj.second;
        if (!obj.first.compare("TEST_DATA_BST"))
            path_test_data_bst = obj.second;
    }
}

int main(int argc, char* argv[]) {
    Logger::Init(LoggerOutput::ConsoleOnly);
    Logger::Info("Tests manual run");

    std::string path_project_root;
    std::string path_test_data_bst;

    parser_env(path_project_root, path_test_data_bst);

    if (path_test_data_bst.empty()) {
        Logger::Error("Var TEST_DATA_BST not found");
        return 1;
    }

    // Parser_file file_test_data(path_test_data_bst);

    return 0;
}