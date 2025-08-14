#pragma once

#include <string_view>

/**
 * @brief Logger class using spdlog. For memory and thread safety, only assign instances
 *        of this class using static storage specifiers; use a static member or variable.
 */
class CncLogger
{
public:
    static const std::string_view DefaultLoggerName;
    static const CncLogger DefaultLogger;

    CncLogger(const std::string_view name);

    void Log_Info(const std::string_view message) const;
    void Log_Warn(const std::string_view message) const;
    void Log_Error(const std::string_view message) const;
    void Log_Debug(const std::string_view message) const;
    void Log_Trace(const std::string_view message) const;
private:
    static CncLogger Instance;

    static void Register(const std::string_view name);

    const std::string_view Name;
};
