#include <spdlog/spdlog.h>

#include "logger.h"

void CncLoggerClass::Log_Info(std::string_view message) {
  spdlog::info(message);
}
