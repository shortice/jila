#pragma once

#include "engine/component.hpp"

namespace Jila {

namespace NetComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentNet {
    "Network",
    "Shortice",
    NetComponent::Init,
    NetComponent::Quit
};

}
