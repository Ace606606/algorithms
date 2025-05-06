// logger.cpp

#include "logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
std::shared_ptr<spdlog::logger> Logger::logger_ = nullptr;

void Logger::Init(LoggerOutput output_type, const std::string& filename,
                  spdlog::level::level_enum level, const std::string& pattern) {
    if (logger_) return;

    std::vector<spdlog::sink_ptr> sinks;

    if (output_type == LoggerOutput::ConsoleOnly ||
        output_type == LoggerOutput::ConsoleAndFile) {
        sinks.push_back(
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    }

    if (output_type == LoggerOutput::FileOnly ||
        output_type == LoggerOutput::ConsoleAndFile) {
        try {
            sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                filename, false));
        } catch (const spdlog::spdlog_ex& ex) {
            std::cerr << "Failed to create file sinc: " << ex.what() << '\n';
        }
    }

    logger_ = std::make_shared<spdlog::logger>("main_logger", sinks.begin(),
                                               sinks.end());
    spdlog::set_default_logger(logger_);
    SetLevel(level);
    SetPattern(pattern);
    logger_->flush_on(spdlog::level::warn);
}

void Logger::Info(const std::string& message) {
    if (logger_)
        logger_->info(message);
    else
        std::cerr << "Logger not initialized" << '\n';
}
void Logger::Warn(const std::string& message) {
    if (logger_)
        logger_->warn(message);
    else
        std::cerr << "Logger not initialized" << '\n';
}
void Logger::Error(const std::string& message) {
    if (logger_)
        logger_->error(message);
    else
        std::cerr << "Logger not initialized" << '\n';
}
void Logger::Debug(const std::string& message) {
    if (logger_)
        logger_->debug(message);
    else
        std::cerr << "Logger not initialized" << '\n';
}

void Logger::SetLevel(spdlog::level::level_enum level) {
    if (logger_) logger_->set_level(level);
}
void Logger::SetPattern(const std::string& pattern) {
    if (logger_) logger_->set_pattern(pattern);
}
std::shared_ptr<spdlog::logger> Logger::GetLogger() { return logger_; }