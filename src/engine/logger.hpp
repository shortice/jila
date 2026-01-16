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

    void warn(std::string_view message);

    void error(std::string_view message);

    void debug(std::string_view message);
    
    void info(std::string_view message);

    static Logger& named(std::string_view name);
};

}
