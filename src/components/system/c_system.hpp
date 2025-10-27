#pragma once
#include "engine/component.hpp"

namespace Jila {

namespace SystemComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentSystem {
    "System",
    "Shortice",
    false,
    SystemComponent::Init,
    SystemComponent::Quit
};

}
