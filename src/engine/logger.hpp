#pragma once

#include <string>

namespace Jila {

/*
Basic logger.
*/
struct Logger {

    std::string name;

    Logger();
    Logger(std::string name);

    void warn(std::string message);

    void error(std::string message);

    void debug(std::string message);
    
    void info(std::string message);

    static Logger& named(std::string name);
};

}
