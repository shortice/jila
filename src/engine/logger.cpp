#include <map>
#include "ulog.h"
#include "engine/logger.hpp"

namespace Jila {

Logger::Logger(std::string name) : name(name) {}

Logger::Logger() {}

void Logger::warn(std::string_view message) {
    ulog_warn("[%s] %s", name.c_str(), message.data());
}

void Logger::error(std::string_view message){
    ulog_error("[%s] %s", name.c_str(), message.data());
}

void Logger::debug(std::string_view message){
    ulog_debug("[%s] %s", name.c_str(), message.data());
}

void Logger::info(std::string_view message){
    ulog_info("[%s] %s", name.c_str(), message.data());
}

static std::map<std::string, Logger> loggers = {};

Logger& Logger::named(std::string_view name) {
    auto logger = loggers.find(name.data());

    if (logger == loggers.end()) {
        loggers[name.data()] = Logger(name.data());
    }

    return loggers[name.data()];
}

}
