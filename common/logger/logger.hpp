// logger.hpp
#pragma once
#include <spdlog/spdlog.h>

#include <memory>
#include <string>
enum class LoggerOutput { ConsoleOnly, FileOnly, ConsoleAndFile };

class Logger {
   public:
    static void Init(
        LoggerOutput output_type = LoggerOutput::ConsoleAndFile,
        const std::string& filename = "logs/app.logs",
        spdlog::level::level_enum level = spdlog::level::debug,
        const std::string& pattern = "[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");

    // logging
    static void Info(const std::string& message);
    static void Warn(const std::string& message);
    static void Error(const std::string& message);
    static void Debug(const std::string& message);

    static void SetPattern(const std::string& pattern);
    static void SetLevel(spdlog::level::level_enum level);
    static std::shared_ptr<spdlog::logger> GetLogger();

   private:
    static std::shared_ptr<spdlog::logger> logger_;
};