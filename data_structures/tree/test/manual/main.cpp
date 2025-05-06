#include <filesystem>
#include <iostream>

#include "logger.hpp"

int main() {
    Logger::Init(LoggerOutput::ConsoleAndFile);
    auto logger = Logger::GetLogger();
    logger->info("Tests manual run");
    return 0;
}