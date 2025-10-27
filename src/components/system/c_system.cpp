#include "SDL3/SDL_platform.h"
#include "components/system/c_system.hpp"
#include "components/system/sys_android.hpp"

namespace Jila {

namespace SystemComponent {

bool Init(sol::state* state) {
    (*state)["platform"] = std::string(SDL_GetPlatform());
    bindSysAndroid(state);

    return true;
}

void Quit(sol::state* state) {}

}

}
