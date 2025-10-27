#include <map>
#include "ulog.h"
#include "engine/logger.hpp"

namespace Jila {

Logger::Logger(std::string name) : name(name) {}

Logger::Logger() {}

Logger::Logger(const Logger& ref) {
    name = ref.name;
}

void Logger::warn(std::string message) {
    log_warn("[%s] %s", name.c_str(), message.c_str());
}

void Logger::error(std::string message){
    log_error("[%s] %s", name.c_str(), message.c_str());
}

void Logger::debug(std::string message){
    log_debug("[%s] %s", name.c_str(), message.c_str());
}

void Logger::info(std::string message){
    log_info("[%s] %s", name.c_str(), message.c_str());
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
