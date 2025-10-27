#include "components/sdl3/c_sdl3.hpp"
#include "components/sdl3/audio.hpp"
#include "components/sdl3/events.hpp"
#include "components/sdl3/images.hpp"
#include "components/sdl3/window.hpp"
#include "components/sdl3/micro.hpp"
#include "components/sdl3/timer.hpp"

namespace Jila {

namespace SdlComponent {

bool Init(sol::state* state) {
    bindSdlAudio(state);
    bindSdlEvent(state);
    bindSdlImages(state);
    bindSdlWindow(state);
    bindSdlMicro(state);
    bindSdlTimer(state);

    return true;
}

void Quit(sol::state* state) {

}

}

}
