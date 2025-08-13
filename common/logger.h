#pragma once

#include <string_view>

static class CncLoggerClass {
public:
  static void Log_Info(std::string_view message);
} CncLogger;
