#include "components/sdl3/events.hpp"
#include "SDL3/SDL_events.h"

namespace Jila {

void bindSdlEvent(sol::state* state) {
    state -> new_enum("SDL_EventType",
        "SDL_EVENT_WINDOW_RESIZED",
        SDL_EVENT_WINDOW_RESIZED,
        "SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED",
        SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED,
        "SDL_EVENT_USER",
        SDL_EVENT_USER
    );

    state -> new_usertype<SDL_UserEvent>(
        "SDL_UserEvent",
        "type", sol::readonly(&SDL_UserEvent::type),
        "code", sol::readonly(&SDL_UserEvent::code),
        "timestamp", sol::readonly(&SDL_UserEvent::timestamp)
    );

    state -> new_usertype<SDL_Event>("SDL_Event",
        "type", sol::readonly(&SDL_Event::type),
        "window", sol::readonly(&SDL_Event::window),
        "user", sol::readonly(&SDL_Event::user)
    );

    state -> new_usertype<SDL_WindowEvent>("SDL_WindowEvent",
        sol::no_constructor,
        "type", sol::readonly(&SDL_WindowEvent::type),
        "timestamp", sol::readonly(&SDL_WindowEvent::timestamp),
        "windowID", sol::readonly(&SDL_WindowEvent::windowID),
        "data1", sol::readonly(&SDL_WindowEvent::data1),
        "data2", sol::readonly(&SDL_WindowEvent::data2)
    );
}

}
