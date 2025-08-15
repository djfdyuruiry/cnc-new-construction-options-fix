#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "logger.h"

// static variables
static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> stdout_sink;
static std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> rotating_sink;
static std::vector<spdlog::sink_ptr> sinks;

// static functions
static void Ensure_SpdLog_Initialised() {
    static std::once_flag onceFlag;

    std::call_once(onceFlag, []() {
        spdlog::init_thread_pool(8192, 1);

        stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("nco.log", 1024 * 1024 * 10, 3);
        sinks = std::vector<spdlog::sink_ptr>{stdout_sink, rotating_sink};

        auto logger_name = std::string(CncLogger::DefaultLoggerName);

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
}

// class members
const auto CncLogger::DefaultLoggerName = std::string("nco");
const auto CncLogger::Default = CncLogger(CncLogger::DefaultLoggerName);

// class methods
void CncLogger::Register(const std::string name)
{
    Ensure_SpdLog_Initialised();

    if (name == CncLogger::DefaultLoggerName) {
        // default logger registered in Ensure_SpdLog_Initialised (exactly once)
        return;
    }

    spdlog::register_or_replace(
        std::make_shared<spdlog::async_logger>(
            name,
            sinks.begin(),
            sinks.end(),
            spdlog::thread_pool(),
            spdlog::async_overflow_policy::block
        )
    );
}

CncLogger::CncLogger(const std::string name) : Name(name)
{
    Register(name);
}

void CncLogger::Fatal(const std::string_view message) const
{
    (*this)().critical(message);
    exit(1);
}

spdlog::logger& CncLogger::operator()() const
{
    return *spdlog::get(Name);
}
