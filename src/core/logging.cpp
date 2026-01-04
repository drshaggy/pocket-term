#include "logging.h"

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void setupLogging() {
      // Rotating file - 5MB max, 3 backup files
      auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
          "/var/log/pocket-term.log", 1024 * 1024 * 5, 3);

      // Set file sink to flush on every write (for debugging)
      file_sink->set_level(spdlog::level::trace);

      auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

      std::vector<spdlog::sink_ptr> sinks {file_sink, console_sink};
      auto logger = std::make_shared<spdlog::logger>("pocketterm", sinks.begin(), sinks.end());

      spdlog::set_default_logger(logger);
      spdlog::set_level(spdlog::level::debug);
      spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");

      // CRITICAL: Force flush on every log message
      spdlog::flush_on(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> createLogger(const std::string& name) {
    auto existing = spdlog::get(name); 
    if (existing) {
        return existing;
    }
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "/var/log/pocket-term.log", 1024 * 1024 * 5, 3);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    std::vector<spdlog::sink_ptr> sinks {file_sink, console_sink};
    auto logger = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());

    logger->set_level(spdlog::level::debug);
    logger->flush_on(spdlog::level::trace);

    spdlog::register_logger(logger);
    return logger;
}
