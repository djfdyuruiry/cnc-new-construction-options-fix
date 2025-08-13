#pragma once

#include <string_view>

class CncLogger
{
public:
    static const std::string_view DefaultLoggerName;
    static const CncLogger DefaultLogger;

    CncLogger(const std::string_view name);

    void Log_Info(const std::string_view message) const;

private:
    static CncLogger Instance;

    static void Register(const std::string_view name);

    const std::string_view Name;
};
