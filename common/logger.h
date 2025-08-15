#pragma once

#include <memory>
#include <string_view>

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
    spdlog::logger& operator()() const;
private:
    static CncLogger Instance;

    static void Register(const std::string name);

    const std::string Name;
};
