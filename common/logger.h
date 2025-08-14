#pragma once

#include <memory>
#include <string_view>

/**
 * @brief Logger class using spdlog. For memory and thread safety, only assign instances
 *        of this class using static storage specifiers; use a static member or variable.
 */
class CncLogger
{
public:
    static const std::string DefaultLoggerName;
    static const CncLogger DefaultLogger;

    CncLogger(const std::string name);

    void Critical(const std::string_view message, ...) const;
    void Error(const std::string_view message, ...) const;
    void Warn(const std::string_view message, ...) const;
    void Info(const std::string_view message, ...) const;
    void Debug(const std::string_view message, ...) const;
    void Trace(const std::string_view message, ...) const;
private:
    static CncLogger Instance;

    static void Register(const std::string name);

    const std::string Name;
};
