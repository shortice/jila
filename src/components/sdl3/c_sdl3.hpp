#pragma once

#include "engine/component.hpp"

namespace Jila {

namespace SdlComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentSdl {
    "SDL",
    "Shortice",
    SdlComponent::Init,
    SdlComponent::Quit
};

}
