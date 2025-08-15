#pragma once

#include <memory>
#include <string_view>

/**
 * spdlog static configuration
 */

// pull in function call info for current compiler
#if defined(__GNUC__) || defined(__clang__)
  #define SPDLOG_FUNCTION static_cast<const char *>(__PRETTY_FUNCTION__)
#elif defined(_MSC_VER)
  #define SPDLOG_FUNCTION static_cast<const char *>(__FUNCSIG__)
#endif

// default to trace whilst initiliasing the program
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>

/**
 * @brief Logger class using spdlog. For memory and thread safety, only assign instances
 *        of this class using static storage specifiers; use a static member or variable.
 */
class CncLogger
{
public:
    static const std::string DefaultLoggerName;
    static const CncLogger Default;

    CncLogger(const std::string name);

    // TODO: Add PII level/log method to require a special flag or runtime arg to force print them (paths containing usernames etc.)
    void Fatal(const std::string_view message) const;
    std::shared_ptr<spdlog::logger> operator()() const;
private:
    static CncLogger Instance;

    static void Register(const std::string name);

    const std::string Name;
};

// alias SPD macros so we don't pollute code with SPD refs
#define CNC_LOG_TRACE(...) \
  SPDLOG_LOGGER_TRACE(CncLogger::Default(), __VA_ARGS__)

#define CNC_LOG_DEBUG(...) \
  SPDLOG_LOGGER_DEBUG(CncLogger::Default(), __VA_ARGS__)

#define CNC_LOG_INFO(...) \
  SPDLOG_LOGGER_INFO(CncLogger::Default(), __VA_ARGS__)

#define CNC_LOG_WARN(...) \
  SPDLOG_LOGGER_WARN(CncLogger::Default(), __VA_ARGS__)

#define CNC_LOG_ERROR(...) \
  SPDLOG_LOGGER_ERROR(CncLogger::Default(), __VA_ARGS__)

#define CNC_LOG_CRITICAL(...) \
  SPDLOG_LOGGER_CRITICAL(CncLogger::Default(), __VA_ARGS__)

#define CNC_LOG_FATAL(...) \
  SPDLOG_LOGGER_CRITICAL(CncLogger::Default(), __VA_ARGS__); \
  exit(1)
