#include "components/sdl3/timer.hpp"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_time.h"

namespace Jila {

// TODO: make a timer bindings.
// Use SDL_PushEvent in timer callbacks.

SDL_DateTime _SDL_TimeToDateTime(Uint32 time, bool localTime) {
    SDL_DateTime dt {0, 0, 0, 0, 0, 0, 0, 0, 0};

    SDL_TimeToDateTime(
        SDL_SECONDS_TO_NS(time), &dt, localTime
    );

    return dt;
}

Uint32 _SDL_DateTimeToTime(SDL_DateTime dateTime) {
    SDL_Time time = 0;

    if (!SDL_DateTimeToTime(
        &dateTime, &time
    )) return 0;

    return time;
}

Uint32 _SDL_GetCurrentTime() {
    SDL_Time time = 0;

    if (!SDL_GetCurrentTime(&time)) return 0;

    return SDL_NS_TO_SECONDS(time);
}

void bindSdlTimer(sol::state* state) {
    state->new_usertype<SDL_DateTime>(
        "SDL_DateTime",
        "second", &SDL_DateTime::second,
        "minute", &SDL_DateTime::minute,
        "hour", &SDL_DateTime::hour,
        "day", &SDL_DateTime::day,
        "day_of_week", &SDL_DateTime::day_of_week,
        "month", &SDL_DateTime::month,
        "year", &SDL_DateTime::year
    );

    state->set_function(
        "SDL_TimeToDateTime",
        &_SDL_TimeToDateTime
    );

    state->set_function(
        "SDL_DateTimeToTime",
        &_SDL_DateTimeToTime
    );

    state->set_function(
        "SDL_GetCurrentTime",
        &_SDL_GetCurrentTime
    );
}

}
