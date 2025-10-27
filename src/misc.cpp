#include "SDL3/SDL_error.h"
#include "misc.hpp"
#include "engine/logger.hpp"

namespace Jila {

void CriticalError(std::string func) {
    Jila::Logger::named("Runtime").error(
        std::string("Error when calling %s: %s\n") +
        func +
        SDL_GetError()
    );
    std::exit(-1);
}

}
