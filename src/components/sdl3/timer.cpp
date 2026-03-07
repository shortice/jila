#include "components/sdl3/timer.hpp"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_time.h"

namespace Jila {

// TODO: make a timer bindings.
// Use SDL_PushEvent in timer callbacks.

static SDL_DateTime DEFAULT_NULL {
    0, 0, 0, 0, 
    0, 0, 0, 
    0, 0
};

SDL_DateTime _SDL_TimeToDateTime(Uint32 time, bool localTime) {
    SDL_DateTime dt = DEFAULT_NULL;

    if (!SDL_TimeToDateTime(
        SDL_SECONDS_TO_NS(time), &dt, localTime
    )) return DEFAULT_NULL;

    return dt;
}

Uint32 _SDL_DateTimeToTime(SDL_DateTime dateTime) {
    SDL_Time time = 0;

    if (!SDL_DateTimeToTime(
        &dateTime, &time
    )) return nullptr;

    return time;
}

Uint32 _SDL_GetCurrentTime() {
    SDL_Time time = 0;

    if (!SDL_GetCurrentTime(&time)) return nullptr;

    return SDL_NS_TO_SECONDS(time);
}

SDL_DateTime _SDL_GetCurrentDateTime(bool localTime) {
    Uint32 time = _SDL_GetCurrentTime();

    if (!time) return DEFAULT_NULL;

    return _SDL_TimeToDateTime(
        time, localTime
    );
}

void bindSdlTimer(sol::state* state) {
    state->new_usertype<SDL_DateTime>(
        "Jila_DateTime",
        "second", &SDL_DateTime::second,
        "minute", &SDL_DateTime::minute,
        "hour", &SDL_DateTime::hour,
        "day", &SDL_DateTime::day,
        "day_of_week", &SDL_DateTime::day_of_week,
        "month", &SDL_DateTime::month,
        "year", &SDL_DateTime::year
    );

    state->set_function(
        "Jila_TimeToDateTime",
        &_SDL_TimeToDateTime
    );

    state->set_function(
        "Jila_DateTimeToTime",
        &_SDL_DateTimeToTime
    );

    state->set_function(
        "Jila_GetCurrentTime",
        &_SDL_GetCurrentTime
    );

    state->set_function(
        "Jila_GetCurrentDateTime",
        &_SDL_GetCurrentDateTime
    );
}

}
