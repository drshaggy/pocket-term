#ifndef LOGGING_H_
#define LOGGING_H_

#include <spdlog/spdlog.h>
#include <memory>

void setupLogging();
std::shared_ptr<spdlog::logger> createLogger(const std::string& name);

#endif
