#include "logging.h"


void setupLogging() {
    // Rotating file - 5MB max, 3 backup files
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/pocketterm.log", 1024 * 1024 * 5, 3);

    // Also log to console for debugging
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // Combine both sinks
    std::vector<spdlog::sink_ptr> sinks {file_sink, console_sink};
    auto logger = std::make_shared<spdlog::logger>("pocketterm", sinks.begin(), sinks.end());

    // Set as default
    spdlog::set_default_logger(logger);

    // Log level (trace, debug, info, warn, error, critical)
    spdlog::set_level(spdlog::level::debug);

    // Pattern: [timestamp] [level] message
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
}
