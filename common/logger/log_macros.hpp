// log_macros.hpp
#pragma once

#include "logger.hpp"

#ifdef ENABLE_DEBUG_LOGS
#define LOG_DEBUG(msg) Logger::Debug(msg)
#else
#define LOG_DEBUG(msg) (void)0
#endif

#define LOG_INFO(msg) Logger::Info(msg)
#define LOG_WARN(msg) Logger::Warn(msg)
#define LOG_ERROR(msg) Logger::Error(msg)
#define LOG_CRITICAL(msg) Logger::Error(msg)