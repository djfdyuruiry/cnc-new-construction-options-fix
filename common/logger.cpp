#include "spdlog/async.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include "logger.h"

const std::string_view CncLogger::DefaultLoggerName = std::string_view("nco");
const auto CncLogger::DefaultLogger = CncLogger(CncLogger::DefaultLoggerName);

void CncLogger::Register(const std::string_view name) {
  static std::once_flag onceFlag;

  static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> stdout_sink;
  static std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> rotating_sink;
  static std::vector<spdlog::sink_ptr> sinks;

  std::call_once(onceFlag, []() {
    spdlog::init_thread_pool(8192, 1);

    stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("nco.log", 1024*1024*10, 3);
    sinks = std::vector<spdlog::sink_ptr> {stdout_sink, rotating_sink};

    std::string logger_name = std::string(CncLogger::DefaultLoggerName.data());

    spdlog::set_default_logger(
      std::make_shared<spdlog::async_logger>(
        logger_name,
        sinks.begin(),
        sinks.end(),
        spdlog::thread_pool(),
        spdlog::async_overflow_policy::block
      )
    );
  });

  std::string logger_name = std::string(name.data());

  spdlog::register_logger(
    std::make_shared<spdlog::async_logger>(
      logger_name,
      sinks.begin(),
      sinks.end(),
      spdlog::thread_pool(),
      spdlog::async_overflow_policy::block
    )
  );
}

CncLogger::CncLogger(const std::string_view name) : Name(name) {
  if (name != CncLogger::DefaultLoggerName) {
    Register(name);
  }
}

void CncLogger::Log_Info(const std::string_view message) const {
  spdlog::get(Name.data())->info(message);
}
