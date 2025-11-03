#include "components/sdl3/c_sdl3.hpp"
#ifdef JILA_AUDIO
#include "components/sdl3/audio.hpp"
#endif
#include "components/sdl3/events.hpp"
#ifdef JILA_IMAGES
#include "components/sdl3/images.hpp"
#endif
#include "components/sdl3/window.hpp"
#include "components/sdl3/micro.hpp"
#include "components/sdl3/timer.hpp"

namespace Jila {

namespace SdlComponent {

bool Init(sol::state* state) {
    #ifdef JILA_AUDIO
    bindSdlAudio(state);
    #endif
    bindSdlEvent(state);
    #ifdef JILA_IMAGES
    bindSdlImages(state);
    #endif
    bindSdlWindow(state);
    bindSdlMicro(state);
    bindSdlTimer(state);

    return true;
}

void Quit(sol::state* state) {

}

}

}
