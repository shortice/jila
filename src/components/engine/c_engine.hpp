#pragma once

#include "engine/component.hpp"

namespace Jila {

namespace EngineComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentEngine {
    "Engine",
    "Shortice",
    false,
    EngineComponent::Init,
    EngineComponent::Quit
};

}
