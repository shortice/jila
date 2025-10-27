#ifndef JILA_RELEASE
#include "SDL3/SDL_events.h"
#include "engine/hot_reloader.hpp"
#include "engine/logger.hpp"

namespace Jila {

void UpdateListener::handleFileAction(
    efsw::WatchID watchid, const std::string &dir,
    const std::string &filename, efsw::Action action,
    std::string oldFilename
) {
    Logger::named("Lua(hot-reload)") \
    .info("Making hot reload!");

    SDL_Event event;
    (void)event;
    event.type = SDL_EVENT_USER;
    event.user.code = 1001;

    SDL_PushEvent(&event);
};

}
#endif
