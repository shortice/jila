#include <map>
#include "ulog.h"
#include "engine/logger.hpp"

namespace Jila {

Logger::Logger(std::string name) : name(name) {}

Logger::Logger() {}

void Logger::warn(std::string message) {
    ulog_warn("[%s] %s", name.c_str(), message.c_str());
}

void Logger::error(std::string message){
    ulog_error("[%s] %s", name.c_str(), message.c_str());
}

void Logger::debug(std::string message){
    ulog_debug("[%s] %s", name.c_str(), message.c_str());
}

void Logger::info(std::string message){
    ulog_info("[%s] %s", name.c_str(), message.c_str());
}

static std::map<std::string, Logger> loggers = {};

Logger& Logger::named(std::string name) {
    auto logger = loggers.find(name);

    if (logger == loggers.end()) {
        loggers[name] = Logger(name);
    }

    return loggers[name];
}

}
