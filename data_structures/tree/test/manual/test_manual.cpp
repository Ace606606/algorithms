#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>
#include <utility>
#include <vector>

#include "ParserEnv.hpp"
#include "ParserFileTest.hpp"
#include "bst.hpp"
#include "logger.hpp"

struct LoggerConfig {
    LoggerOutput output = LoggerOutput::ConsoleOnly;
    std::string path = "logs/app.logs";
    spdlog::level::level_enum level = spdlog::level::debug;
    std::string pattern = "[%Y-%m-%d %H:%M:%S] [%^%l%$] %v";
};

void parser_env(std::string& path_project_root,
                std::string& path_test_data_bst) {
    std::string env_path = std::filesystem::current_path() / ".env";
    Logger::Debug("Path to .env: " + env_path);

    ParserEnv parser_env(env_path);

    Logger::Debug("Status read_env_file: " +
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

LoggerConfig parse_args(int argc, char* argv[]) {
    LoggerConfig cfg;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.size() <= 2) continue;

        std::string flag = arg.substr(0, 2);
        std::string value = arg.substr(2);

        if (flag == "-o") {
            cfg.output = (value == "cf")  ? LoggerOutput::ConsoleAndFile
                         : (value == "f") ? LoggerOutput::FileOnly
                                          : LoggerOutput::ConsoleOnly;
        } else if (flag == "-f") {
            if (!value.empty()) cfg.path = value;
        } else if (flag == "-l") {
            cfg.level = (value == "info")    ? spdlog::level::info
                        : (value == "warn")  ? spdlog::level::warn
                        : (value == "error") ? spdlog::level::err
                                             : spdlog::level::debug;
        } else if (flag == "-p") {
            if (!value.empty()) cfg.pattern = value;
        }
    }

    return cfg;
}

int main(int argc, char* argv[]) {
    LoggerConfig config = parse_args(argc, argv);
    Logger::Init(config.output, config.path, config.level, config.pattern);

    Logger::Info("Tests manual run");

    std::string path_project_root;
    std::string path_test_data_bst;

    parser_env(path_project_root, path_test_data_bst);

    if (path_test_data_bst.empty()) {
        Logger::Error("Var TEST_DATA_BST not found");
        return 1;
    }

    Logger::Debug("################RUN_TEST################");
    BinarySearchTree<int> bst;

    bst.insert(1);
    bst.insert(2);

    // Node<int> node{1};
    // std::cout << node.getData() << "\n";
    // Parser_file file_test_data(path_test_data_bst);

    return 0;
}